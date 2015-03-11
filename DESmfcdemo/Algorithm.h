#include "desencryption.h"
#include "RC4.h"
#include "AES.h"

//�����㷨����
class BaseAlg
{
	public:
		//���ܺ���
		virtual void Encrypt(const char *plainFile, const char *keyStr,const char *cipherFile) = 0;
		//���ܺ���
		virtual void Decrypt(const char *cipherFile, const char *keyStr,const char *plainFile) = 0;
};

//DES�����㷨��
class DESAlg : public BaseAlg
{
	public:
		//���ܺ���
		virtual void Encrypt(const char *plainFile, const char *keyStr,const char *cipherFile)
		{
			//����des���������
			desencryption des;
			//���ü��ܺ���
			des.DES_Encrypt(plainFile, keyStr, cipherFile);
		}

		//���ܺ���
		virtual void Decrypt(const char *cipherFile, const char *keyStr,const char *plainFile)
		{
			//����des���������
			desencryption des;
			//���ý��ܺ���
			des.DES_Decrypt(cipherFile, keyStr, plainFile);
		}
};


//RC4�����㷨��
class RC4Alg : public BaseAlg
{
	public:
		//���ܺ���
		virtual void Encrypt(const char *plainFile, const char *keyStr,const char *cipherFile)
		{
			//����RC4���������
			RC4 rc4;
			//���ü��ܺ���
			rc4.Encrypt(plainFile, keyStr, cipherFile);
		}

		//���ܺ���
		virtual void Decrypt(const char *cipherFile, const char *keyStr,const char *plainFile)
		{
			//����RC4���������
			RC4 rc4;
			//���ý��ܺ���
			rc4.Decrypt(cipherFile, keyStr, plainFile);
		}
};


//AES�����㷨��
class AESAlg : public BaseAlg
{
	public:
		//���ܺ���
		virtual void Encrypt(const char *plainFile, const char *keyStr,const char *cipherFile)
		{
			//����AES���������
			AES aes;
			//���ü��ܺ���
			aes.Encrypt_File(plainFile, (unsigned char*)keyStr, cipherFile);
		}

		//���ܺ���
		virtual void Decrypt(const char *cipherFile, const char *keyStr,const char *plainFile)
		{
			//����AES���������
			AES aes;
			//���ý��ܺ���
			aes.Decrypt_File(cipherFile, (unsigned char*)keyStr, plainFile);
		}
};