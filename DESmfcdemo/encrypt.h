#pragma once
#include <string>
#include "common.h"

class encrypt
{
public:
	encrypt(string key, Fvector filelist, string en_dir, string de_dir);  //���캯������ʼ����Ա����
	~encrypt(void);  //��������
	void desEncrypt();  //���ܺ���
	void desDecrypt();  //���ܺ���

private:
	string key;  //��Կ
	string en_dir;  //�������Ŀ¼
	string de_dir;  //�������Ŀ¼
	Fvector filelist;  //�ļ��б�
};

