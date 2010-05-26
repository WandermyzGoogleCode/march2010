#include <stdio.h>
#include "../include/crypto.h"
#include <string>
#include <string.h>
using namespace std;

int main()
{
	const string dataDir = "/usr/local/lives3/data/";

	string public_key_filename = dataDir + "usr0_pubkey.dat";
	string private_key_filename = dataDir + "usr0_prikey.dat";

	RSA* rsaKey = RSA_generate_key(2048, RSA_F4, NULL, NULL);
	PrivateKey privateKey;
	privateKey.rsaKey = rsaKey;
	PublicKey publicKey = getPublicKey(privateKey);

	PrivateKeyToTransfer privateMem = writePrivateKeyToMem(privateKey);
	PublicKeyToTransfer publicMem = writePublicKeyToMem(publicKey);

	FILE * fd = fopen(public_key_filename.c_str(), "wb");
	fwrite(publicMem.block, 400, 1, fd);
	fclose(fd);

	fd = fopen(private_key_filename.c_str(), "wb");
	fwrite(privateMem.block, 1500, 1, fd);
	fclose(fd);
}
