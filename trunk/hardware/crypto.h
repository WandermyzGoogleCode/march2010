/*
 * crypto.h
 *
 *  Created on: 2010-5-8
 *      Author: spaceflyer
 */

#ifndef CRYPTO_H_
#define CRYPTO_H_

#include <string>

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
void encryptByPublicKey(void* data, int data_size, const PublicKey& key);

/*
 * @param data
 * 		the binary data that should be processed.
 * @param data size
 *		the size of data. You may specify additional condition to the size and discuss with us.
 * @param key
 * 		the key used
 */
void decryptByPublicKey(void* data, int data_size, const PublicKey& key);

//data encrypted by private key can only be decrypted by public key
/*
 * @param data
 * 		the binary data that should be processed.
 * @param data size
 *		the size of data. You may specify additional condition to the size and discuss with us.
 * @param key
 * 		the key used
 */
void encryptByPrivateKey(void* data, int data_size, const PrivateKey& key);

/*
 * @param data
 * 		the binary data that should be processed.
 * @param data size
 *		the size of data. You may specify additional condition to the size and discuss with us.
 * @param key
 * 		the key used
 */
void decryptByPrivateKey(void* data, int data_size, const PrivateKey& key);

/*
 * @param data
 * 		the binary data that should be processed.
 * @param data size
 *		the size of data. You may specify additional condition to the size and discuss with us.
 * @param key
 * 		the key used
 */
void symmetricallyEncrypt(void* data, int data_size, const SymmetricKey& key);

/*
 * @param data
 * 		the binary data that should be processed.
 * @param data size
 *		the size of data. You may specify additional condition to the size and discuss with us.
 * @param key
 * 		the key used
 */
void symmetricallyDecrypt(void* data, int data_size, const SymmetricKey& key);

//use the codeword input by user to generate a private key
PrivateKey generatePrivateKey(const std::string& codeword);

//use private key key to generate symmetric key.
SymmetricKey generateSymmetricKey(const PrivateKey& key);

//Generate next symmetric key according to the current key.
//This function should be determinant.
SymmetricKey generateNextKey(const SymmetricKey& key);

#endif /* CRYPTO_H_ */
