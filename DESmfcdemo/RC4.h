//#include "common.h"



class RC4
{
public:
	void Encrypt(const char *r,const char *key,const char *w);

	void Decrypt(const char *r,const char *key,const char *w);
};