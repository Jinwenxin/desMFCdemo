#include "desencryption.h"
#include "RC4.h"
#include "AES.h"
#include <string>

//加密算法类型
const int iDES = 0;  //DES
const int iRC4 = 1;  //RC4
const int iAES = 2;  //AES
//操作类型
const int iEncrypt = 0;     //一级加密
const int iSecEncrypt = 1;  //二级加密
const int iDecrypt = 2;  //解密

//函数声明
string FindExt(string filepath);		   //返回文件扩展名函数
bool IsSecondEncrypt(string filepath);	   //判断文件是否经过二级加密函数
void WriteInfo(int alg, string ext, string filepath);           //写入文件信息函数
int ReadInfo(int &alg, string &ext, string filepath);          //读取文件信息函数

//加密算法基类
class BaseAlg
{
	public:
		//加密函数
		virtual void Encrypt(string plainFile, const char *keyStr,string cipherFile) = 0;
		//二级加密函数
		virtual void SecondEncrypt(string plainFile, const char *keyStr,string cipherFile) = 0;
		//解密函数
		virtual void Decrypt(string cipherFile, const char *keyStr,string plainFile) = 0;
};


//DES加密算法类
class DESAlg : public BaseAlg
{
	public:
		//加密函数
		virtual void Encrypt(string plainFile, const char *keyStr,string cipherFile);
		//二级加密函数
		virtual void SecondEncrypt(string plainFile, const char *keyStr,string cipherFile);
		//解密函数
		virtual void Decrypt(string cipherFile, const char *keyStr,string plainFile);
};


//RC4加密算法类
class RC4Alg : public BaseAlg
{
	public:
		//加密函数
		virtual void Encrypt(string plainFile, const char *keyStr,string cipherFile);
		//二级加密函数
		virtual void SecondEncrypt(string plainFile, const char *keyStr,string cipherFile);
		//解密函数
		virtual void Decrypt(string cipherFile, const char *keyStr,string plainFile);
};


//AES加密算法类
class AESAlg : public BaseAlg
{
	public:
		//加密函数
		virtual void Encrypt(string plainFile, const char *keyStr,string cipherFile);
		//二级加密函数
		virtual void SecondEncrypt(string plainFile, const char *keyStr,string cipherFile);
		//解密函数
		virtual void Decrypt(string cipherFile, const char *keyStr,string plainFile);
};