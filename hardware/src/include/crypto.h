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

/**
 * just a buffer 256 bytes
 */
struct B256{
	char b[256];
};

struct PrivateKey{};//TODO You should specify the detailed members and structure.

struct PublicKey{};//TODO You should specify the detailed members and structure.

struct SymmetricKey{};//TODO You should specify the detailed members and structure.

//data encrypted by public key can only be decrypted by private key
/*
 * @param data
 * 		the binary data that should be processed.
 * @param data size
 *		the size of data. You may specify additional condition to the size and discuss with us.
 * @param key
 * 		the key used
 */
void encryptByPublicKey(B256* block, const PublicKey& key);

/*
 * @param data
 * 		the binary data that should be processed.
 * @param data size
 *		the size of data. You may specify additional condition to the size and discuss with us.
 * @param key
 * 		the key used
 */
void decryptByPublicKey(B256* data, const PublicKey& key);

//data encrypted by private key can only be decrypted by public key
/*
 * @param data
 * 		the binary data that should be processed.
 * @param data size
 *		the size of data. You may specify additional condition to the size and discuss with us.
 * @param key
 * 		the key used
 */
void encryptByPrivateKey(B256* data, const PrivateKey& key);

/*
 * @param data
 * 		the binary data that should be processed.
 * @param data size
 *		the size of data. You may specify additional condition to the size and discuss with us.
 * @param key
 * 		the key used
 */
void decryptByPrivateKey(B256* data, const PrivateKey& key);

/*
 * @param data
 * 		the binary data that should be processed.
 * @param data size
 *		the size of data. You may specify additional condition to the size and discuss with us.
 * @param key
 * 		the key used
 */
void symmetricallyEncrypt(unsigned char* data, int data_size, const SymmetricKey& key);

/*
 * @param data
 * 		the binary data that should be processed.
 * @param data size
 *		the size of data. You may specify additional condition to the size and discuss with us.
 * @param key
 * 		the key used
 */
void symmetricallyDecrypt(unsigned char* data, int data_size, const SymmetricKey& key);

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

#endif /* CRYPTO_H_ */
