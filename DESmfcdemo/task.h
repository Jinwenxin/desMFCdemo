#pragma once
#include <string>
#include "Algorithm.h"


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

