#include <string>
#include <vector>
using namespace std;
#pragma once

//�궨��
#define PLAIN_FILE_OPEN_ERROR -1
#define KEY_FILE_OPEN_ERROR -2
#define CIPHER_FILE_OPEN_ERROR -3
#define OK 1

typedef char ElemType;  //���������������

class desencryption
{
public:
	desencryption(string key, vector<string> filelist, string en_dir, string de_dir);  //���캯������ʼ����Ա����
	~desencryption(void);  //��������
	void desEncrypt();  //���ܺ���
	void desDecrypt();  //���ܺ���

private:
	string key;  //��Կ
	string en_dir;  //�������Ŀ¼
	string de_dir;  //�������Ŀ¼
	vector<string> filelist;  //�ļ��б�
};

