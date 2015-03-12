#include "desencryption.h"
#include "RC4.h"
#include "AES.h"
#include <string>


//加密算法基类
class BaseAlg
{
	public:
		//加密函数
		virtual void Encrypt(string plainFile, string keyStr,string cipherFile) = 0;
		//二级加密函数
		virtual void SecondEncrypt(string plainFile, string keyStr,string cipherFile) = 0;
		//解密函数
		virtual void Decrypt(string cipherFile, string keyStr,string plainFile) = 0;
};


//DES加密算法类
class DESAlg : public BaseAlg
{
	public:
		//加密函数
		virtual void Encrypt(string plainFile, string keyStr,string cipherFile);
		//二级加密函数
		virtual void SecondEncrypt(string plainFile, string keyStr,string cipherFile);
		//解密函数
		virtual void Decrypt(string cipherFile, string keyStr,string plainFile);
};


//RC4加密算法类
class RC4Alg : public BaseAlg
{
	public:
		//加密函数
		virtual void Encrypt(string plainFile, string keyStr,string cipherFile);
		//解密函数
		virtual void Decrypt(string cipherFile, string keyStr,string plainFile);
};


//AES加密算法类
class AESAlg : public BaseAlg
{
	public:
		//加密函数
		virtual void Encrypt(string plainFile, string keyStr,string cipherFile);
		//解密函数
		virtual void Decrypt(string cipherFile, string keyStr,string plainFile);
};