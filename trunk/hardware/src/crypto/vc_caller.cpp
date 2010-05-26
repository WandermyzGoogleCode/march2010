#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include "../include/data.h"
#include "../include/crypto.h"
using namespace std;

int main()
{
	const string tmpDir = "/usr/local/lives3/tmp/";
	const string privateKeyFile = "/usr/local/lives3/data/usr0_prikey.dat";
	const string publicKeyFile = "/usr/local/lives3/data/usr0_pubkey.dat";

	PublicKeyToTransfer publicMem;
	FILE* fd_publickey = fopen(publicKeyFile.c_str(), "rb");
	fread(publicMem.block, 400, 1, fd_publickey);
	fclose(fd_publickey);

	PrivateKeyToTransfer privateMem;
	FILE* fd_privatekey = fopen(privateKeyFile.c_str(), "rb");
	fread(privateMem.block, 1500, 1, fd_privatekey);
	fclose(fd_privatekey);

	PublicKey pubKey = getPublicKeyFromMem(publicMem);
	PrivateKey priKey = getPrivateKeyFromMem(privateMem);

	string tmpFileName = tmpDir + "virtual_client.tmp";
	FILE* fd = fopen(tmpFileName.c_str(), "rb");

	unsigned char strPhoneNum[30];
	unsigned char strName[MAX_NAME_LENGTH];
	unsigned char strStatus[MAX_STATUS_LENGTH];

	fread(strPhoneNum, 1, 30, fd);
	fread(strName, 1, MAX_NAME_LENGTH, fd);
	fread(strStatus, 1, MAX_STATUS_LENGTH, fd);

	int pos = -1;
	for (int i=0; i<30; i++)
	{
		if (strPhoneNum[i] == '\0')
		{
			pos = i;
			break;
		}
	}

	fclose(fd);

	PhoneNumber iPhoneNum;
	sscanf((const char*)strPhoneNum, "%lld", &iPhoneNum);
	EncryptedPhoneNumber encryptedPhoneNum = EncryptedPhoneNumber::getEncryptedPhoneNumber(iPhoneNum, pubKey);

	UserEntry entry;
	entry.pubKey = writePublicKeyToMem(pubKey);
	entry.myNumber = iPhoneNum;
	entry.nOfConnection = 1;
	entry.connection[0] = 0;
	memcpy(entry.name, strName, MAX_NAME_LENGTH);
	memcpy(entry.status, strStatus, MAX_STATUS_LENGTH);
	entry.valid = true;
	fillRandPadding(entry.randPadding, UserEntry::RAND_PADDING_SIZE);

	printf("%d\n", entry.validSize());
}
