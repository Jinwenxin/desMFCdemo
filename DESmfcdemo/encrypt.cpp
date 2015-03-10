#include "StdAfx.h"
#include "encrypt.h"
#include "desencryption.h"
#include "RC4.H"
#include <ImageHlp.h>

string key;         //��Կ
string en_dir;      //�������Ŀ¼
string de_dir;      //�������Ŀ¼
Fvector filelist;   //�ļ��б�

CRITICAL_SECTION g_cs;    //�ٽ�������
int g_index = 0;          //ȫ����Դ����¼�ļ��б����Ѵ��������
static HWND g_mainHnd;    //��������
static HANDLE g_EnHnd_1;   //�߳�һ���
static HANDLE g_EnHnd_2;   //�̶߳����
int t1 = 0;
int t2 = 0;

//���캯��,��ʼ����Ա����
//	 key_f       ��Կ
//   en_dir_f    �������Ŀ¼
//   de_dir_f    �������Ŀ¼
//   filelist_f  �ļ��б�
//	 mainHwnd    ��������
encrypt::encrypt(HWND mainHwnd, string key_f, Fvector filelist_f, string en_dir_f = "", string de_dir_f = "")
{
	g_mainHnd = mainHwnd;   //��������
	key = key_f;            //��Կ
	en_dir = en_dir_f;      //�������Ŀ¼
	de_dir = de_dir_f;      //�������Ŀ¼
	filelist = filelist_f;  //�ļ��б�	
}

//��������
encrypt::~encrypt(void)
{
	//�ͷŴ���ļ��б�������ռ�ڴ�
	//Fvector().swap(filelist);  
}

//���ܺ���
void encrypt::desEncrypt()
{
	//��ʼ���ٽ�������
	InitializeCriticalSection(&g_cs);

	//���������߳����ڼ��ܲ���
	CWinThread *pThread_1, *pThread_2;

	pThread_1 = AfxBeginThread(EnThread, this);   //��ʼ�����߳�1
	g_EnHnd_1 = pThread_1 ->m_hThread;            //��ȡ�߳�1���

	pThread_2 = AfxBeginThread(EnThread, this);   //��ʼ�����߳�2
	g_EnHnd_2 = pThread_2 ->m_hThread;            //��ȡ�߳�2���
}

//���ܺ���
void encrypt::desDecrypt()
{

	//�����ļ��б���н��ܲ���
	for(unsigned int i = 0; i < filelist.size(); i++)
	{
		//���Ŀ¼��ʱ����
		string dir_temp;
		//�����ļ�·��ת������
		pathTransform(de_dir, filelist[i], dir_temp);
		
		//����des���������
		//desencryption des;
		//���ý��ܺ���
		//des.DES_Decrypt(filelist[i].file.c_str(), key.c_str(), dir_temp.c_str());

		RC4 rc;
		rc.Decrypt(filelist[i].file.c_str(), key.c_str(), dir_temp.c_str());
	}
}


//�ļ�·��ת������
//  dir        ���·��
//  fileinfo   �������ļ���Ϣ
//  dir_temp   ת�����ļ�·��
void pathTransform(string dir, File fileinfo, string &dir_temp)
{
		if(dir != "")  
		{
			//�����Ŀ¼��ֵ����ʱ����
			dir_temp = dir;

			////���Ŀ¼��Ϊ�������'\'
			//dir_temp += "\\";
			////�����Ŀ¼������ļ���
			//int pos = filelist[i].file.find_last_of('\\');
			//dir_temp += filelist[i].file.substr(pos + 1);

			//����Ҫ���ֵ��ļ�Ŀ¼�ṹ��ʼλ��
			int pos = fileinfo.from.size();
			//����ļ�Ŀ¼�ṹ���ļ���
			dir_temp += fileinfo.file.substr(pos);
			//�����ļ���Ŀ¼�ṹ�����Ŀ¼�������򴴽�Ŀ¼
			MakeSureDirectoryPathExists(dir_temp.c_str());
		}
		else
		{
			//���Ŀ¼Ϊ������ԴĿ¼���������������ļ�
			dir_temp = fileinfo.file;
			int pos = fileinfo.file.find_last_of('.');
			dir_temp.insert(pos, "����");
		}
}


UINT EnThread(LPVOID param)
{
	//�̵߳�ǰҪ������ļ��б�����
	int index;

	while(1)
	{	
		//�ٽ�������������Դ
		EnterCriticalSection(&g_cs);
        
		if(g_index == filelist.size())
		{
			//�����̷߳��������Ϣ
			::PostMessage(g_mainHnd, WM_FINISHMSG, 0, 0);

			//�ٽ�������
			LeaveCriticalSection(&g_cs);
			return false;      //�˳�����
		}

		index = g_index++;   //��ù���������ֵ,�����м�1����

		//�ٽ�������
		LeaveCriticalSection(&g_cs);

		//���Ŀ¼��ʱ����
		string dir_temp;
		//�����ļ�·��ת������
		pathTransform(en_dir, filelist[index], dir_temp);

		//����des���������
		desencryption des;
		//���ü��ܺ���
		des.DES_Encrypt(filelist[index].file.c_str(), key.c_str(), dir_temp.c_str());
		//RC4 rc;
		//rc.Decrypt(filelist[index].file.c_str(), key.c_str(), dir_temp.c_str());

		
	}

	return true;
}