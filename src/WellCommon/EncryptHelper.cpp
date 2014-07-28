#include "StdAfx.h"
#include "EncryptHelper.h"
#include <stdio.h>
#include <string.h>

#include "cfilelog.h"

EncryptHelper::EncryptHelper(void)
{
}


EncryptHelper::~EncryptHelper(void)
{
}


//aes加密
int EncryptHelper::AES_Encrypt(const unsigned char* strIn, unsigned char* strOut, int& nlen)
{
	AES_KEY aes;
	unsigned char key[AES_BLOCK_SIZE];        // AES_BLOCK_SIZE = 16
	unsigned char iv[AES_BLOCK_SIZE];        // init vector
	unsigned char* input_string;
	unsigned char* encrypt_string;
	unsigned int len;        // encrypt length (in multiple of AES_BLOCK_SIZE)
	unsigned int i;

	// set the encryption length
	len = 0;
	int lenTmp = strlen((char*)strIn);
	if ((lenTmp + 1) % AES_BLOCK_SIZE == 0) {
		len = lenTmp + 1;
	} else {
		len = ((lenTmp + 1) / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
	}

	// set the input string
	input_string = (unsigned char*)calloc(len, sizeof(unsigned char));
	if (input_string == NULL) {
		//fprintf(stderr, "Unable to allocate memory for input_string\n");
		log() << "Unable to allocate memory for input_string";
	}
	strncpy((char*)input_string, (const char*)strIn, lenTmp);

	// Generate AES 128-bit key
	for (i=0; i<16; ++i) {
		key[i] = 32 + i;
	}

	// Set encryption key
	for (i=0; i<AES_BLOCK_SIZE; ++i) {
		iv[i] = 0;
	}
	if (AES_set_encrypt_key(key, 128, &aes) < 0) {
		//fprintf(stderr, "Unable to set encryption key in AES\n");
		log() << "Unable to set encryption key in AES";
		return -1;
	}

	// alloc encrypt_string
	encrypt_string = (unsigned char*)calloc(len, sizeof(unsigned char));    
	if (encrypt_string == NULL) {
		fprintf(stderr, "Unable to allocate memory for encrypt_string\n");
		log() << "Unable to allocate memory for encrypt_string";
		return -1;
	}

	// encrypt (iv will change)
	AES_cbc_encrypt(input_string, encrypt_string, len, &aes, iv, AES_ENCRYPT);

	//编码成16进制
	Encode2Hex(encrypt_string, len, strOut, nlen);

//	printf("encode result=%s/n", strOut);

	free(input_string);
	free(encrypt_string);
	return 0;
}

//aes解密
int EncryptHelper::AES_Decrypt(const unsigned char* strIn, int inLen, unsigned char* strOut, int& nlen)
{
	AES_KEY aes;
	unsigned char key[AES_BLOCK_SIZE];        // AES_BLOCK_SIZE = 16
	unsigned char iv[AES_BLOCK_SIZE];        // init vector
	unsigned char* decrypt_string;
	unsigned int len;        // encrypt length (in multiple of AES_BLOCK_SIZE)
	unsigned int i;

	//编码时会用=补齐为3/4的倍数，先求出实现长度
	unsigned char* chT = const_cast<unsigned char*>(strIn);
	int nT = inLen;
	while(chT[--nT] == '=')
		--inLen;

	int nTmp = 0;
	unsigned char chTmp[1024] = {0};
	len = DecodeHex(strIn, inLen, chTmp, nTmp);
	if(nTmp == -1 || len > 10000)
		return -1;

	// Generate AES 128-bit key
	for (i=0; i<16; ++i) {
		key[i] = 32 + i;
	}

	if (AES_set_encrypt_key(key, 128, &aes) < 0) {
		//fprintf(stderr, "Unable to set encryption key in AES\n");
		log() << "Unable to set encryption key in AES";
		return -1;
	}


	// alloc decrypt_string
	decrypt_string = (unsigned char*)calloc(len, sizeof(unsigned char));
	if (decrypt_string == NULL) {
		//fprintf(stderr, "Unable to allocate memory for decrypt_string\n");
		log() << "Unable to allocate memory for decrypt_string";
		return -1;
	}

	// Set decryption key
	for (i=0; i<AES_BLOCK_SIZE; ++i) {
		iv[i] = 0;
	}
	if (AES_set_decrypt_key(key, 128, &aes) < 0) {
		//fprintf(stderr, "Unable to set decryption key in AES\n");
		log() << "Unable to set decryption key in AES";
		return -1;
	}

	// decrypt
//	AES_cbc_encrypt(strIn, decrypt_string, len, &aes, iv, 
//		AES_DECRYPT);
	AES_cbc_encrypt(chTmp, decrypt_string, len, &aes, iv, 
			AES_DECRYPT);


	// print
// 	printf("encrypted string = ");
// 	for (i=0; i<len; ++i) {
// 		printf("%x%x", (strIn[i] >> 4) & 0xf, 
// 			strIn[i] & 0xf);    
// 	}
// 	printf("\n");
// 	printf("decrypted string = %s\n", decrypt_string);
	nlen = strlen((char*)decrypt_string);
	memcpy(strOut, decrypt_string, nlen);

	free(decrypt_string);

	return 0;
}

int EncryptHelper::Encode2Hex(const unsigned char *str,int str_len, unsigned char *encode,int& encode_len){
	encode_len = EVP_EncodeBlock(encode, str, str_len);
	return encode_len;
}

int EncryptHelper::DecodeHex(const unsigned char *str,int str_len, unsigned char *decode,int& decode_buffer_len){
	decode_buffer_len = EVP_DecodeBlock(decode, str, str_len);
	return decode_buffer_len;
}

/*
#include "EncryptHelper.h"
int _tmain(int argc, _TCHAR* argv[])
{
	EncryptHelper eh;
	const char* strIn ="[uid=DFJTA1RY8WUF8G8PSZYS][mac=9OABCEEF00FF][ddns=www.org.net][usr=admin][pwd=admin]";
	unsigned char* strOut =  (unsigned char*)calloc(1024, sizeof(unsigned char));  
	memset(strOut, 0, 1024);
	int len = 0;
	eh.AES_Encrypt((const unsigned char*)strIn, strOut, len);

	eh.AES_Decrypt(strOut, len, strOut, len);

	return 0; 
}
*/