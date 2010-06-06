/*
 * hardware.h
 *
 *  Created on: 2010-5-4
 *      Author: spaceflyer
 */

#ifndef HARDWARE_H_

#include "data.h"
#include "crypto.h"
#include "lock.h"
#include <assert.h>
#include <stdio.h>

//TODO add getGeneration interface
/*
 * All private things can only be
 * accessed by hard ways, i.e. open the hardware.
 * Of course, that's the requirement for the
 * real hardware, not simulation.
 */
class SafeCore {
private:
	/*
	 * initKey: 	the initial private key
	 */
	PrivateKeyToTransfer initKey;

	/*
	 * the public key of initKey
	 */
	PublicKeyToTransfer pubKey;

	/*
	 * currentKey: 	the private key used now for symmetric encryption.
	 * 				note that asymmetric encryption always uses initKey as private key
	 * nextKey: 	the private key used in next generation
	 */
	SymmetricKey currentKey, nextKey;

	/*
	 * currentCounter:
	 * 		The number of leak operations that have been done
	 * 		using the currentKey.
	 * generation:
	 * 		the generation of currentKey. 0 for initKey and so on.
	 */
	int generation, currentCounter;

	/*
	 * The index that is lastly refreshed.
	 * This is recorded to ensure that the
	 * index is refreshed in increasing order.
	 */
	Index lastRefreshIndex;

	//Only private constructor
	SafeCore(const PrivateKey& initKey);

	//Only to load
	SafeCore() {
	}

	void clearGeneration();

	TimeType makeUserEntry(UserEntry& outputEntry);

	TimeType getTimeNow();

public:
	/*
	 * The maximum number that one key can be used to
	 * do some leak operations.
	 * Once currentCounter is greater than or equal to this,
	 * key update is enforced to do further leak operations.
	 */
	static const int MAX_COUNT = 100;//TESTING

	int getCurrentCounter() {
		return currentCounter;
	}

	//factory method
	static void makeSafeCore(FILE* file, const PrivateKey& initKey) {
		SafeCore core(initKey);
		assert(fwrite(&core, sizeof(SafeCore), 1, file) == 1);
	}

	/*
	 * load a SafeCore from a file.
	 *
	 * In real hardware, this is not needed, since everything should
	 * be stored in hardware.
	 *
	 *
	 */
	static SafeCore* loadSafeCore(FILE* file) {
		SafeCore* res = new SafeCore;
		assert(fread(res, sizeof(SafeCore), 1, file) == 1);
		return res;
	}

	void save(FILE* file){
		fseek(file, 0, SEEK_SET);
		assert(fwrite(this, sizeof(SafeCore), 1, file) == 1);
	}

	/* a leak operation
	 *
	 * @return		false when currentCounter is too big and no
	 * 				leak operations are allowed. true when successful
	 * @param res	the result index
	 */
	bool getIndex(const EncryptedPhoneNumber& epn, Index& res);

	/*
	 * a leak operation
	 *
	 * @return
	 * 		false when operations failed, true otherwise. The failure may
	 * 		be caused by: 1. currentCounter too large; 2. no connection between
	 * 		two users; 3. bad input parameter
	 * @param operateUser
	 *		the UserEntry that is symmetrically encrypted by currentKey.
	 *		(i.e. the entry directly saved in database)
	 *		this user is the one who want to get the updateEntry
	 * @param targetUser
	 *		the UserEntry that is symmetrically encrypted by currentKey.
	 *		(i.e. the entry directly saved in database)
	 *		this user is the source of the updateEntry
	 * @param res
	 * 		the result UpdateEntry. It is asymmetrically encrypted by the public key of operateUser.
	 * 		So only operate user can decrypt it in his client using his private key.
	 * @param threshold
	 * 		a time threshold, if the update time of targetUser
	 * 		is later than this threshold, updated will be true.
	 * 		This feature is for incremental update.
	 * @param updated
	 * 		See the description of threshold.
	 */
	bool getUpdateEntry(const UserEntry& operateUser,
			const UserEntry& targetUser, UpdateEntry& res, TimeType threshold,
			bool& updated);

	/*
	 * a leak operation
	 *
	 * @return Successful or not
	 *
	 * @param hasOld
	 * 		whether there is an oldEntry.
	 * @param oldEntry
	 * 		the oldEntry.
	 * 		if this oldEntry is valid, we will return false.
	 * @param inputEntry
	 * 		the userEntry that is asymmetrically encrypted by SafeCore's public key
	 * @param outputEntry
	 * 		the entry we need, which is encrypted symmetrically by SafeCore's currentKey
	 *
	 * Even someone know your phone number, he can't retrieve your friend's information
	 * without knowing your private key.
	 *
	 * The updateTime of outputEntry will be set up using the
	 * clock inside the hardware.(This is for incremental update)
	 */
	bool makeNewUserEntry(bool hasOld, const UserEntry& oldEntry, const UserEntry& inputEntry,
			UserEntry& outputEntry);

	/*
	 * a leak operation
	 *
	 * @return Successful or not
	 *
	 * @param oldEntry
	 *		the old userEntry that is encrypted symmetrically by SafeCore's currentKey.
	 *		This is to ensure that the update operation is originated by the
	 *		real user. We will check whether inputEntry is encrypted by oldEntry's
	 *		private key(a signature).
	 *
	 * @param inputEntry
	 * 		the userEntry that is asymmetrically encrypted by SafeCore's public key,
	 * 		and then asymmetrically encrypted by user's private key as a signature.
	 *
	 * @param outputEntry
	 * 		the entry we need, which is encrypted symmetrically by SafeCore's currentKey
	 *
	 * Even someone know your phone number, he can't retrieve your friend's information
	 * without knowing your private key.
	 *
	 * However, we make sure that once you are registered, no one can be an impostor
	 * to change your profile, using the mechanism of signature.
	 *
	 * The updateTime of outputEntry will be set up using the
	 * clock inside the hardware.(This is for incremental update)
	 */
	bool makeUpdateUserEntry(const UserEntry& oldEntry,
			const UserEntry& inputEntry, UserEntry& outputEntry);

	/*
	 * return whether successful. Failed may be caused by non-increasing index
	 *
	 * a non-leak operation
	 *
	 * The index and entry input is symmetrically encrypted by currentKey and
	 * the index and entry output will be encrypted by nextKey.
	 * We don't know whether first index and entry in input will be
	 * the first index and entry in output or second.
	 *
	 * Note that firstIndex and secondIndex must be all greater than lastRefreshIndex.
	 * And the lastRefreshIndex will be set to the larger one of firstIndex and
	 * secondIndex in input.
	 */
	bool refreshEntries(Index& firstIndex, UserEntry& firstEntry,
			Index& secondIndex, UserEntry& secondEntry);

	/*
	 * return whether successful. Failed may be caused by non-increasing index
	 *
	 * a non-leak operation
	 *
	 * The index and entry input is symmetrically encrypted by currentKey and
	 * the index and entry output will be encrypted by nextKey.
	 *
	 * Note that index must be greater than lastRefreshIndex.
	 * This is only for the last entry to update and the lastUpdateIndex
	 * will set to largestIndex after this call.
	 *
	 * This call is designed to solve the problem that only
	 * odd number of entries exist.
	 */
	bool refreshEntry(Index& index, UserEntry& entry);

	/*
	 * a non-leak operation
	 *
	 * Just increase generation, reset currentCounter to be 0,
	 * reset lastRefreshIndex and assign nextKey to currentKey and generate
	 * the next nextKey.
	 */
	void shiftToNextKey(){
		currentKey = nextKey;
		nextKey = generateNextKey(currentKey);
		clearGeneration();
		generation++;
	}

	/*
	 * a non-leak operation
	 *
	 * Just to get the public key of SafeCore
	 */
	PublicKeyToTransfer getPublicKey() {
		return pubKey;
	}
};

#define HARDWARE_H_

#endif /* HARDWARE_H_ */
