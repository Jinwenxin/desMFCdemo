#include "desencryption.h"
#include "RC4.h"
#include "AES.h"
#include <string>

//�����㷨����
const int iDES = 0;  //DES
const int iRC4 = 1;  //RC4
const int iAES = 2;  //AES
//��������
const int iEncrypt = 0;     //һ������
const int iSecEncrypt = 1;  //��������
const int iDecrypt = 2;  //����

//��������
string FindExt(string filepath);		   //�����ļ���չ������
bool IsSecondEncrypt(string filepath);	   //�ж��ļ��Ƿ񾭹��������ܺ���
void WriteInfo(int alg, string ext, string filepath);           //д���ļ���Ϣ����
int ReadInfo(int &alg, string &ext, string filepath);          //��ȡ�ļ���Ϣ����

//�����㷨����
class BaseAlg
{
	public:
		//���ܺ���
		virtual void Encrypt(string plainFile, const char *keyStr,string cipherFile) = 0;
		//�������ܺ���
		virtual void SecondEncrypt(string plainFile, const char *keyStr,string cipherFile) = 0;
		//���ܺ���
		virtual void Decrypt(string cipherFile, const char *keyStr,string plainFile) = 0;
};


//DES�����㷨��
class DESAlg : public BaseAlg
{
	public:
		//���ܺ���
		virtual void Encrypt(string plainFile, const char *keyStr,string cipherFile);
		//�������ܺ���
		virtual void SecondEncrypt(string plainFile, const char *keyStr,string cipherFile);
		//���ܺ���
		virtual void Decrypt(string cipherFile, const char *keyStr,string plainFile);
};


//RC4�����㷨��
class RC4Alg : public BaseAlg
{
	public:
		//���ܺ���
		virtual void Encrypt(string plainFile, const char *keyStr,string cipherFile);
		//�������ܺ���
		virtual void SecondEncrypt(string plainFile, const char *keyStr,string cipherFile);
		//���ܺ���
		virtual void Decrypt(string cipherFile, const char *keyStr,string plainFile);
};


//AES�����㷨��
class AESAlg : public BaseAlg
{
	public:
		//���ܺ���
		virtual void Encrypt(string plainFile, const char *keyStr,string cipherFile);
		//�������ܺ���
		virtual void SecondEncrypt(string plainFile, const char *keyStr,string cipherFile);
		//���ܺ���
		virtual void Decrypt(string cipherFile, const char *keyStr,string plainFile);
};