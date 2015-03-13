#pragma once
#include <string.h>
#include <string>
#include <fstream>
#include <iostream>
//#include "common.h"
using namespace std;

class AES
{
public:
	AES(void);
	~AES(void);
	void Encrypt_File(string plainFile, unsigned char* key, string cipherFile);
	void Decrypt_File(string plainFile, unsigned char* key, string cipherFile);

private:
	unsigned char* InvCipher(unsigned char* input);
	void* InvCipher(void* input, int length);
	void setKey(unsigned char *key);
	unsigned char *Cipher(unsigned char* input);
	unsigned char *Cipher(void* input, int length);
	void SubBytes(unsigned char state[][4]);
	void ShiftRows(unsigned char state[][4]);
	void MixColumns(unsigned char state[][4]);
	unsigned char FFmul(unsigned char a, unsigned char b);
	void AddRoundKey(unsigned char state[][4], unsigned char k[][4]);
	void KeyExpansion(unsigned char* key, unsigned char w[][4][4]);

	void InvSubBytes(unsigned char state[][4]);
	void InvShiftRows(unsigned char state[][4]);
	void InvMixColumns(unsigned char state[][4]);

	void PKCS7Padding(int count, unsigned char* block);
	int InvPKCS7Padding(unsigned char* block);
	char *UnsignedptrToCharptr(unsigned char *unc, int length);
	unsigned char *CharptrToUnsignedptr(char *c, int length);

	unsigned char w[11][4][4];
	unsigned char Sbox[256];
	unsigned char InvSbox[256];
};

