#include "StdAfx.h"
#include "encrypt.h"
#include "desencryption.h"
#include "RC4.H"
#include <ImageHlp.h>

string key;         //密钥
string en_dir;      //加密输出目录
string de_dir;      //解密输出目录
Fvector filelist;   //文件列表

CRITICAL_SECTION g_cs;    //临界区对象
int g_index = 0;          //全局资源，记录文件列表中已处理的索引
static HWND g_mainHnd;    //父窗体句柄
static HANDLE g_EnHnd_1;   //线程一句柄
static HANDLE g_EnHnd_2;   //线程二句柄
int t1 = 0;
int t2 = 0;

//构造函数,初始化成员变量
//	 key_f       密钥
//   en_dir_f    加密输出目录
//   de_dir_f    解密输出目录
//   filelist_f  文件列表
//	 mainHwnd    父窗体句柄
encrypt::encrypt(HWND mainHwnd, string key_f, Fvector filelist_f, string en_dir_f = "", string de_dir_f = "")
{
	g_mainHnd = mainHwnd;   //父窗体句柄
	key = key_f;            //密钥
	en_dir = en_dir_f;      //加密输出目录
	de_dir = de_dir_f;      //解密输出目录
	filelist = filelist_f;  //文件列表	
}

//析构函数
encrypt::~encrypt(void)
{
	//释放存放文件列表容器所占内存
	//Fvector().swap(filelist);  
}

//加密函数
void encrypt::desEncrypt()
{
	//初始化临界区对象
	InitializeCriticalSection(&g_cs);

	//定义两个线程用于加密操作
	CWinThread *pThread_1, *pThread_2;

	pThread_1 = AfxBeginThread(EnThread, this);   //开始加密线程1
	g_EnHnd_1 = pThread_1 ->m_hThread;            //获取线程1句柄

	pThread_2 = AfxBeginThread(EnThread, this);   //开始加密线程2
	g_EnHnd_2 = pThread_2 ->m_hThread;            //获取线程2句柄
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
		//desencryption des;
		//调用解密函数
		//des.DES_Decrypt(filelist[i].file.c_str(), key.c_str(), dir_temp.c_str());

		RC4 rc;
		rc.Decrypt(filelist[i].file.c_str(), key.c_str(), dir_temp.c_str());
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


UINT EnThread(LPVOID param)
{
	//线程当前要处理的文件列表索引
	int index;

	while(1)
	{	
		//临界区锁定共享资源
		EnterCriticalSection(&g_cs);
        
		if(g_index == filelist.size())
		{
			//向主线程发送完成消息
			::PostMessage(g_mainHnd, WM_FINISHMSG, 0, 0);

			//临界区解锁
			LeaveCriticalSection(&g_cs);
			return false;      //退出函数
		}

		index = g_index++;   //获得共享区索引值,并进行加1操作

		//临界区解锁
		LeaveCriticalSection(&g_cs);

		//输出目录临时变量
		string dir_temp;
		//调用文件路径转换函数
		pathTransform(en_dir, filelist[index], dir_temp);

		//创建des加密类对象
		desencryption des;
		//调用加密函数
		des.DES_Encrypt(filelist[index].file.c_str(), key.c_str(), dir_temp.c_str());
		//RC4 rc;
		//rc.Decrypt(filelist[index].file.c_str(), key.c_str(), dir_temp.c_str());

		
	}

	return true;
}