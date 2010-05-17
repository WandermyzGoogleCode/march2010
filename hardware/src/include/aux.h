/*
 * aux.h
 *
 * The auxiliary functions for crypto
 *
 *  Created on: 2010-5-16
 *      Author: skywalker
 */

#ifndef AUX_H_
#define AUX_H_

#include <openssl/evp.h>
#include <openssl/rand.h>

void hexDump(FILE* f, const char* title, const unsigned char* s, int len);

void selectRandomKeyAES(unsigned char* key, int b);

unsigned char *encryptMessageAES(EVP_CIPHER_CTX *ctx, unsigned char* data, int len, int *rb);

unsigned char* decryptMessageAES(EVP_CIPHER_CTX* ctx, unsigned char* data, int len);

#endif // AUX_H_
