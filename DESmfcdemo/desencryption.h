#include <string>
#include <vector>
using namespace std;
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
	desencryption(string key, vector<string> filelist, string en_dir, string de_dir);  //构造函数，初始化成员变量
	~desencryption(void);  //析构函数
	void desEncrypt();  //加密函数
	void desDecrypt();  //解密函数

private:
	string key;  //密钥
	string en_dir;  //加密输出目录
	string de_dir;  //解密输出目录
	vector<string> filelist;  //文件列表
};

