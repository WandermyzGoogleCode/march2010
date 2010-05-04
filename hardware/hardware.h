/*
 * hardware.h
 *
 *  Created on: 2010-5-4
 *      Author: spaceflyer
 */

#ifndef HARDWARE_H_

#include "data.h"

/*
 * All private things can only be
 * accessed by hard ways, i.e. open the hardware.
 * Of course, that's the requirement for the
 * real hardware, not simulation.
 */
class SafeCore
{
private:
	/*
	 * initKey: 	the initial private key
	 * currentKey: 	the private key used now for symmetric encryption.
	 * 				note that asymmetric encryption always uses initKey as private key
	 * nextKey: 	the private key used in next generation
	 */
	PrivateKey initKey, currentKey, nextKey;

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

public:
	/*
	 * The maximum number that one key can be used to
	 * do some leak operations.
	 * Once currentCounter is greater than or equal to this,
	 * key update is enforced to do further leak operations.
	 */
	static const int MAX_COUNT = 1000000;

	int getCurrentCounter(){ return currentCounter; }

	//factory method
	static SafeCore* makeSafeCore(const PrivateKey& initKey);

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
	bool getUpdateEntry(
			const UserEntry& operateUser,
			const UserEntry& targetUser,
			UpdateEntry& res,
			TimeType threshold,
			bool& updated
	);

	/*
	 * a leak operation
	 *
	 * @return
	 * 		false when operations failed, true otherwise. The failure is
	 * 		caused by: 1. currentCounter too large
	 *
	 * @param inputEntry
	 * 		the userEntry that is asymmetrically encrypted by SafeCore's public key
	 * @param outputEntry
	 * 		the entry we need, which is encrypted symmetrically by SafeCore's currentKey
	 *
	 * Note that our system is not that secured. Once someone know your phone number
	 * and he also knows your friend's phone number, he may become an impostor and
	 * get your friend's information. However, that's not the security we are concerned about
	 * because the impostor already know the phone number of yours and your friends'.
	 * However, even we can't ensure this security in such a high alert level(by hardware),
	 * we may ensure it by administrator and our software system.
	 *
	 * The updateTime of outputEntry will be set up using the
	 * clock inside the hardware.(This is for incremental update)
	 */
	bool makeUserEntry(const UserEntry& inputEntry, UserEntry& outputEntry);

	/*
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
	void refreshEntries(Index& firstIndex, UserEntry& firstEntry, Index& secondIndex, UserEntry& secondEntry);

	/*
	 * a non-leak operation
	 *
	 * Just increase generation, reset currentCounter to be 0,
	 * reset lastRefreshIndex and assign nextKey to currentKey and generate
	 * the next nextKey.
	 */
	void shiftToNextKey();

	/*
	 * a non-leak operation
	 *
	 * Just to get the public key of SafeCore
	 */
	PublicKey getPublicKey();
};

#define HARDWARE_H_


#endif /* HARDWARE_H_ */
