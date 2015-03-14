#include "StdAfx.h"
#include "task.h"
#include <ImageHlp.h>

string key;         //��Կ
string en_dir;      //�������Ŀ¼
string de_dir;      //�������Ŀ¼
Fvector filelist;   //�ļ��б�
int alg;            //�ӽ����㷨����
int type;           //�������ͣ�0-һ�����ܣ�1-�������ܣ�2-����

CRITICAL_SECTION g_cs;    //�ٽ�������
int g_index;          //ȫ����Դ����¼�ļ��б����Ѵ��������
static HWND g_mainHnd;    //��������
static HANDLE g_Hnd_1;   //�߳�һ���
static HANDLE g_Hnd_2;   //�̶߳����


//���캯��,��ʼ����Ա����
//	 key_f       ��Կ
//   en_dir_f    �������Ŀ¼
//   de_dir_f    �������Ŀ¼
//   filelist_f  �ļ��б�
//	 mainHwnd    ��������
task::task(HWND mainHwnd, string key_f, Fvector filelist_f, string en_dir_f = "", string de_dir_f = "")
{
	g_mainHnd = mainHwnd;   //��������
	key = key_f;            //��Կ
	en_dir = en_dir_f;      //�������Ŀ¼
	de_dir = de_dir_f;      //�������Ŀ¼
	filelist = filelist_f;  //�ļ��б�	
}


//��������
task::~task(void)
{
	//�ͷŴ���ļ��б�������ռ�ڴ�
	//Fvector().swap(filelist);  
}


//���ܺ���
// alg		�ӽ����㷨���ͣ�0-DES��1-RC4��
// type		�������ͣ�0-���ܣ�1-����
void task::DoTask(int alg_f, int type_f)
{
	//�ӽ����㷨���͸�ֵ
	alg = alg_f;
	//�������͸�ֵ
	type = type_f;
	//��ʼ���ٽ�������
	InitializeCriticalSection(&g_cs);
	//��ʼ���ٽ�����Դ
	g_index = 0;

	//���������߳����ڼ��ܲ���
	CWinThread *pThread_1, *pThread_2;

	pThread_1 = AfxBeginThread(EnThread, this);   //��ʼ�����߳�1
	g_Hnd_1 = pThread_1 ->m_hThread;            //��ȡ�߳�1���

	pThread_2 = AfxBeginThread(EnThread, this);   //��ʼ�����߳�2
	g_Hnd_2 = pThread_2 ->m_hThread;            //��ȡ�߳�2���
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
			//����Ҫ���ֵ��ļ�Ŀ¼�ṹ��ʼλ��
			int pos = fileinfo.from.size();
			
			if(pos == 0)    //��ѡ���ļ�����
			{
				//�ҵ�·�����ļ�����ʼλ��
				pos = fileinfo.file.find_last_of('\\');
				//����ļ���
				dir_temp += fileinfo.file.substr(pos);
			}
			else			//��ѡ��Ŀ¼����
			{
				//����ļ�Ŀ¼�ṹ���ļ���
				dir_temp += fileinfo.file.substr(pos);
				//�����ļ���Ŀ¼�ṹ�����Ŀ¼�������򴴽�Ŀ¼
				MakeSureDirectoryPathExists(dir_temp.c_str());
			}
		}
		else
		{
			//���Ŀ¼Ϊ������ԴĿ¼���������������ļ�
			dir_temp = fileinfo.file;
		}
		//�޸ļ����ļ���չ��
		int posext = dir_temp.find_last_of('.');
		//ȥ��ԭ�ļ�����չ��
		dir_temp = dir_temp.substr(0, posext);
		//��Ӷ���õļ����ļ���չ��
		if(type == 2)  //���ܲ���ʱ��չ��Ϊ.fess
			dir_temp += ".fess";
		else
			dir_temp += ".fes";
}


//�ӽ����̺߳���
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
		//��ù���������ֵ,�����м�1����
		index = g_index++;
		//�ٽ�������
		LeaveCriticalSection(&g_cs);

		//���Ŀ¼��ʱ����
		string dir_temp;

		//�����㷨�������
		BaseAlg *base = NULL;

		switch(type)
		{
		case iEncrypt:		//һ������
			//ת������Ӧ�㷨�����
			base = CreateAlg(base, alg);
		switch(type)
		case 0:		//һ������
			//�����ļ�·��ת������
			pathTransform(en_dir, filelist[index], dir_temp);
			//���ü��ܺ���
			base->Encrypt(filelist[index].file, key.c_str(), dir_temp);
			break;

		case  iSecEncrypt:	//��������
			//ת������Ӧ�㷨�����
			base = CreateAlg(base, alg);
			//�����ļ�·��ת������
			pathTransform(en_dir, filelist[index], dir_temp);
			//���ö������ܺ���
			base->SecondEncrypt(filelist[index].file, key.c_str(), dir_temp);
			break;

		case iDecrypt:		//����
			{
				//�������ļ���������
				int alg_temp;
				//�������ļ�ԭ��չ��
				string ext_temp = "";
				//�������ļ�ԭMD5ֵ
				string md5str_temp = "";
				//��ȡ�������ļ���Ϣ
				ReadInfo(alg_temp, ext_temp, md5str_temp, filelist[index].file);

				//ת������Ӧ�㷨�����
				base = CreateAlg(base, alg_temp);
				//�����ļ�·��ת������
				pathTransform(de_dir, filelist[index], dir_temp);

				//�����ļ���������ļ���չ��Ϊ�ļ�ԭ��չ��
				int posext = dir_temp.find_last_of('.');
				//ȥ��ԭ�ļ�����չ��
				dir_temp = dir_temp.substr(0, posext + 1);
				dir_temp += ext_temp;
				//���ý��ܺ���
				base->Decrypt(filelist[index].file, key.c_str(), dir_temp);

				//���ܺ����¼���MD5ֵ
				string md5str = "";
				MD5_Read(dir_temp.c_str(),md5str);
				//�Ƚ�����MD5ֵ
				if(md5str_temp.compare(md5str) != 0)
				{
					//����MDֵ����ͬ������Ӧ����
					CString msg;
					msg.Format("%s �ļ���������", dir_temp);
					AfxMessageBox(msg);
				}
				break;
			}
		default:
			break;
		}
	}
	return true;
}

//�㷨��ת������
// base		�㷨�������
// alg		�ӽ����㷨����
BaseAlg *CreateAlg(BaseAlg *base, int alg)
{
	switch(alg)
	{
		//DES�ӽ���
	case iDES:
		base = new DESAlg;
		break;
		//RC4�ӽ���
	case iRC4:
		//base = new RC4Alg;
		break;
	case iAES:
		//AES�ӽ���
		//base = new AESAlg;
		break;
	default:
		break;
	}
	//���ض���ָ��
	return base;
}