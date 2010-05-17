/*
 * hardware.cpp
 *
 *  Created on: 2010-5-17
 *      Author: spaceflyer
 */

#include <hardware.h>

static SafeCore* SafeCore::makeSafeCore(const PrivateKey& initKey);

bool SafeCore::getIndex(const EncryptedPhoneNumber& epn, Index& res);

bool SafeCore::getUpdateEntry(const UserEntry& operateUser,
		const UserEntry& targetUser, UpdateEntry& res, TimeType threshold,
		bool& updated);

TimeType SafeCore::makeNewUserEntry(const UserEntry& inputEntry,
		UserEntry& outputEntry);

TimeType SafeCore::makeUpdateUserEntry(const UserEntry& oldEntry,
		const UserEntry& inputEntry, UserEntry& outputEntry);

void SafeCore::refreshEntries(Index& firstIndex, UserEntry& firstEntry,
		Index& secondIndex, UserEntry& secondEntry);

void SafeCore::shiftToNextKey();

PublicKey getPublicKey();
