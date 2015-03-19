#pragma once
#include <string>
#include "Algorithm.h"


//函数声明
void pathTransform(string dir, File fileinfo, string &dir_temp);        //文件路径转换函数
UINT EnThread(LPVOID param);											//加解密线程函数
BaseAlg *CreateAlg(BaseAlg *base, int alg);									//加解密线程函数

class task
{
public:
	task(HWND mainHwnd, string key, Fvector filelist, string en_dir, string de_dir);  //构造函数，初始化成员变量
	~task(void);  //析构函数
	void DoTask(int alg, int type);  //任务函数
};

