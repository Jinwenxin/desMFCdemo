#include "desencryption.h"
#include "RC4.h"
#include "AES.h"

//加密算法基类
class BaseAlg
{
	public:
		//加密函数
		virtual void Encrypt(const char *plainFile, const char *keyStr,const char *cipherFile) = 0;
		//解密函数
		virtual void Decrypt(const char *cipherFile, const char *keyStr,const char *plainFile) = 0;
};

//DES加密算法类
class DESAlg : public BaseAlg
{
	public:
		//加密函数
		virtual void Encrypt(const char *plainFile, const char *keyStr,const char *cipherFile)
		{
			//创建des加密类对象
			desencryption des;
			//调用加密函数
			des.DES_Encrypt(plainFile, keyStr, cipherFile);
		}

		//解密函数
		virtual void Decrypt(const char *cipherFile, const char *keyStr,const char *plainFile)
		{
			//创建des加密类对象
			desencryption des;
			//调用解密函数
			des.DES_Decrypt(cipherFile, keyStr, plainFile);
		}
};


//RC4加密算法类
class RC4Alg : public BaseAlg
{
	public:
		//加密函数
		virtual void Encrypt(const char *plainFile, const char *keyStr,const char *cipherFile)
		{
			//创建RC4加密类对象
			RC4 rc4;
			//调用加密函数
			rc4.Encrypt(plainFile, keyStr, cipherFile);
		}

		//解密函数
		virtual void Decrypt(const char *cipherFile, const char *keyStr,const char *plainFile)
		{
			//创建RC4加密类对象
			RC4 rc4;
			//调用解密函数
			rc4.Decrypt(cipherFile, keyStr, plainFile);
		}
};


//AES加密算法类
class AESAlg : public BaseAlg
{
	public:
		//加密函数
		virtual void Encrypt(const char *plainFile, const char *keyStr,const char *cipherFile)
		{
			//创建AES加密类对象
			AES aes;
			//调用加密函数
			aes.Encrypt_File(plainFile, (unsigned char*)keyStr, cipherFile);
		}

		//解密函数
		virtual void Decrypt(const char *cipherFile, const char *keyStr,const char *plainFile)
		{
			//创建AES加密类对象
			AES aes;
			//调用解密函数
			aes.Decrypt_File(cipherFile, (unsigned char*)keyStr, plainFile);
		}
};