#pragma once
#include <string>
#include "common.h"

#define WM_FINISHMSG WM_USER + 200	//�Զ�����Ϣ

//�����ļ�·��ת������
void pathTransform(string dir, File fileinfo, string &dir_temp);
UINT EnThread(LPVOID param);

class encrypt
{
public:
	encrypt(HWND mainHwnd, string key, Fvector filelist, string en_dir, string de_dir);  //���캯������ʼ����Ա����
	~encrypt(void);  //��������
	void desEncrypt();  //���ܺ���
	void desDecrypt();  //���ܺ���
protected:
	int a;
};

