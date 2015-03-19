//存放通用的数据结构，如结构体
#include <string>
#include <vector>
using namespace std;

//自定义消息
#define WM_FINISHMSG WM_USER + 200	//整个加解密完成后发送的消息
#define WM_ONEFINISHMSG WM_USER + 201 //完成一个文件后发送的消息
#define WM_COUNTFINISHMSG WM_USER + 202  //完成一定字节后发送的消息

//File结构体，存放文件信息
struct File
{
	//文件来源，即用户选择的目录路径
	string from;
	//文件全路径
	string file;
};

//自定义存放File结构体容器Fvector
typedef vector<File> Fvector;

//文件信息缓冲大小
const int BUFMAX = 128;


