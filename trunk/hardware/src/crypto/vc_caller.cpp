#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include "../include/data.h"
#include "../include/crypto.h"
using namespace std;

int main()
{
	const string tmpDir = "../tmp/";
	const string privateKeyFile = "../data/usr0_prikey.dat";
	const string publicKeyFile = "../data/usr0_pubkey.dat";
	const string serverPublicKeyFile = "../data/server_pubkey.dat";

	PublicKeyToTransfer publicMem;
	FILE* fd_publickey = fopen(publicKeyFile.c_str(), "rb");
	if (!fd_publickey)
	{
		fprintf(stderr, "opening failed!\n");
				return 1;
	}
	fread(publicMem.block, 400, 1, fd_publickey);
	fclose(fd_publickey);

	PrivateKeyToTransfer privateMem;
	FILE* fd_privatekey = fopen(privateKeyFile.c_str(), "rb");
	if (!fd_privatekey)
	{
		fprintf(stderr, "opening failed!\n");
				return 1;
	}
	fread(privateMem.block, 1500, 1, fd_privatekey);
	fclose(fd_privatekey);

	PublicKeyToTransfer serverPubMem;
	FILE* fd = fopen(serverPublicKeyFile.c_str(), "rb");
	fread(&serverPubMem, 400, 1, fd);
	PublicKey serverPublicKey = getPublicKeyFromMem(serverPubMem);
	fclose(fd);

	PublicKey pubKey = getPublicKeyFromMem(publicMem);
	PrivateKey priKey = getPrivateKeyFromMem(privateMem);

	unsigned char strPhoneNum[30];
	unsigned char strName[MAX_NAME_LENGTH];
	unsigned char strStatus[MAX_STATUS_LENGTH];

	string tmpFileName = tmpDir + "virtual_client.tmp";
	fd = fopen(tmpFileName.c_str(), "rb");
	fread(strPhoneNum, 1, 30, fd);
	fread(strName, 1, MAX_NAME_LENGTH, fd);
	fread(strStatus, 1, MAX_STATUS_LENGTH, fd);
	fclose(fd);
	remove(tmpFileName.c_str());

	int pos = -1;
	for (int i=0; i<30; i++)
	{
		if (strPhoneNum[i] == '\0')
		{
			pos = i;
			break;
		}
	}

	PhoneNumber iPhoneNum;
	sscanf((const char*)strPhoneNum, "%lld", &iPhoneNum);
	EncryptedPhoneNumber encryptedPhoneNum = EncryptedPhoneNumber::getEncryptedPhoneNumber(iPhoneNum, serverPublicKey);

	UserEntry entry;
	entry.pubKey = writePublicKeyToMem(pubKey);
	entry.myNumber = iPhoneNum;
	entry.nOfConnection = 1;
	entry.connection[0] = 0;
	memcpy(entry.name, strName, MAX_NAME_LENGTH);
	memcpy(entry.status, strStatus, MAX_STATUS_LENGTH);
	entry.valid = true;
	fillRandPadding(entry.randPadding, UserEntry::RAND_PADDING_SIZE);

	SymmetricKey sk = generateRandomSymmetricKey();
	symmetricallyEncrypt((unsigned char*)&entry, entry.validSize(), sk);
	encryptByPublicKey(&entry.symKey, serverPublicKey);

	tmpFileName = tmpDir + "virtual_client_c_return.tmp";
	fd = fopen(tmpFileName.c_str(), "wb");
	if (!fd)
	{
		fprintf(stderr, "opening failed!\n");
		return 1;
	}
	fwrite(&encryptedPhoneNum, ENCRYPTED_PHONENUMBER_LENGTH, 1, fd);
	fwrite(&entry, sizeof(entry), 1, fd);
	fclose(fd);
}
