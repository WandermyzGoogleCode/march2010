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
 * @param data
 * 		the binary data that should be processed.
 * @param data_size
 *		the size of data. You may specify additional condition to the size and discuss with us.
 * @param key
 * 		the key used
 * @return
 * 		whether the operation is successful
 *
 * Special Note: data_size should be 512 exactly, while the size of useful data should be smaller
 *               than 470. If we use 256-bit
 */
bool encryptByPublicKey(B256* block, const PublicKey& key);

/*
 * @param data
 * 		the binary data that should be processed.
 * @param data_size
 *		the size of data. You may specify additional condition to the size and discuss with us.
 * @param key
 * 		the key used
 * @return
 * 		whether the operation is successful
 */
bool verifyByPublicKey(B256* block, B256* sig, const PublicKey& key);

//data encrypted by private key can only be decrypted by public key
/*
 * @param data
 * 		the binary data that should be processed.
 * @param data_size
 *		the size of data. You may specify additional condition to the size and discuss with us.
 * @param key
 * 		the key used
 * @return
 * 		whether the operation is successful
 */
bool signByPrivateKey(B256* data, const PrivateKey& key);

/*
 * @param data
 * 		the binary data that should be processed.
 * @param data_size
 *		the size of data. You may specify additional condition to the size and discuss with us.
 * @param key
 * 		the key used
 * @return
 * 		whether the operation is successful
 */
bool decryptByPrivateKey(B256* data, const PrivateKey& key);

/*
 * @param data
 * 		the binary data that should be processed.
 * @param data_size
 *		the size of data. You may specify additional condition to the size and discuss with us.
 * @param key
 * 		the key used
 * @return
 * 		whether the operation is successful
 */
bool symmetricallyEncrypt(unsigned char* data, int data_size, const SymmetricKey& key);

/*
 * @param data
 * 		the binary data that should be processed.
 * @param data_size
 *		the size of data. You may specify additional condition to the size and discuss with us.
 * @param key
 * 		the key used
 * @return
 * 		whether the operation is successful
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

PublicKey getPublicKey(const PrivateKey& key);

#endif /* CRYPTO_H_ */
