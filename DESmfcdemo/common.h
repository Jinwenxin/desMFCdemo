//���ͨ�õ����ݽṹ����ṹ��
#include <string>
#include <vector>
using namespace std;

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
const int BUFMAX = 45;