#include "StdAfx.h"
#include "Algorithm.h"

//DES�����㷨��

//DES���ܺ���
void DESAlg::Encrypt(string plainFile, const char *keyStr,string cipherFile)
{
	//����des���������
	desencryption des;
	//����������ļ�MD5ֵ
	string md5str = "";
	MD5_Read(plainFile.c_str(), md5str);
	//����д����Ϣ����
	WriteInfo(iDES, FindExt(plainFile), md5str, cipherFile);
	//���ü��ܺ���
	des.DES_Encrypt(plainFile.c_str(), keyStr, cipherFile.c_str());
}


//DES�������ܺ���
void DESAlg::SecondEncrypt(string plainFile, const char *keyStr,string cipherFile)
{
	//����des���������
	desencryption des;
	//���ü��ܺ���ʵ��һ������
	des.DES_Encrypt(plainFile.c_str(), keyStr, cipherFile.c_str());
	//����������ļ�MD5ֵ
	string md5str;
	MD5_Read(plainFile.c_str(),md5str);
	//����д����Ϣ����
	WriteInfo(iDES, FindExt(plainFile), md5str, cipherFile + "s");
	//���ü��ܺ���ʵ�ֶ������ܣ����޸ļ����ļ���׺
	des.DES_Encrypt(cipherFile.c_str(), keyStr, (cipherFile + "s").c_str());
	//ɾ��һ�������ļ�
	remove(cipherFile.c_str());
}


//DES���ܺ���
void DESAlg::Decrypt(string cipherFile, const char *keyStr,string plainFile)
{
	//����des���������
	desencryption des;
	if(IsSecondEncrypt(cipherFile))	//����ļ�������������
	{
		//���ý��ܺ���
		des.DES_Decrypt(cipherFile.c_str(), keyStr, cipherFile.substr(0, cipherFile.size() - 1).c_str());
		//ɾ�����������ļ�
		remove(cipherFile.c_str());
		//�޸��ļ�·��
		cipherFile = cipherFile.substr(0, cipherFile.size() - 1);
	}
	//���ý��ܺ���
	des.DES_Decrypt(cipherFile.c_str(), keyStr, plainFile.c_str());
	//ɾ��һ�������ļ�
	remove(cipherFile.c_str());
}


//RC4�����㷨��

//RC4���ܺ���
void RC4Alg::Encrypt(string plainFile, const char *keyStr,string cipherFile)
{
	//����RC4���������
	RC4 rc4;
	//����������ļ�MD5ֵ
	string md5str = "";
	MD5_Read(plainFile.c_str(), md5str);
	WriteInfo(iRC4, FindExt(plainFile), md5str, cipherFile);
	//���ü��ܺ���
	rc4.Encrypt(plainFile.c_str(), keyStr, cipherFile.c_str());
}


//RC4�������ܺ���
void RC4Alg::SecondEncrypt(string plainFile, const char *keyStr,string cipherFile)
{

}


//RC4���ܺ���
void RC4Alg::Decrypt(string cipherFile, const char *keyStr,string plainFile)
{
	//����RC4���������
	RC4 rc4;
	//���ý��ܺ���
	rc4.Decrypt(cipherFile.c_str(), keyStr, plainFile.c_str());
	//ɾ��һ�������ļ�
	remove(cipherFile.c_str());
}


//AES�����㷨��

//AES���ܺ���
void AESAlg::Encrypt(string plainFile, const char *keyStr,string cipherFile)
{
	//����AES���������
	AES aes;
	//���ü��ܺ���
	aes.Encrypt_File(plainFile.c_str(), (unsigned char*)keyStr, cipherFile.c_str());
}


//AES���ܺ���
void AESAlg::Decrypt(string cipherFile, const char *keyStr,string plainFile)
{
	//����AES���������
	AES aes;
	//���ý��ܺ���
	aes.Decrypt_File(cipherFile.c_str(), (unsigned char*)keyStr, plainFile.c_str());
}


//�����ļ���չ������
// filepath    �ļ�·��
extern string FindExt(string filepath)
{
	//���ļ�·�����ҵ��ļ���չ��
	int pos = filepath.find_last_of('.');
	return filepath.substr(pos + 1);
}


//�ж��ļ��Ƿ񾭹��������ܺ���
// filepath		�������ļ��ļ�·��
extern bool IsSecondEncrypt(string filepath)
{
	//��ȡ�ļ���չ��
	string ext = FindExt(filepath);

	//�ж��ļ���չ��
	if(ext.compare("fess") == 0)
		//�Ƕ��������ļ�
		return true;
	//���Ƕ��������ļ�
	return false;
}


//д���ļ���Ϣ����
// alg          �����㷨����
// ext          �ļ���չ��
// filepath		�ļ�·��
extern void WriteInfo(int alg, string ext, string md5str, string filepath)
{
	FILE *file;
	//�½���򿪴�д���ļ�
	if((file = fopen(filepath.c_str(),"wb")) == NULL)
		return;

	//�ļ���Ϣ������
	string buf;
	//�Ѽ������ͷ����ļ���Ϣ������
	buf.push_back('0' + alg);
	//������Ϣ�ָ��� 
	buf.push_back('*');
	//�����ļ���չ��
	buf += ext;
	//������Ϣ�ָ��� 
	buf.push_back('*');
	//����MD5ֵ
	buf += md5str;
	//����Ϣ�ָ������ʣ�೤���ַ�
	while(buf.size() < BUFMAX)
		buf.push_back('*');

	//���ļ���Ϣд���ļ�
	fwrite(buf.c_str(), sizeof(char), buf.size(), file);
	//�ر��ļ�
	fclose(file);
}


//��ȡ�ļ���Ϣ����
// alg			�����㷨����
// ext			�ļ���չ��
// filepath		�ļ�·�� 
void ReadInfo(int &alg, string &ext,string &md5str, string filepath)
{
	FILE *file;
	//�򿪴������ļ�
	if((file = fopen(filepath.c_str(),"rb")) == NULL)
		return;

	//�ļ���Ϣ������
	char buf[BUFMAX];
	//��ȡ�������ͼ��ָ���
	fread(buf, sizeof(char), BUFMAX, file);
	//���������͸�ֵ
	alg = buf[0] - '0';

	//��������չ����λ��ʼ
	int index = 2;
	//��ȡ�ļ���չ��,�����ָ�����ֹͣ��ȡ
	while(buf[index] != '*')
	{
		//����ȡ���ַ�������չ��������
		ext.push_back(buf[index++]);
	}

	//������MD5ֵ��λ��ʼ
	index++;
	//��ȡMD5ֵ,�����ָ�����ֹͣ��ȡ
	while(buf[index] != '*')
	{
		//����ȡ���ַ�����MD5ֵ������
		md5str.push_back(buf[index++]);
	}

	//�ر��ļ�
	fclose(file);
}