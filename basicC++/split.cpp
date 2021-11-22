#include <iostream>
#include <vector>
#include <string.h>
#include <string>
#include <unistd.h>
using namespace std;
 
vector<string> split(const string& str, const string& delim) {
	vector<string> res;
	if("" == str) return res;
	//先将要切割的字符串从string类型转换为char*类型
	//char * strs = new char[str.length() + 1] ; //不要忘了
	//strcpy(strs, str.c_str()); 
    //char* strs = (char*) str.c_str();
    char* strs = const_cast<char*>(str.c_str());
    const char* d = delim.c_str();
 
	char *p = strtok(strs, d);
	while(p) {
		string s = p; //分割得到的字符串转换为string类型
		res.push_back(s); //存入结果数组
		p = strtok(NULL, d);
	}
 
	return res;
}
 
void test1() { //空字符串
	cout << "******test1****** "<<endl;
	string s = "";
	
	std::vector<string> res = split(s, " ");
	for (int i = 0; i < res.size(); ++i)
	{
		cout << res[i] <<endl;
	}
}
 
void test2() { //只有一个字符串
	cout << "******test2****** " <<endl;
	string s = "my";
	
	std::vector<string> res = split(s, " ");
	for (int i = 0; i < res.size(); ++i)
	{
		cout << res[i] <<endl;
	}
}
 
void test3() { //正常字符串
	cout << "******test3****** "<<endl;
	string s = "my  name nis lmm   ";//连续多个空格，空格会被过滤掉
	
	std::vector<string> res = split(s, " ");
	for (int i = 0; i < res.size(); ++i)
	{
		cout << res[i] <<endl;
	}
}

void splitStr() {
    char a[]="aaa||a||bbb||c||ee||";
    char* needle="||";

    //char *haystack=a;        //不能直接char *haystack="aaa||a||bbb||c||ee||"; 会报内存不能写错误
    a[0] = 'b';
    char* haystack = a;
    cout << haystack<<endl;
    char* buf = strstr( haystack, needle);
    while(buf != NULL )    {
       //在出现分隔符的位置设置结束符\0
        *buf = '\0';
        printf( "%s\n", haystack);
        haystack = buf + strlen(needle);
        buf = strstr( haystack, needle);
        } 
}

vector<string> split_find(const string line, const string sep)
{
	vector<string> buf;
	int temp=0;
	string::size_type pos=0;

    pos = line.find(sep, temp);
	while (pos!=string::npos)
	{
		buf.push_back(line.substr(temp, pos-temp));
		temp = pos + sep.size();
        pos = line.find(sep, temp);
	}
	buf.push_back(line.substr(temp, line.size() - temp));
	return buf;
}
 
int test_find()
{
	string line = "C:\\Users\\79476\\Desktop";
	vector<string> buf = split_find(line,"\\");
	typedef vector<string>::iterator itr;
	for (itr i = buf.begin(); i != buf.end(); i++)
	{
		cout << *i << endl;
	}
}
 
int main() {
 
	//test1();
	//test2();
	test_find();
	return 0;
}