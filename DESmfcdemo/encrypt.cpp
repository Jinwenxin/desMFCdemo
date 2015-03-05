#include "StdAfx.h"
#include "encrypt.h"
#include "desencryption.h"
#include <ImageHlp.h>

//�����ļ�·��ת������
void pathTransform(string dir, File fileinfo, string &dir_temp);


//���캯��,��ʼ����Ա����
//	 key       ��Կ
//   en_dir    �������Ŀ¼
//   de_dir    �������Ŀ¼
//   filelist  �ļ��б�
encrypt::encrypt(string key, Fvector filelist, string en_dir = "", string de_dir = "")
{
	this ->key = key;  //��Կ
	this ->en_dir = en_dir;  //�������Ŀ¼
	this ->de_dir = de_dir;  //�������Ŀ¼
	this ->filelist = filelist;  //�ļ��б�
}

//��������
encrypt::~encrypt(void)
{
	//�ͷŴ���ļ��б�������ռ�ڴ�
	Fvector().swap(filelist);  
}

//���ܺ���
void encrypt::desEncrypt()
{
	//�����ļ��б���м��ܲ���
	for(unsigned int i = 0; i < filelist.size(); i++)
	{
		//���Ŀ¼��ʱ����
		string dir_temp;
		//�����ļ�·��ת������
		pathTransform(en_dir, filelist[i], dir_temp);

		//����des���������
		desencryption des;
		//���ü��ܺ���
		des.DES_Encrypt(filelist[i].file.c_str(), key.c_str(), dir_temp.c_str());
	}
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
		desencryption des;
		//���ý��ܺ���
		des.DES_Decrypt(filelist[i].file.c_str(), key.c_str(), dir_temp.c_str());
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
