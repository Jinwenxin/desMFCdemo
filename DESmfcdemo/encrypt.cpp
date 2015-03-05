#include "StdAfx.h"
#include "encrypt.h"
#include "desencryption.h"
#include <ImageHlp.h>

//声明文件路径转换函数
void pathTransform(string dir, File fileinfo, string &dir_temp);


//构造函数,初始化成员变量
//	 key       密钥
//   en_dir    加密输出目录
//   de_dir    解密输出目录
//   filelist  文件列表
encrypt::encrypt(string key, Fvector filelist, string en_dir = "", string de_dir = "")
{
	this ->key = key;  //密钥
	this ->en_dir = en_dir;  //加密输出目录
	this ->de_dir = de_dir;  //解密输出目录
	this ->filelist = filelist;  //文件列表
}

//析构函数
encrypt::~encrypt(void)
{
	//释放存放文件列表容器所占内存
	Fvector().swap(filelist);  
}

//加密函数
void encrypt::desEncrypt()
{
	//遍历文件列表进行加密操作
	for(unsigned int i = 0; i < filelist.size(); i++)
	{
		//输出目录临时变量
		string dir_temp;
		//调用文件路径转换函数
		pathTransform(en_dir, filelist[i], dir_temp);

		//创建des加密类对象
		desencryption des;
		//调用加密函数
		des.DES_Encrypt(filelist[i].file.c_str(), key.c_str(), dir_temp.c_str());
	}
}

//解密函数
void encrypt::desDecrypt()
{
	//遍历文件列表进行解密操作
	for(unsigned int i = 0; i < filelist.size(); i++)
	{
		//输出目录临时变量
		string dir_temp;
		//调用文件路径转换函数
		pathTransform(de_dir, filelist[i], dir_temp);
		
		//创建des加密类对象
		desencryption des;
		//调用解密函数
		des.DES_Decrypt(filelist[i].file.c_str(), key.c_str(), dir_temp.c_str());
	}
}


//文件路径转换函数
//  dir        输出路径
//  fileinfo   待处理文件信息
//  dir_temp   转换后文件路径
void pathTransform(string dir, File fileinfo, string &dir_temp)
{
		if(dir != "")  
		{
			//将输出目录赋值给临时变量
			dir_temp = dir;

			////输出目录不为空则添加'\'
			//dir_temp += "\\";
			////在输出目录中添加文件名
			//int pos = filelist[i].file.find_last_of('\\');
			//dir_temp += filelist[i].file.substr(pos + 1);

			//查找要保持的文件目录结构起始位置
			int pos = fileinfo.from.size();
			//添加文件目录结构及文件名
			dir_temp += fileinfo.file.substr(pos);
			//保持文件的目录结构，如果目录不存在则创建目录
			MakeSureDirectoryPathExists(dir_temp.c_str());
		}
		else
		{
			//输出目录为空则在源目录生成重命名解密文件
			dir_temp = fileinfo.file;
			int pos = fileinfo.file.find_last_of('.');
			dir_temp.insert(pos, "副本");
		}
}
