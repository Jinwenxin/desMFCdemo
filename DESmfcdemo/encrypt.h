#pragma once
#include <string>
#include "common.h"

class encrypt
{
public:
	encrypt(string key, Fvector filelist, string en_dir, string de_dir);  //构造函数，初始化成员变量
	~encrypt(void);  //析构函数
	void desEncrypt();  //加密函数
	void desDecrypt();  //解密函数

private:
	string key;  //密钥
	string en_dir;  //加密输出目录
	string de_dir;  //解密输出目录
	Fvector filelist;  //文件列表
};

