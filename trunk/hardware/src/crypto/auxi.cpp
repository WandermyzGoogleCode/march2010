/*
 * auxi.cpp
 *
 *  Created on: 2010-5-16
 *      Author: skywalker
 */

#include <openssl/evp.h>
#include <openssl/rand.h>

void hexDump(FILE* f, const char* title, const unsigned char* s, int len)
{
	fprintf(f, "%s", title);
	for (int i = 0; i < len; i++)
	{
		unsigned char ch = s[i];
		fprintf(f, "%x%x", (ch >> 4) & 0xf, ch & 0xf);
	}
	fprintf(f, "\n");
}

void selectRandomKeyAES(unsigned char* key, int b)
{
	RAND_bytes(key, b);
	//hexDump(stdout, "Random key: ", key, b);
}

unsigned char *encryptMessageAES(EVP_CIPHER_CTX *ctx, unsigned char* data,
		int len, int *rb)
{
	unsigned char* ret;
	int tmp, ol;

	ol = 0;
	ret = (unsigned char*) malloc(len + EVP_CIPHER_CTX_block_size(ctx));
	for (int i = 0; i < len / 128; i++)
	{
		if (!EVP_EncryptUpdate(ctx, &ret[ol], &tmp, &data[ol], 128))
			return NULL;
		ol += tmp;
	}
	if (len % 128)
	{
		if (!EVP_EncryptUpdate(ctx, &ret[ol], &tmp, &data[ol], len % 128))
			return NULL;
		ol += tmp;
	}
	if (!EVP_EncryptFinal(ctx, &ret[ol], &tmp))
		return NULL;
	*rb = ol + tmp;
	return ret;
}

unsigned char* decryptMessageAES(EVP_CIPHER_CTX* ctx, unsigned char* data, int len)
{
	unsigned char* ret = (unsigned char*) malloc(len);
	int ol, finalLen;
	EVP_DecryptUpdate(ctx, ret, &ol, data, len);
	if (!EVP_DecryptFinal(ctx, ret+ol, &finalLen))
	{
		free(ret);
		return NULL;
	}
	for (int i=0; i<len-(ol+finalLen); i++)
		ret[ol+finalLen+i] = 0;
	return ret;
}
