//���ͨ�õ����ݽṹ����ṹ��
#include <string>
#include <vector>
using namespace std;

//�Զ�����Ϣ
#define WM_FINISHMSG WM_USER + 200	//�����ӽ�����ɺ��͵���Ϣ
#define WM_ONEFINISHMSG WM_USER + 201 //���һ���ļ����͵���Ϣ
#define WM_COUNTFINISHMSG WM_USER + 202  //���һ���ֽں��͵���Ϣ

//File�ṹ�壬����ļ���Ϣ
struct File
{
	//�ļ���Դ�����û�ѡ���Ŀ¼·��
	string from;
	//�ļ�ȫ·��
	string file;
};

//�Զ�����File�ṹ������Fvector
typedef vector<File> Fvector;

//�ļ���Ϣ�����С
const int BUFMAX = 128;


