/*
 * crypto.h
 *
 *  Created on: 2010-5-8
 *      Author: spaceflyer
 */

#ifndef CRYPTO_H_
#define CRYPTO_H_

#include <string>

struct PrivateKey{};//TODO Undefined

struct PublicKey{};//TODO Undefined

struct SymmetricKey{};//TODO Undefined

//data encrypted by public key can only be decrypted by private key
void encryptByPublicKey(void* data, int data_size, const PublicKey& key);
void decryptByPublicKey(void* data, int data_size, const PublicKey& key);

//data encrypted by private key can only be decrypted by public key
void encryptByPrivateKey(void* data, int data_size, const PrivateKey& key);
void decryptByPrivateKey(void* data, int data_size, const PrivateKey& key);

void symmetricallyEncrypt(void* data, int data_size, const SymmetricKey& key);
void symmetricallyDecrypt(void* data, int data_size, const SymmetricKey& key);

PrivateKey generatePrivateKey(const std::string& codeword);
SymmetricKey generateSymmetricKey(const PrivateKey& key);

//Generate next symmetric key according to the current key.
//This function should be determinant.
SymmetricKey generateNextKey(const SymmetricKey& key);

#endif /* CRYPTO_H_ */
