#include "StdAfx.h"
#include "Algorithm.h"

//DES加密算法类

//DES加密函数
void DESAlg::Encrypt(string plainFile, const char *keyStr,string cipherFile)
{
	//创建des加密类对象
	desencryption des;
	//计算待加密文件MD5值
	string md5str = "";
	MD5_Read(plainFile.c_str(), md5str);
	//调用写入信息函数
	WriteInfo(iDES, FindExt(plainFile), md5str, cipherFile);
	//调用加密函数
	des.DES_Encrypt(plainFile.c_str(), keyStr, cipherFile.c_str());
}


//DES二级加密函数
void DESAlg::SecondEncrypt(string plainFile, const char *keyStr,string cipherFile)
{
	//创建des加密类对象
	desencryption des;
	//调用加密函数实现一级加密
	des.DES_Encrypt(plainFile.c_str(), keyStr, cipherFile.c_str());
	//计算待加密文件MD5值
	string md5str;
	MD5_Read(plainFile.c_str(),md5str);
	//调用写入信息函数
	WriteInfo(iDES, FindExt(plainFile), md5str, cipherFile + "s");
	//调用加密函数实现二级加密，并修改加密文件后缀
	des.DES_Encrypt(cipherFile.c_str(), keyStr, (cipherFile + "s").c_str());
	//删除一级加密文件
	remove(cipherFile.c_str());
}


//DES解密函数
void DESAlg::Decrypt(string cipherFile, const char *keyStr,string plainFile)
{
	//创建des加密类对象
	desencryption des;
	if(IsSecondEncrypt(cipherFile))	//如果文件经过二级加密
	{
		//调用解密函数
		des.DES_Decrypt(cipherFile.c_str(), keyStr, cipherFile.substr(0, cipherFile.size() - 1).c_str());
		//删除二级加密文件
		remove(cipherFile.c_str());
		//修改文件路径
		cipherFile = cipherFile.substr(0, cipherFile.size() - 1);
	}
	//调用解密函数
	des.DES_Decrypt(cipherFile.c_str(), keyStr, plainFile.c_str());
	//删除一级加密文件
	remove(cipherFile.c_str());
}


//RC4加密算法类

//RC4加密函数
void RC4Alg::Encrypt(string plainFile, const char *keyStr,string cipherFile)
{
	//创建RC4加密类对象
	RC4 rc4;
	//计算待加密文件MD5值
	string md5str = "";
	MD5_Read(plainFile.c_str(), md5str);
	WriteInfo(iRC4, FindExt(plainFile), md5str, cipherFile);
	//调用加密函数
	rc4.Encrypt(plainFile.c_str(), keyStr, cipherFile.c_str());
}


//RC4二级加密函数
void RC4Alg::SecondEncrypt(string plainFile, const char *keyStr,string cipherFile)
{

}


//RC4解密函数
void RC4Alg::Decrypt(string cipherFile, const char *keyStr,string plainFile)
{
	//创建RC4加密类对象
	RC4 rc4;
	//调用解密函数
	rc4.Decrypt(cipherFile.c_str(), keyStr, plainFile.c_str());
	//删除一级加密文件
	remove(cipherFile.c_str());
}


//AES加密算法类

//AES加密函数
void AESAlg::Encrypt(string plainFile, const char *keyStr,string cipherFile)
{
	//创建AES加密类对象
	AES aes;
	//调用加密函数
	aes.Encrypt_File(plainFile.c_str(), (unsigned char*)keyStr, cipherFile.c_str());
}


//AES解密函数
void AESAlg::Decrypt(string cipherFile, const char *keyStr,string plainFile)
{
	//创建AES加密类对象
	AES aes;
	//调用解密函数
	aes.Decrypt_File(cipherFile.c_str(), (unsigned char*)keyStr, plainFile.c_str());
}


//返回文件扩展名函数
// filepath    文件路径
extern string FindExt(string filepath)
{
	//在文件路径中找到文件扩展名
	int pos = filepath.find_last_of('.');
	return filepath.substr(pos + 1);
}


//判断文件是否经过二级加密函数
// filepath		待解密文件文件路径
extern bool IsSecondEncrypt(string filepath)
{
	//获取文件扩展名
	string ext = FindExt(filepath);

	//判断文件扩展名
	if(ext.compare("fess") == 0)
		//是二级加密文件
		return true;
	//不是二级加密文件
	return false;
}


//写入文件信息函数
// alg          加密算法类型
// ext          文件拓展名
// filepath		文件路径
extern void WriteInfo(int alg, string ext, string md5str, string filepath)
{
	FILE *file;
	//新建或打开待写入文件
	if((file = fopen(filepath.c_str(),"wb")) == NULL)
		return;

	//文件信息缓冲区
	string buf;
	//把加密类型放入文件信息缓冲区
	buf.push_back('0' + alg);
	//加入信息分隔符 
	buf.push_back('*');
	//加入文件扩展名
	buf += ext;
	//加入信息分隔符 
	buf.push_back('*');
	//加入MD5值
	buf += md5str;
	//用信息分隔符填充剩余长度字符
	while(buf.size() < BUFMAX)
		buf.push_back('*');

	//将文件信息写入文件
	fwrite(buf.c_str(), sizeof(char), buf.size(), file);
	//关闭文件
	fclose(file);
}


//读取文件信息函数
// alg			加密算法类型
// ext			文件扩展名
// filepath		文件路径 
void ReadInfo(int &alg, string &ext,string &md5str, string filepath)
{
	FILE *file;
	//打开待解密文件
	if((file = fopen(filepath.c_str(),"rb")) == NULL)
		return;

	//文件信息缓冲区
	char buf[BUFMAX];
	//读取加密类型及分隔符
	fread(buf, sizeof(char), BUFMAX, file);
	//将加密类型赋值
	alg = buf[0] - '0';

	//索引从扩展名首位开始
	int index = 2;
	//读取文件拓展名,遇到分隔符则停止读取
	while(buf[index] != '*')
	{
		//将读取的字符加入扩展名变量中
		ext.push_back(buf[index++]);
	}

	//索引从MD5值首位开始
	index++;
	//读取MD5值,遇到分隔符则停止读取
	while(buf[index] != '*')
	{
		//将读取的字符加入MD5值变量中
		md5str.push_back(buf[index++]);
	}

	//关闭文件
	fclose(file);
}