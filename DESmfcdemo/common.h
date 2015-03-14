//存放通用的数据结构，如结构体
#include <string>
#include <vector>
using namespace std;

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
const int BUFMAX = 45;