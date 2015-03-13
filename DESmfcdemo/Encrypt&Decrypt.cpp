#include "StdAfx.h"
#include "RC4.H"

#include<stdio.h> 
#include<string> 
#include<stdlib.h>   
#include<fstream>
#include<iostream>
#include<time.h>
using namespace std;









char rc4key[256];//随机化密钥表 
char s[256];//初始化阶段所用的s表  


void swap(char si,char sj)//交换si和sj的值 
{
	char temp; 
	temp=si; 
	si=sj; 
	sj=temp; 
}   


void init_s(const char *key_data)//初始化s表 
{
	int i,j;  
	for(i=0;i<256;i++)//s表先初始化为s[0]=0,s[1]=1,...,s[255]=255   
		s[i]=i;  
	for(i=0;i<256;i++)//初始化密钥表 
	{
		j=i%256;   
		rc4key[i]=key_data[j];  
	}   
	for(i=0,j=0;i<256;i++)//根据密钥表rc4key填充s表  
	{
		j=(rc4key[i]+s[i]+j)%256;   
		swap(s[i],s[j]);  
	} 
}   

 char *rc4( char buffer_data[],int buffer_len)//加密和解密操作
 {
	 int i; 
	 char *result1=( char *)malloc(sizeof(char)*buffer_len); 
	 for(i=0;i<buffer_len;i++)  //将缓冲区中的数据与随机密钥序列进行异或就可以进行加密和解密   
	 {	
		 result1[i]=buffer_data[i]^s[i];//rc4key[i]; 
		 
	 } //返回加密后的密文或解密后的明文
	 
	 return result1;
 }   

 void RC4::Encrypt(const char *r,const char *key,const char *w)
 {
    char *result=NULL; 
	fstream in,out;
	in.open(r,ios::binary|ios::in);
	out.open(w,ios::binary|ios::out|ios::app);




	if(!in)
		cout<<"第一个文件打开失败"<<endl;

	if(!out)
		cout<<"第二个文件打开失败"<<endl;


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
		cout<<"第一个文件打开失败"<<endl;

	if(!out)
		cout<<"第二个文件打开失败"<<endl;


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
 
