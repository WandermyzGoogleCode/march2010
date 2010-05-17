/*
 * data.h
 *
 *  Created on: 2010-5-4
 *      Author: spaceflyer
 */

#ifndef DATA_H_

#include "crypto.h"
#include <assert.h>

typedef long long 			int64;
typedef unsigned long long 	uint64;
typedef uint64				PhoneNumber;
typedef uint64				TimeType;

const int INDEX_LENGTH = 16;//16 bytes index(symmetrically encrypted)

//256 bytes encrypted phone number(random padded to 32 bytes)
//by SafeCore's PublicKey
const int ENCRYPTED_PHONENUMBER_LENGTH = 256;

const int MAX_NAME_LENGTH = 32;
const int MAX_STATUS_LENGTH =1024;
const int MAX_CONNECTION = 256;

struct EncryptedPhoneNumber
{
	unsigned char b[ENCRYPTED_PHONENUMBER_LENGTH];
};

struct Index
{
	unsigned char b[INDEX_LENGTH];
};

//Size about 3KB-4KB
struct UserEntry
{
	PublicKey pubKey;//The public key of this user
	PhoneNumber myNumber;//The phone number of this user

	TimeType updateTime;
	PhoneNumber connection[MAX_CONNECTION];
	char name[MAX_NAME_LENGTH];
	char status[MAX_STATUS_LENGTH];

	//We may add some invalid users into the database
	//to make sure no one can tell which real phone numbers
	//are using our system
	bool valid;

	char randPadding[3];

	B256 symKey;//a symKey or an asymmetrically encrypted symKey

	/* a signature of asymmetrically encrypted symKey
	 * or nothing if this is for register
	 */
	B256 siganture;

	/**
	 * the size of valid data.
	 *
	 * the remains are signature and symKey.
	 */
	int validSize(){
		int res = sizeof(UserEntry)-2*sizeof(B256);
		assert(res%16 == 0);//for symmetrically encryption
		return res;
	}
};

//Size: 1KB+40BYTE
struct UpdateEntry
{
	PhoneNumber phone;
	char name[MAX_NAME_LENGTH];
	char status[MAX_STATUS_LENGTH];

	char randPadding[8];

	B256 symKey;//a symKey or an asymmetrically encrypted symKey

	/**
	 * the size of valid data.
	 *
	 * the remains is symKey.
	 */
	int validSize(){
		int res = sizeof(UpdateEntry)-sizeof(B256);
		assert(res%16 == 0);//for symmetrically encryption
		return res;
	}
};

//Size: 4BYTE+nOfEntry*(1KB+40BYTE)
//Note that only those bytes are transfered through network
//
//This package itself will not be encrypted.
//But each entry is encrypted to ensure the security.
struct UpdatePackage
{
	int nOfEntry;

	//Only first nOfEntry are valid
	UpdateEntry entries[MAX_CONNECTION];
};

//Size: 4BYTE+nOfEntry*16BYTE
//Note that only those bytes are transfered through network
//
//This request itself will not be encrypted.
//But each entry is encrypted to ensure the security.
struct UpdateRequest
{
	int nOfEntry;

	EncryptedPhoneNumber entries[MAX_CONNECTION];
};

#define DATA_H_


#endif /* DATA_H_ */
