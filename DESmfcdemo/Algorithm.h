#include "desencryption.h"
#include "RC4.h"
#include "AES.h"
#include <string>


//�����㷨����
class BaseAlg
{
	public:
		//���ܺ���
		virtual void Encrypt(string plainFile, string keyStr,string cipherFile) = 0;
		//�������ܺ���
		virtual void SecondEncrypt(string plainFile, string keyStr,string cipherFile) = 0;
		//���ܺ���
		virtual void Decrypt(string cipherFile, string keyStr,string plainFile) = 0;
};


//DES�����㷨��
class DESAlg : public BaseAlg
{
	public:
		//���ܺ���
		virtual void Encrypt(string plainFile, string keyStr,string cipherFile);
		//�������ܺ���
		virtual void SecondEncrypt(string plainFile, string keyStr,string cipherFile);
		//���ܺ���
		virtual void Decrypt(string cipherFile, string keyStr,string plainFile);
};


//RC4�����㷨��
class RC4Alg : public BaseAlg
{
	public:
		//���ܺ���
		virtual void Encrypt(string plainFile, string keyStr,string cipherFile);
		//���ܺ���
		virtual void Decrypt(string cipherFile, string keyStr,string plainFile);
};


//AES�����㷨��
class AESAlg : public BaseAlg
{
	public:
		//���ܺ���
		virtual void Encrypt(string plainFile, string keyStr,string cipherFile);
		//���ܺ���
		virtual void Decrypt(string cipherFile, string keyStr,string plainFile);
};