#pragma once
#include <string>
#include "common.h"

#define WM_FINISHMSG WM_USER + 200	//自定义消息

//声明文件路径转换函数
void pathTransform(string dir, File fileinfo, string &dir_temp);
UINT EnThread(LPVOID param);

class encrypt
{
public:
	encrypt(HWND mainHwnd, string key, Fvector filelist, string en_dir, string de_dir);  //构造函数，初始化成员变量
	~encrypt(void);  //析构函数
	void desEncrypt();  //加密函数
	void desDecrypt();  //解密函数
protected:
	int a;
};

