/*
 * test.cpp
 *
 *  Created on: 2010-5-15
 *      Author: skywalker
 */

#include "crypto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "aux.h"

int main()
{
	// test symmetric encryption/decryption

	char msg[] = "Liu Zhifang     ";
	printf("Testing symmetric encryption/decryption...\n");
	int len = 16;  // data length should be a multiple of 16
	fprintf(stdout, "plaintext: %s\n", msg);
	hexDump(stdout, "plaintext: ", (unsigned char*)msg, len);

	unsigned char key[32];   // 256-bit key

	// generate a random symmetric key for testing
	selectRandomKeyAES(key, 32);
	SymmetricKey sk;
	sk.len = 32;
	sk.keycode = key;

	symmetricallyEncrypt((unsigned char*)msg, len, sk);
	hexDump(stdout, "ciphertext: ", (unsigned char*)msg, len);

	symmetricallyDecrypt((unsigned char*)msg, len, sk);
	hexDump(stdout, "plaintext: ", (unsigned char*)msg, len);
	fprintf(stdout, "plaintext: %s\n", msg);

	// test asymmetric encryption/decryption

	printf("\nTesting asymmetric encryption/decryption...\n");
	RSA* rsaKey = RSA_generate_key(2048, RSA_F4, NULL, NULL);
	printf("%d\n", RSA_size(rsaKey));

	PublicKey serverPublicKey;
	serverPublicKey.e = rsaKey->e;
	serverPublicKey.n = rsaKey->n;

	PrivateKey serverPrivateKey;
	serverPrivateKey.rsaKey = rsaKey;

	unsigned char data[256];   // the result of RSA encryption is 256 bytes long
	memset(data, 0, sizeof(data));
	memcpy(data, sk.keycode, 32);

	B256* b1 = (B256*)data;
	encryptByPublicKey(b1, serverPublicKey);
	decryptByPrivateKey(b1, serverPrivateKey);

	hexDump(stdout, "plaintext: ", sk.keycode, 32);
	hexDump(stdout, "decrypted: ", data, 32);

	// test generateNextKey

	printf("\nTesting genrateNextKey...\n");
	SymmetricKey newKey = generateNextKey(sk);
	printf("newKey.len = %d\n", newKey.len);
	hexDump(stdout, "newKey: ", newKey.keycode, newKey.len);

	newKey = generateNextKey(sk);
	printf("newKey.len = %d\n", newKey.len);
	hexDump(stdout, "newKey: ", newKey.keycode, newKey.len);

	// testing signature

	printf("\nTesting signature...\n");

	RSA* userKey = RSA_generate_key(2048, RSA_F4, NULL, NULL);
	PublicKey userPublicKey;
	userPublicKey.e = userKey->e;
	userPublicKey.n = userKey->n;

	PrivateKey userPrivateKey;
	userPrivateKey.rsaKey = userKey;

	encryptByPublicKey(b1, serverPublicKey);
	B256 encryptedSymmetricKey;
	memcpy(&encryptedSymmetricKey, b1, 256);

	signByPrivateKey(b1, userPrivateKey);
	bool sigSuccess = verifyByPublicKey(&encryptedSymmetricKey, b1, userPublicKey);
	printf(sigSuccess ? "Verification OK!\n" : "Verification failed!\n");

	encryptedSymmetricKey.b[0] = 234;  // tamper the content
	sigSuccess = verifyByPublicKey(&encryptedSymmetricKey, b1, userPublicKey);
	printf(sigSuccess ? "Verification OK!\n" : "Verification failed!\n");

	// Testing generateSymmetricKey

	printf("\nTesting generateSymmetricKey...\n");

	PrivateKey pk1, pk2, pk3;
	pk1.rsaKey = RSA_generate_key(2048, RSA_F4, NULL, NULL);
	pk2.rsaKey = pk1.rsaKey;
	pk3.rsaKey = RSA_generate_key(2048, RSA_F4, NULL, NULL);

	SymmetricKey sk1, sk2, sk3;
	sk1 = generateSymmetricKey(pk1);
	sk2 = generateSymmetricKey(pk2);
	sk3 = generateSymmetricKey(pk3);

	hexDump(stdout, "Private Key 1: ", sk1.keycode, sk1.len);
	hexDump(stdout, "Private Key 2: ", sk2.keycode, sk2.len);
	hexDump(stdout, "Private Key 3: ", sk3.keycode, sk3.len);

	// Testing generatePrivateKey

	printf("\nTesting generatePrivateKey...\n");
	std::string word = "15810084822chimneyliumale";
	PrivateKey newPrivateKey = generatePrivateKey(word);
	PublicKey newPublicKey;
	newPublicKey.e = newPrivateKey.rsaKey->e;
	newPublicKey.n = newPrivateKey.rsaKey->n;

	B256 temp;
	memcpy(&temp, &encryptedSymmetricKey, 256);
	signByPrivateKey(&encryptedSymmetricKey, newPrivateKey);
	sigSuccess = verifyByPublicKey(&temp, &encryptedSymmetricKey, newPublicKey);
	printf(sigSuccess ? "Verification OK!\n" : "Verification failed!\n");
}


