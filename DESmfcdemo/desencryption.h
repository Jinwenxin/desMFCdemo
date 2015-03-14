#pragma once

//宏定义
#define PLAIN_FILE_OPEN_ERROR -1
#define KEY_FILE_OPEN_ERROR -2
#define CIPHER_FILE_OPEN_ERROR -3
#define OK 1

typedef char ElemType;  //定义基本数据类型

class desencryption
{
public:
	desencryption(void);  //构造函数
	~desencryption(void);  //析构函数
	//DES加密函数
	int DES_Encrypt(const char *plainFile, const char *keyStr,const char *cipherFile); 
	//DES解密函数
	int DES_Decrypt(const char *cipherFile, const char *keyStr,const char *plainFile); 
};

