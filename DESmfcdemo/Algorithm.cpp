#include "StdAfx.h"
#include "Algorithm.h"

//��������
bool IsSecondEncrypt(string filepath);


//DES�����㷨��

//DES���ܺ���
void DESAlg::Encrypt(string plainFile, string keyStr,string cipherFile)
{
	//����des���������
	desencryption des;
	//���ü��ܺ���
	des.DES_Encrypt(plainFile.c_str(), keyStr.c_str(), cipherFile.c_str());
}


//DES�������ܺ���
void DESAlg::SecondEncrypt(string plainFile, string keyStr,string cipherFile)
{
	//����des���������
	desencryption des;
	//���ü��ܺ���ʵ��һ������
	des.DES_Encrypt(plainFile.c_str(), keyStr.c_str(), cipherFile.c_str());
	//���ü��ܺ���ʵ�ֶ������ܣ����޸ļ����ļ���׺
	des.DES_Encrypt(cipherFile.c_str(), keyStr.c_str(), (cipherFile + "s").c_str());
	//ɾ��һ�������ļ�
	remove(cipherFile.c_str());
}


//DES���ܺ���
void DESAlg::Decrypt(string cipherFile, string keyStr,string plainFile)
{
	//����des���������
	desencryption des;
	if(IsSecondEncrypt(cipherFile))	//����ļ�������������
	{
		//���ý��ܺ���
		des.DES_Decrypt(cipherFile.c_str(), keyStr.c_str(), cipherFile.substr(0, cipherFile.size() - 1).c_str());
		//ɾ�����������ļ�
		remove(cipherFile.c_str());
		//�޸��ļ�·��
		cipherFile = cipherFile.substr(0, cipherFile.size() - 1);
	}
	//���ý��ܺ���
	des.DES_Decrypt(cipherFile.c_str(), keyStr.c_str(), plainFile.c_str());
	//ɾ��һ�������ļ�
	//remove(cipherFile.c_str());
}


//RC4�����㷨��

//RC4���ܺ���
void RC4Alg::Encrypt(string plainFile, string keyStr,string cipherFile)
{
	//����RC4���������
	RC4 rc4;
	//���ü��ܺ���
	rc4.Encrypt(plainFile.c_str(), keyStr.c_str(), cipherFile.c_str());
}


//RC4���ܺ���
void RC4Alg::Decrypt(string cipherFile, string keyStr,string plainFile)
{
	//����RC4���������
	RC4 rc4;
	//���ý��ܺ���
	rc4.Decrypt(cipherFile.c_str(), keyStr.c_str(), plainFile.c_str());
}


//AES�����㷨��

//AES���ܺ���
void AESAlg::Encrypt(string plainFile, string keyStr,string cipherFile)
{
	//����AES���������
	AES aes;
	//���ü��ܺ���
	aes.Encrypt_File(plainFile.c_str(), (unsigned char*)keyStr.c_str(), cipherFile.c_str());
}


//AES���ܺ���
void AESAlg::Decrypt(string cipherFile, string keyStr,string plainFile)
{
	//����AES���������
	AES aes;
	//���ý��ܺ���
	aes.Decrypt_File(cipherFile.c_str(), (unsigned char*)keyStr.c_str(), plainFile.c_str());
}


//�ж��ļ��Ƿ񾭹��������ܺ���
// filepath		�������ļ��ļ�·��
extern bool IsSecondEncrypt(string filepath)
{
	//���ļ�·�����ҵ��ļ���չ��
	int pos = filepath.find_last_of('.');
	string ext = filepath.substr(pos + 1);

	//�ж��ļ���չ��
	if(ext.compare("fess") == 0)
		//�Ƕ��������ļ�
		return true;
	//���Ƕ��������ļ�
	return false;
}