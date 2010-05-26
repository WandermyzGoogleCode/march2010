/*
 * test.cpp
 *
 *  Created on: 2010-5-15
 *      Author: skywalker
 */

#include "../include/crypto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "../include/aux.h"

int main()
{
	// test symmetric encryption/decryption

	char msg[] = "ddddddddddddddddlzflzflzf000000";
		printf("Testing symmetric encryption/decryption...\n");
		int len = 32;  // data length should be a multiple of 16
		fprintf(stdout, "plaintext: %s\n", msg);
		hexDump(stdout, "plaintext: ", (unsigned char*)msg, len);

		unsigned char key[32];   // 256-bit key

		// generate a random symmetric key for testing
		selectRandomKeyAES(key, 32);
		SymmetricKey sk;
		memcpy(sk.keycode, key, 32);

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
		hexDump(stdout, "newKey: ", newKey.keycode, 32);

		newKey = generateNextKey(sk);
		hexDump(stdout, "newKey: ", newKey.keycode, 32);

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

		hexDump(stdout, "Private Key 1: ", sk1.keycode, 32);
		hexDump(stdout, "Private Key 2: ", sk2.keycode, 32);
		hexDump(stdout, "Private Key 3: ", sk3.keycode, 32);

		// Testing generatePrivateKey and getPublicKey

		printf("\nTesting generatePrivateKey...\n");
		std::string word = "15810084822chimneyliumale";
		PrivateKey newPrivateKey = generatePrivateKey(word);
		PublicKey newPublicKey = getPublicKey(newPrivateKey);

		B256 temp;
		memcpy(&temp, &encryptedSymmetricKey, 256);
		signByPrivateKey(&encryptedSymmetricKey, newPrivateKey);
		sigSuccess = verifyByPublicKey(&temp, &encryptedSymmetricKey, newPublicKey);
		printf(sigSuccess ? "Verification OK!\n" : "Verification failed!\n");

		// Testing generateRandomSymmetricKey

		printf("\nTesting generateRandomSymmetricKey...\n");
		SymmetricKey kk = generateRandomSymmetricKey();
		hexDump(stdout, "Random Symmetric Key: ", kk.keycode, SYMMETRIC_KEY_SIZE);

		// Test serialization of asymmetric key

		printf("\nTesting serialization of asymmetric key...\n");
		PrivateKey key1;
		key1.rsaKey = RSA_generate_key(2048, RSA_F4, NULL, NULL);
		PublicKey key2 = getPublicKey(key1);

		PrivateKeyToTransfer t1 = writePrivateKeyToMem(key1);
		PublicKeyToTransfer t2 = writePublicKeyToMem(key2);

		PrivateKey key11 = getPrivateKeyFromMem(t1);
		PublicKey key22 = getPublicKeyFromMem(t2);

		SymmetricKey key3 = generateRandomSymmetricKey();

		hexDump(stdout, "Symmetric Key: ", key3.keycode, 32);

		unsigned char data2[256];
		memcpy(data2, key3.keycode, 32);
		encryptByPublicKey((B256*)data2, key22);
		decryptByPrivateKey((B256*)data2, key11);

		hexDump(stdout, "Decrypted    : ", data2, 32);
	}
