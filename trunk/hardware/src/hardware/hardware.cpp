/*
 * hardware.cpp
 *
 *  Created on: 2010-5-17
 *      Author: spaceflyer
 */

#include "../include/data.h"
#include "../include/hardware.h"
#include "../include/crypto.h"
#include "../include/lock.h"
#include "../include/auxi.h"
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>

void SafeCore::clearGeneration() {
	currentCounter = 0;
	memset(&lastRefreshIndex, 0, sizeof(Index));
}

TimeType SafeCore::getTimeNow() {
	timeval t;
	gettimeofday(&t, NULL);
	return TimeType(t.tv_sec);
}

SafeCore::SafeCore(const PrivateKey& initKey) {
	this->initKey = writePrivateKeyToMem(initKey);
	pubKey = writePublicKeyToMem(::getPublicKey(initKey));
	currentKey = generateSymmetricKey(initKey);
	nextKey = generateNextKey(currentKey);
	generation = 0;
	clearGeneration();
}

bool SafeCore::getIndex(const EncryptedPhoneNumber& epn, Index& res) {
	if (currentCounter >= MAX_COUNT)
		return false;
	currentCounter++;
	B256 buffer;
	memcpy(&buffer, &epn, sizeof(EncryptedPhoneNumber));
	decryptByPrivateKey(&buffer, getPrivateKeyFromMem(initKey));
	memset(buffer.b + sizeof(PhoneNumber), 0, sizeof(buffer)
			- sizeof(PhoneNumber));//clear random padding
	memcpy(&res, &buffer, sizeof(Index));
	symmetricallyEncrypt((BYTE*) &res, sizeof(Index), currentKey);
	return true;
}

bool SafeCore::getUpdateEntry(const UserEntry& operateUser,
		const UserEntry& targetUser, UpdateEntry& res, TimeType threshold,
		bool& updated) {
	if (currentCounter >= MAX_COUNT)
		return false;
	currentCounter++;
	UserEntry rOperateUser = operateUser, rTargetUser = targetUser;
	symmetricallyDecrypt((BYTE*) &rOperateUser, rOperateUser.validSize(),
			currentKey);
	symmetricallyDecrypt((BYTE*) &rTargetUser, rTargetUser.validSize(),
			currentKey);

	//	hexDump(stdout, "Operate Valid:", (BYTE*)&rOperateUser.valid, 1);
	//	hexDump(stdout, "Target Valid:", (BYTE*)&rTargetUser.valid, 1);

	bool connected = false;
	if (rTargetUser.nOfConnection >= MAX_CONNECTION)//bad entry
		return false;
	if (!rTargetUser.valid)
		return false;
	for (int i = 0; i < rTargetUser.nOfConnection; i++)
		if (rTargetUser.connection[i] == 0 || rTargetUser.connection[i]
				== rOperateUser.myNumber) {//0 for unidirectional entry
			connected = true;
			break;
		}
	if (!connected)
		return false;
	updated = (threshold < rTargetUser.updateTime);

	memcpy(&res, &rTargetUser, res.validSize());
	fillRandPadding(&(res.randPadding), res.RAND_PADDING_SIZE);
	SymmetricKey key = generateRandomSymmetricKey();
	symmetricallyEncrypt((BYTE*) &res, res.validSize(), key);

	memcpy(&(res.symKey), &key, sizeof(key));
	encryptByPublicKey(&(res.symKey), getPublicKeyFromMem(rOperateUser.pubKey));
	return true;
}

TimeType SafeCore::makeUserEntry(UserEntry& outputEntry) {
	decryptByPrivateKey(&outputEntry.symKey, getPrivateKeyFromMem(initKey));
	//hexDump(stdout, "After transfer: ", outputEntry.symKey.b, 32);
	SymmetricKey symKey;
	memcpy(&symKey, &outputEntry.symKey, sizeof(symKey));
	symmetricallyDecrypt((BYTE*) &outputEntry, outputEntry.validSize(), symKey);
	TimeType res = outputEntry.updateTime = getTimeNow();
	outputEntry.valid = true;
	fillRandPadding(&(outputEntry.randPadding), outputEntry.RAND_PADDING_SIZE);
	symmetricallyEncrypt((BYTE*) &outputEntry, outputEntry.validSize(),
			currentKey);

	memset((BYTE*) &outputEntry + outputEntry.validSize(), 0,
			sizeof(outputEntry) - outputEntry.validSize());
	return true;
}

bool SafeCore::makeNewUserEntry(bool hasOld, const UserEntry& oldEntry,
		const UserEntry& inputEntry, UserEntry& outputEntry) {
	if (currentCounter >= MAX_COUNT)
		return 0;
	currentCounter++;
	if (hasOld) {
		UserEntry rOldEntry = oldEntry;
		symmetricallyDecrypt((BYTE*) &rOldEntry, rOldEntry.validSize(),
				currentKey);
		if (rOldEntry.valid)
			return 0;
	}
	outputEntry = inputEntry;
	return makeUserEntry(outputEntry);
}

bool SafeCore::makeUpdateUserEntry(const UserEntry& oldEntry,
		const UserEntry& inputEntry, UserEntry& outputEntry) {
	if (currentCounter >= MAX_COUNT)
		return 0;
	currentCounter++;
	UserEntry rOldEntry = oldEntry, rInputEntry = inputEntry;
	symmetricallyDecrypt((BYTE*) &rOldEntry, rOldEntry.validSize(), currentKey);

	if (!rOldEntry.valid || !verifyByPublicKey(&rInputEntry.symKey,
			&rInputEntry.siganture, getPublicKeyFromMem(rOldEntry.pubKey)))
		return 0;
	outputEntry = inputEntry;
	return makeUserEntry(outputEntry);
}

bool SafeCore::refreshEntries(Index& firstIndex, UserEntry& firstEntry,
		Index& secondIndex, UserEntry& secondEntry) {
	if (firstIndex.compare(lastRefreshIndex) <= 0)
		return false;
	if (firstIndex.compare(secondIndex) <= 0)
		return false;
	lastRefreshIndex = secondIndex;

	Index rIndex[2] = { firstIndex, secondIndex };
	UserEntry rEntry[2] = { firstEntry, secondEntry };
	for (int i = 0; i < 2; i++) {
		symmetricallyDecrypt((BYTE*) (rIndex + i), sizeof(Index), currentKey);
		memset(((BYTE*) (rIndex + i)) + sizeof(PhoneNumber), 0, sizeof(Index)
				- sizeof(PhoneNumber));

		symmetricallyEncrypt((BYTE*) (rIndex + i), sizeof(Index), nextKey);

		symmetricallyDecrypt((BYTE*) (rEntry + i), rEntry[i].validSize(),
				currentKey);
		symmetricallyEncrypt((BYTE*) (rEntry + i), rEntry[i].validSize(),
				nextKey);
		memset(((BYTE*) (rEntry + i)) + rEntry[i].validSize(), 0,
				sizeof(rEntry[i]) - rEntry[i].validSize());
	}
	if (rIndex[0].compare(rIndex[1]) > 0) {
		std::swap(rIndex[0], rIndex[1]);
		std::swap(rEntry[0], rEntry[1]);
	}
	firstIndex = rIndex[0];
	firstEntry = rEntry[0];
	secondIndex = rIndex[1];
	secondEntry = rEntry[1];

	return true;
}

bool SafeCore::refreshEntry(Index& index, UserEntry& entry) {
	if (index.compare(lastRefreshIndex) <= 0)
		return false;
	lastRefreshIndex = Index::getLargestIndex();
	symmetricallyDecrypt((BYTE*) (&index), sizeof(index), currentKey);
	memset(((BYTE*) (&index)) + sizeof(PhoneNumber), 0, sizeof(Index)
			- sizeof(PhoneNumber));
	symmetricallyEncrypt((BYTE*) (&index), sizeof(index), nextKey);

	symmetricallyDecrypt((BYTE*) (&entry), entry.validSize(), currentKey);
	symmetricallyEncrypt((BYTE*) (&entry), entry.validSize(), nextKey);
	memset(((BYTE*) (&entry)) + entry.validSize(), 0, sizeof(entry)
			- entry.validSize());
	return true;
}
