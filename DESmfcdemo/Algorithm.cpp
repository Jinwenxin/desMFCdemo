#include "StdAfx.h"
#include "Algorithm.h"

//函数声明
bool IsSecondEncrypt(string filepath);


//DES加密算法类

//DES加密函数
void DESAlg::Encrypt(string plainFile, string keyStr,string cipherFile)
{
	//创建des加密类对象
	desencryption des;
	//调用加密函数
	des.DES_Encrypt(plainFile.c_str(), keyStr.c_str(), cipherFile.c_str());
}


//DES二级加密函数
void DESAlg::SecondEncrypt(string plainFile, string keyStr,string cipherFile)
{
	//创建des加密类对象
	desencryption des;
	//调用加密函数实现一级加密
	des.DES_Encrypt(plainFile.c_str(), keyStr.c_str(), cipherFile.c_str());
	//调用加密函数实现二级加密，并修改加密文件后缀
	des.DES_Encrypt(cipherFile.c_str(), keyStr.c_str(), (cipherFile + "s").c_str());
	//删除一级加密文件
	remove(cipherFile.c_str());
}


//DES解密函数
void DESAlg::Decrypt(string cipherFile, string keyStr,string plainFile)
{
	//创建des加密类对象
	desencryption des;
	if(IsSecondEncrypt(cipherFile))	//如果文件经过二级加密
	{
		//调用解密函数
		des.DES_Decrypt(cipherFile.c_str(), keyStr.c_str(), cipherFile.substr(0, cipherFile.size() - 1).c_str());
		//删除二级加密文件
		remove(cipherFile.c_str());
		//修改文件路径
		cipherFile = cipherFile.substr(0, cipherFile.size() - 1);
	}
	//调用解密函数
	des.DES_Decrypt(cipherFile.c_str(), keyStr.c_str(), plainFile.c_str());
	//删除一级加密文件
	//remove(cipherFile.c_str());
}


//RC4加密算法类

//RC4加密函数
void RC4Alg::Encrypt(string plainFile, string keyStr,string cipherFile)
{
	//创建RC4加密类对象
	RC4 rc4;
	//调用加密函数
	rc4.Encrypt(plainFile.c_str(), keyStr.c_str(), cipherFile.c_str());
}


//RC4解密函数
void RC4Alg::Decrypt(string cipherFile, string keyStr,string plainFile)
{
	//创建RC4加密类对象
	RC4 rc4;
	//调用解密函数
	rc4.Decrypt(cipherFile.c_str(), keyStr.c_str(), plainFile.c_str());
}


//AES加密算法类

//AES加密函数
void AESAlg::Encrypt(string plainFile, string keyStr,string cipherFile)
{
	//创建AES加密类对象
	AES aes;
	//调用加密函数
	aes.Encrypt_File(plainFile.c_str(), (unsigned char*)keyStr.c_str(), cipherFile.c_str());
}


//AES解密函数
void AESAlg::Decrypt(string cipherFile, string keyStr,string plainFile)
{
	//创建AES加密类对象
	AES aes;
	//调用解密函数
	aes.Decrypt_File(cipherFile.c_str(), (unsigned char*)keyStr.c_str(), plainFile.c_str());
}


//判断文件是否经过二级加密函数
// filepath		待解密文件文件路径
extern bool IsSecondEncrypt(string filepath)
{
	//在文件路径中找到文件扩展名
	int pos = filepath.find_last_of('.');
	string ext = filepath.substr(pos + 1);

	//判断文件扩展名
	if(ext.compare("fess") == 0)
		//是二级加密文件
		return true;
	//不是二级加密文件
	return false;
}