#pragma once

//�궨��
#define PLAIN_FILE_OPEN_ERROR -1
#define KEY_FILE_OPEN_ERROR -2
#define CIPHER_FILE_OPEN_ERROR -3
#define OK 1

typedef char ElemType;  //���������������

class desencryption
{
public:
	desencryption(void);  //���캯��
	~desencryption(void);  //��������
	//DES���ܺ���
	int DES_Encrypt(const char *plainFile, const char *keyStr,const char *cipherFile); 
	//DES���ܺ���
	int DES_Decrypt(const char *cipherFile, const char *keyStr,const char *plainFile); 
};

