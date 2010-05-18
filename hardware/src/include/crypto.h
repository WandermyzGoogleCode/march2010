/*
 * crypto.h
 *
 *  Created on: 2010-5-8
 *      Author: spaceflyer
 *  Modified on: 2010-5-14
 *  	Author: skywalker
 */

#ifndef CRYPTO_H_
#define CRYPTO_H_

#include <string>
#include <openssl/rsa.h>

/**
 * just a buffer 256 bytes
 */
struct B256
{
	unsigned char b[256];
};

struct PrivateKey
{
	// RSA key, including both public components and private components and
	// private components, and also big prime p and q which speed up the
	// calculation. Struct RSA is from OpenSSL.
	RSA *rsaKey;
};

struct PublicKey
{
	// only public components of struct RSA are included here
	BIGNUM *e;
	BIGNUM *n;
};

struct SymmetricKey
{
	int len; // the length of the symmetric key
	unsigned char* keycode; // the content of the symmetric key
};

/**
 * for all the routines below, size refers to number of bytes of data, not bits!
 */

//data encrypted by public key can only be decrypted by private key
/*
 * @param block
 * 		contains the binary data that should be processed.
 * @param key
 * 		the key used
 * @return
 * 		whether the operation is successful
 *
 * Special Note: data size should be 256 exactly. And this function is only used to
 *               encrypt 32-byte symmetric key.
 */
bool encryptByPublicKey(B256* block, const PublicKey& key);

/*
 * @param block
 * 		contains the decrypted symmetric key
 * @param sig
 *      the buffer which holds the signature for block
 * @param key
 * 		the key used
 * @return
 * 		whether verification is successful
 *
 * Special Note: sig is exactly generated in function signByPublicKey
 */
bool verifyByPublicKey(B256* block, B256* sig, const PublicKey& key);

//data encrypted by private key can only be decrypted by public key
/*
 * @param block
 * 		contains the binary data that should be processed.
 * @param key
 * 		the key used
 * @return
 * 		whether the operation is successful
 */
bool signByPrivateKey(B256* block, const PrivateKey& key);

/*
 * @param block
 * 		contains the binary data that should be processed.
 * @param key
 * 		the key used
 * @return
 * 		whether the operation is successful
 */
bool decryptByPrivateKey(B256* block, const PrivateKey& key);

/*
 * @param block
 * 		contains the binary data that should be processed.
 * @param key
 * 		the key used
 * @return
 * 		whether the operation is successful
 *
 * Special Note: data_size should be multiple of 16, while the size of useful data in 'data' should
 *               be smaller than data_size
 */
bool symmetricallyEncrypt(unsigned char* data, int data_size, const SymmetricKey& key);

/*
 * @param block
 * 		contains the binary data that should be processed.
 * @param key
 * 		the key used
 * @return
 * 		whether the operation is successful
 *
 * Special Note: data should be exactly generated from 'symmetricallyEncrypt', whose size is multiple of 16.
 *               so you don't need to take care of padding
 */
bool symmetricallyDecrypt(unsigned char* data, int data_size, const SymmetricKey& key);

/*
 * The following three generate functions should satisfy:
 * 	1. Same input, same output
 *  2. Without knowing the input, it's very hard to know the output
 *  3. The input and output key should be legal to their definition
 */

//use the codeword input by user to generate a private key
PrivateKey generatePrivateKey(const std::string& codeword);

//use private key key to generate symmetric key.
SymmetricKey generateSymmetricKey(const PrivateKey& key);

//Generate next symmetric key according to the current key.
//This function should be determinant.
SymmetricKey generateNextKey(const SymmetricKey& key);

// Get the public key from private key
PublicKey getPublicKey(const PrivateKey& key);

// Generate a random symmetric key.
SymmetricKey generateRandomSymmetricKey();

#endif /* CRYPTO_H_ */
