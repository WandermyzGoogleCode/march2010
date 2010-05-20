/*
 * data.h
 *
 *  Created on: 2010-5-4
 *      Author: spaceflyer
 */

#ifndef DATA_H_

#include "crypto.h"
#include <assert.h>
#include <string.h>

typedef unsigned char		BYTE;
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

static void fillRandPadding(void* p, int size) {
	for (int i = 0; i < size; i++)
		(((BYTE*) p)[i]) = rand() % 256;
}

struct EncryptedPhoneNumber
{
	unsigned char b[ENCRYPTED_PHONENUMBER_LENGTH];

	const static int PADDING_SIZE = 32-sizeof(PhoneNumber);

	static EncryptedPhoneNumber getEncryptedPhoneNumber(PhoneNumber pn, const PublicKey& pubkey){
		EncryptedPhoneNumber epn;
		memcpy(&epn, &pn, sizeof(pn));
		fillRandPadding(((BYTE*) (&epn)) + sizeof(pn), epn.PADDING_SIZE);
		encryptByPublicKey((B256*) &epn, pubkey);
		return epn;
	}
};

struct Index
{
	unsigned char b[INDEX_LENGTH];

	int compare(const Index& x){
		for(int i=0; i<INDEX_LENGTH; i++)
			if (b[i] != x.b[i])
				return ((int)b[i]-x.b[i]);
		return 0;
	}
};

//Size about 5KB-6KB
struct UserEntry
{
	static const int RAND_PADDING_SIZE = 3;

	PublicKeyToTransfer pubKey;//The public key of this user
	PhoneNumber myNumber;//The phone number of this user

	TimeType updateTime;
	int nOfConnection;
	PhoneNumber connection[MAX_CONNECTION];
	char name[MAX_NAME_LENGTH];
	char status[MAX_STATUS_LENGTH];

	//We may add some invalid users into the database
	//to make sure no one can tell which real phone numbers
	//are using our system
	bool valid;

	char randPadding[RAND_PADDING_SIZE];

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
	static int validSize(){
		int res = sizeof(UserEntry)-2*sizeof(B256);
		assert(res%16 == 0);//for symmetrically encryption
		return res;
	}
};

//Size: 1KB+40BYTE
struct UpdateEntry
{
	static const int RAND_PADDING_SIZE = 8;

	PhoneNumber phone;
	char name[MAX_NAME_LENGTH];
	char status[MAX_STATUS_LENGTH];

	char randPadding[RAND_PADDING_SIZE];

	B256 symKey;//a symKey or an asymmetrically encrypted symKey

	/**
	 * the size of valid data.
	 *
	 * the remains is symKey.
	 */
	static int validSize(){
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
