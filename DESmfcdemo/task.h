#pragma once
#include <string>
#include "common.h"
#include "Algorithm.h"

#define WM_FINISHMSG WM_USER + 200	//�Զ�����Ϣ

//��������
void pathTransform(string dir, File fileinfo, string &dir_temp);        //�ļ�·��ת������
UINT EnThread(LPVOID param);											//�ӽ����̺߳���
BaseAlg *CreateAlg(BaseAlg *base, int alg);									//�ӽ����̺߳���

class task
{
public:
	task(HWND mainHwnd, string key, Fvector filelist, string en_dir, string de_dir);  //���캯������ʼ����Ա����
	~task(void);  //��������
	void DoTask(int alg, int type);  //������
};

