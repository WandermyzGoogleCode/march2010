/*
 * data.h
 *
 *  Created on: 2010-5-4
 *      Author: spaceflyer
 */

#ifndef DATA_H_

typedef long long 			int64;
typedef unsigned long long 	uint64;
typedef uint64				PhoneNumber;
typedef uint64				TimeType;

const int INDEX_LENGTH = 8;//128 bits index

//256 bits encrypted phone number(random padded)
//by SafeCore's PublicKey
const int ENCRYPTED_PHONENUMBER_LENGTH = 16;

const int MAX_NAME_LENGTH = 32;
const int MAX_STATUS_LENGTH =1024;
const int MAX_CONNECTION = 256;

struct EncryptedPhoneNumber
{
	unsigned char d[ENCRYPTED_PHONENUMBER_LENGTH];
};

struct Index
{
	unsigned char d[INDEX_LENGTH];
};

struct PrivateKey{};//TODO Undefined

struct PublicKey{};//TODO Undefined

//Size about 3KB-4KB
struct UserEntry
{
	PublicKey pubKey;//The public key of this user
	PhoneNumber myNumber;//The phone number of this user

	TimeType updateTime;
	PhoneNumber connection[MAX_CONNECTION];
	char name[MAX_NAME_LENGTH];
	char status[MAX_STATUS_LENGTH];

	uint64 randPadding;
};

//Size: 1KB+40BYTE
struct UpdateEntry
{
	PhoneNumber phone;
	char name[MAX_NAME_LENGTH];
	char status[MAX_STATUS_LENGTH];

	uint64 randPadding;
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
