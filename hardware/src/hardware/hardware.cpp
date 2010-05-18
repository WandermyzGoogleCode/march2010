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

void SafeCore::fillRandPadding(void* p, int size) {
	for (int i = 0; i < size; i++)
		(((BYTE*)p)[i]) = rand() % 256;
}

SafeCore::SafeCore(const PrivateKey& initKey) {
	pubKey = ::getPublicKey(initKey);
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
	decryptByPrivateKey(&buffer, initKey);
	memset(&buffer + sizeof(PhoneNumber), 0, sizeof(buffer)
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
	encryptByPublicKey(&(res.symKey), rOperateUser.pubKey);
	return true;
}

TimeType SafeCore::makeUserEntry(UserEntry& outputEntry){
	decryptByPrivateKey(&outputEntry.symKey, initKey);
	SymmetricKey symKey;
	memcpy(&symKey, &outputEntry.symKey, sizeof(symKey));
	symmetricallyDecrypt((BYTE*)&outputEntry, outputEntry.validSize(), symKey);
	TimeType res = outputEntry.updateTime = getTimeNow();
	outputEntry.valid = true;
	fillRandPadding(&(outputEntry.randPadding), outputEntry.RAND_PADDING_SIZE);
	symmetricallyEncrypt((BYTE*) &outputEntry, outputEntry.validSize(),
			currentKey);
	memset((BYTE*) &outputEntry + outputEntry.validSize(), 0,
			sizeof(outputEntry) - outputEntry.validSize());
	return res;
}

TimeType SafeCore::makeNewUserEntry(const UserEntry& inputEntry,
		UserEntry& outputEntry) {
	if (currentCounter >= MAX_COUNT)
		return false;
	currentCounter++;
	outputEntry = inputEntry;
	return makeUserEntry(outputEntry);
}

TimeType SafeCore::makeUpdateUserEntry(const UserEntry& oldEntry,
		const UserEntry& inputEntry, UserEntry& outputEntry) {
	if (currentCounter >= MAX_COUNT)
		return false;
	currentCounter++;
	UserEntry rOldEntry = oldEntry, rInputEntry = inputEntry;
	symmetricallyDecrypt((BYTE*)&rOldEntry, rOldEntry.validSize(), currentKey);
	if (!verifyByPublicKey(&rInputEntry.symKey, &rInputEntry.siganture, rOldEntry.pubKey))
		return false;
	outputEntry = inputEntry;
	return makeUserEntry(outputEntry);
}

int main() {
}
