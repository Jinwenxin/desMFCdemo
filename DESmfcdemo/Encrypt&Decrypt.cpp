#include "StdAfx.h"
#include "RC4.H"

#include<stdio.h> 
#include<string> 
#include<stdlib.h>   
#include<fstream>
#include<iostream>
#include<time.h>
using namespace std;









char rc4key[256];//�������Կ�� 
char s[256];//��ʼ���׶����õ�s��  


void swap(char si,char sj)//����si��sj��ֵ 
{
	char temp; 
	temp=si; 
	si=sj; 
	sj=temp; 
}   


void init_s(const char *key_data)//��ʼ��s�� 
{
	int i,j;  
	for(i=0;i<256;i++)//s���ȳ�ʼ��Ϊs[0]=0,s[1]=1,...,s[255]=255   
		s[i]=i;  
	for(i=0;i<256;i++)//��ʼ����Կ�� 
	{
		j=i%256;   
		rc4key[i]=key_data[j];  
	}   
	for(i=0,j=0;i<256;i++)//������Կ��rc4key���s��  
	{
		j=(rc4key[i]+s[i]+j)%256;   
		swap(s[i],s[j]);  
	} 
}   

 char *rc4( char buffer_data[],int buffer_len)//���ܺͽ��ܲ���
 {
	 int i; 
	 char *result1=( char *)malloc(sizeof(char)*buffer_len); 
	 for(i=0;i<buffer_len;i++)  //���������е������������Կ���н�����򪡾Ϳ��Խ��м��ܺͽ���   
	 {	
		 result1[i]=buffer_data[i]^s[i];//rc4key[i]; 
		 
	 } //���ؼ��ܺ�����Ļ���ܺ������
	 
	 return result1;
 }   

 void RC4::Encrypt(const char *r,const char *key,const char *w)
 {
    char *result=NULL; 
	fstream in,out;
	in.open(r,ios::binary|ios::in);
	out.open(w,ios::binary|ios::out|ios::app);




	if(!in)
		cout<<"��һ���ļ���ʧ��"<<endl;

	if(!out)
		cout<<"�ڶ����ļ���ʧ��"<<endl;


	char buf_data[256];
	init_s(key); 
	int buf_len=0;
	while(!in.eof())
	{		
	 	   
			in.read(buf_data,sizeof(buf_data));

			buf_len=in.gcount();

			if(buf_len == 256)
			{
				result=rc4(buf_data,sizeof(buf_data));
				out.write(result, sizeof(buf_data));
			}
			else
			{
				result=rc4(buf_data,buf_len);
				out.write(result, buf_len);
			}
	}
	delete result;

 }
 

 void RC4::Decrypt(const char *r,const char *key,const char *w)
 {
	char *result=NULL; 
	fstream in,out;
	in.open(r,ios::binary|ios::in);
	out.open(w,ios::binary|ios::out);


	if(!in)
		cout<<"��һ���ļ���ʧ��"<<endl;

	if(!out)
		cout<<"�ڶ����ļ���ʧ��"<<endl;


	char buf_data[256];
	int buf_len=0;
	while(!in.eof())
	{		 	   
			in.read(buf_data,sizeof(buf_data));
	
			buf_len=in.gcount();
			

			if(buf_len == 256)
			{
				result=rc4(buf_data,sizeof(buf_data));
				out.write(result, sizeof(buf_data));
			}
			else
			{
				result=rc4(buf_data,buf_len);
				out.write(result, buf_len);
			}
	}
	delete result;

 }
 
