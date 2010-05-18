/*
 * crypto.cpp
 *
 * Implementation of the interfaces in crypto.h
 *
 *  Created on: 2010-5-15
 *      Author: skywalker
 *  Modified on: 2010-5-16
 *  	Author: skywalker
 */

#include "../include/crypto.h"
#include "../include/aux.h"
#include <openssl/sha.h>
#include <openssl/ssl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bool symmetricallyEncrypt(unsigned char* data, int data_size,
		const SymmetricKey& key)
{
	int keyLength = key.len;

	if (keyLength != 32) // key length should be 32bytes, i.e. 256 bits.
		return false;

	// initialize the AES cipher
	EVP_CIPHER *pAesCipher = (EVP_CIPHER*) EVP_aes_256_cbc();
	EVP_CIPHER_CTX *encryptCtx = (EVP_CIPHER_CTX*) malloc(
			sizeof(EVP_CIPHER_CTX));
	EVP_EncryptInit(encryptCtx, pAesCipher, key.keycode, NULL);

	// encrypt
	int lenOutput; // the length of the ciphertext
	unsigned char* ciphertext = encryptMessageAES(encryptCtx, data, data_size
			- 1, &lenOutput);

	if (lenOutput != data_size) // the output length must equals input length
		return false;

	memcpy(data, ciphertext, data_size);
	free(ciphertext);
	return true;
}

bool symmetricallyDecrypt(unsigned char* data, int data_size,
		const SymmetricKey& key)
{
	int keyLength = key.len;

	if (keyLength != 32) // key length should be 32bytes, i.e. 256 bits.
		return false;

	// initialize the AES cipher
	EVP_CIPHER *pAesCipher = (EVP_CIPHER*) EVP_aes_256_cbc();
	EVP_CIPHER_CTX *decryptCtx = (EVP_CIPHER_CTX*) malloc(
			sizeof(EVP_CIPHER_CTX));
	EVP_DecryptInit(decryptCtx, pAesCipher, key.keycode, NULL);

	// decrypt
	unsigned char* decrypted = decryptMessageAES(decryptCtx, data, data_size);

	memcpy(data, decrypted, data_size);
	free(decrypted);
	return true;
}

bool encryptByPublicKey(B256* block, const PublicKey& key)
{
	int data_size = 256;
	unsigned char* data = (unsigned char*)block->b;

	RSA * publicKey = RSA_generate_key(2048, RSA_F4, NULL, NULL);
	publicKey->e = key.e;
	publicKey->n = key.n;
	publicKey->p = NULL;
	publicKey->q = NULL;
	publicKey->d = NULL;

	unsigned char* res = (unsigned char*) malloc(data_size);
	if (RSA_public_encrypt(32, data, res, publicKey, RSA_PKCS1_OAEP_PADDING)
			== -1)
		return false;

	memcpy(data, res, data_size);
	free(res);
	return true;
}

bool decryptByPrivateKey(B256* block, const PrivateKey& key)
{
	int data_size = 256;
	unsigned char* data = (unsigned char*)block->b;

	RSA * privateKey = key.rsaKey;

	unsigned char* res = (unsigned char*) malloc(data_size);
	if (RSA_private_decrypt(data_size, data, res, privateKey,
			RSA_PKCS1_OAEP_PADDING) == -1)
		return false;

	memcpy(data, res, data_size);
	free(res);
	return true;
}

SymmetricKey generateNextKey(const SymmetricKey& key)
{
	SymmetricKey newKey;
	newKey.len = key.len;
	newKey.keycode = (unsigned char*) malloc(newKey.len);

	SHA256(key.keycode, 32, newKey.keycode);

	return newKey;
}

bool signByPrivateKey(B256* block, const PrivateKey& key)
{
	int data_size = 256;
	unsigned char* data = (unsigned char*)block->b;

	unsigned char* res = (unsigned char*)malloc(data_size);
	unsigned int signLen;
	RSA_sign(NID_sha1, data, 32, res, &signLen, key.rsaKey);

	if (signLen != 256)
		return false;

	memcpy(data, res, data_size);
	free(res);
	return true;
}

bool verifyByPublicKey(B256* block, B256* sig, const PublicKey& key)
{
	int data_size = 256;
	int sig_size = 256;
	unsigned char* data = (unsigned char*)block->b;
	unsigned char* sig_buf = (unsigned char*)sig->b;

	RSA * publicKey = RSA_generate_key(2048, RSA_F4, NULL, NULL);
	publicKey->e = key.e;
	publicKey->n = key.n;
	publicKey->p = NULL;
	publicKey->q = NULL;
	publicKey->d = NULL;

	int success = RSA_verify(NID_sha1, data, 32, sig_buf, sig_size, publicKey);
	return (success==0 ? false : true);
}

SymmetricKey generateSymmetricKey(const PrivateKey& key)
{
	BIGNUM *bn = BN_new();
	BN_copy(bn, key.rsaKey->e);
	BN_add(bn, bn, key.rsaKey->d);
	BN_add(bn, bn, key.rsaKey->n);
	BN_add(bn, bn, key.rsaKey->p);
	BN_add(bn, bn, key.rsaKey->q);

	int len = BN_num_bytes(bn);
	unsigned char* tmp_buf = (unsigned char*)malloc(len);
	BN_bn2bin(bn, tmp_buf);

	SymmetricKey res;
	res.len = 32;
	res.keycode = (unsigned char*)malloc(res.len);
	SHA256(tmp_buf, len, res.keycode);

	BN_free(bn);
	return res;
}

PrivateKey generatePrivateKey(const std::string& codeword)
{
	unsigned char* codewordstr = (unsigned char*)codeword.c_str();
	int len = codeword.length();

	unsigned char num1[128];   // 1024-bit
	unsigned char num2[128];   // 1024-bit

	SHA512(codewordstr, len/4, num1);
	SHA512(codewordstr+len/4, len/4, num1+64);
	SHA512(codewordstr+len/4*2, len/4, num2);
	SHA512(codewordstr+len/4*3, len/4, num2+64);

	BIGNUM *p = BN_new();
	BIGNUM *q = BN_new();
	BIGNUM *n = BN_new();
	BIGNUM *e = BN_new();
	BIGNUM *d = BN_new();
	BIGNUM *big1 = BN_new();
	BN_dec2bn(&big1, "1");
	BN_bin2bn(num1, 128, p);
	BN_bin2bn(num2, 128, q);

	BN_CTX* ctx = BN_CTX_new();
	while (!BN_is_prime(p, BN_prime_checks, NULL, ctx, NULL))
		BN_add(p, p, big1);

	while (!BN_is_prime(q, BN_prime_checks, NULL, ctx, NULL))
		BN_add(q, q, big1);

	BN_mul(n, p, q, ctx);
	BN_dec2bn(&e, "65537");

	BIGNUM* tmp1 = BN_new();
	BIGNUM* tmp2 = BN_new();
	BN_sub(tmp1, p, big1);
	BN_sub(tmp2, q, big1);
	BN_mul(tmp1, tmp1, tmp2, ctx);
	BN_mod_inverse(d, e, tmp1,ctx);

	RSA* rsaKey = RSA_generate_key(2048, RSA_F4, NULL, NULL);
	BN_copy(rsaKey->p, p);
	BN_copy(rsaKey->q, q);
	BN_copy(rsaKey->n, n);
	BN_copy(rsaKey->e, e);
	BN_copy(rsaKey->d, d);

	PrivateKey res;
	res.rsaKey = rsaKey;

	char* str = BN_bn2dec(p);
	printf("p: %s\n", str);
	str = BN_bn2dec(q);
	printf("q: %s\n", str);
	str = BN_bn2dec(n);
	printf("n: %s\n", str);
	str = BN_bn2dec(e);
	printf("e: %s\n", str);
	str = BN_bn2dec(d);
	printf("d: %s\n", str);

	BN_free(tmp2);
	BN_free(tmp1);
	BN_CTX_free(ctx);
	BN_free(big1);
	BN_free(d);
	BN_free(e);
	BN_free(n);
	BN_free(q);
	BN_free(p);

	return res;
}

PublicKey getPublicKey(const PrivateKey& key)
{
	PublicKey res;
	res.e = BN_new();
	res.n = BN_new();
	BN_copy(res.e, key.rsaKey->e);
	BN_copy(res.n, key.rsaKey->n);

	return res;
}

//TODO
SymmetricKey generateRandomSymmetricKey(){}

