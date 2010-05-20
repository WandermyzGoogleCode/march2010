/*
 * caller_tester.cpp
 *
 *  Created on: 2010-5-19
 *      Author: spaceflyer
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include "../include/data.h"
#include "../include/crypto.h"
using namespace std;

const string caller_path =
		"/home/spaceflyer/programming/eclipse_workspace/hardware/hardware_caller";
const string run_path =
		"/home/spaceflyer/programming/eclipse_workspace/hardware/run/";
const string filename = "test";

FILE* testfile;
PublicKey pubkey;

Index getIndex(const EncryptedPhoneNumber& epn, const string& name) {
	Index ind;
	testfile = fopen(filename.c_str(), "wb");
	fwrite(&epn, sizeof(epn), 1, testfile);
	fclose(testfile);
	system(("cp " + filename + " " + name).c_str());
	system((caller_path + " safecore getIndex " + filename).c_str());
	testfile = fopen(filename.c_str(), "rb");
	fread(&ind, sizeof(ind), 1, testfile);
	fclose(testfile);
	return ind;
}

void testMakeSafeCore() {
	printf("TEST-----make safe core\n");
	system((caller_path + " safecore makeSafeCore").c_str());
	printf("\n");
}

void testGetPubKey() {
	printf("TEST-----get public key\n");
	system((caller_path + " safecore getPublicKey pubkey").c_str());
	PublicKeyToTransfer pkt;
	FILE* pf = fopen("pubkey", "rb");
	fread(&pkt, sizeof(pkt), 1, pf);
	fclose(pf);
	pubkey = getPublicKeyFromMem(pkt);
	printf("\n");
}

void testCompareIndex() {
	printf("TEST-----compare index\n");
	Index ind1, ind2;
	PhoneNumber pn = rand() % 10000;
	EncryptedPhoneNumber epn;

	ind1 = getIndex(EncryptedPhoneNumber::getEncryptedPhoneNumber(pn, pubkey),
			"ind1.in");
	system(("cp " + filename + " ind1").c_str());

	ind2 = getIndex(EncryptedPhoneNumber::getEncryptedPhoneNumber(pn, pubkey),
			"ind2.in");
	system(("cp " + filename + " ind2").c_str());

	printf("ind1 vs ind2 = %d\n", ind1.compare(ind2));
	printf("\n");
}

void testGetCounter() {
	printf("TEST-----get current counter\n");
	system((caller_path + " safecore getCurrentCounter " + filename).c_str());
	system(("cp " + filename + " counter").c_str());
	printf("\n");
}

void testMakeNewUser(PhoneNumber myNumber, PhoneNumber conNumber,
		const string& name) {
	printf("TEST-----make new user\n");
	UserEntry user;
	user.myNumber = myNumber;
	user.nOfConnection = 1;
	user.connection[1] = conNumber;
	strcpy(user.name, name.c_str());
	user.pubKey = writePublicKeyToMem(getPublicKey(generatePrivateKey(name)));
	SymmetricKey symKey = generateRandomSymmetricKey();
	memcpy(&(user.symKey), &symKey, sizeof(symKey));
	symmetricallyEncrypt((BYTE*) &user, user.validSize(), symKey);
	encryptByPublicKey(&(user.symKey), pubkey);//FIXME symKey valid 32 bytes or 256 bytes?
	testfile = fopen(filename.c_str(), "wb");
	bool hasOld = false;
	fwrite(&hasOld, sizeof(hasOld), 1, testfile);
	UserEntry oldEntry;
	memset(&oldEntry, 0, sizeof(oldEntry));
	fwrite(&oldEntry, sizeof(oldEntry), 1, testfile);
	fwrite(&user, sizeof(user), 1, testfile);
	fclose(testfile);
	system((caller_path + " safecore makeNewUserEntry " + filename).c_str());
	system(("cp " + filename + " " + name).c_str());
	printf("\n");
}

int main() {
	srand(time(0));
	chdir(run_path.c_str());
	testMakeSafeCore();
	testGetPubKey();
	testCompareIndex();
	testGetCounter();
	//testMakeNewUser(123, 456, "user.123");
	//testMakeNewUser(456, 123, "user.456");
	//testMakeNewUser(789, 0, "user.789");
}
