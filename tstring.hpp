#ifndef TSTRING_H_
#define TSTRING_H_
#include <iostream>
#include <ostream>
class tstring
{
private:
    char *tchar = NULL;
    //获取字符串长度
    static size_t GetPCharLength(const char *str);
    //复制字符串
    static void Strcpy(char *newstr, const char *oldstr);
    //连接字符串
    static void Strcat(char *before, const char *after);
    //比较字符串是否相等
    static bool Strcmp(const char *str1, const char *str2);
    //将字符串转化为小写
    static void Strlwr(char *str);

public:
    //无参数
    tstring();
    //直接初始化
    tstring(const char *str);
    //使用另一个对象初始化
    tstring(const tstring &tstr);
    //析构函数
    ~tstring();
    //转化为char*
    const char *cstr();
    //获取对象得字符串长度
    size_t GetLength();
    //比较两个对象是否相等
    bool compare(const tstring &tstr);
    //比较内容是否相等，忽略大小写
    bool compareIgnoreCase(const tstring &tstr);
    //获取字符串上某个字符
    char charAt(int index);
    //判断字符串是否为空
    bool isEmpty();
    //查找字符串，返回首个字符位置,size_t参数为返回后的位置偏移量
    size_t find(const char *newstr, size_t move);
    //将字符串全部转化为小写
    tstring &toLowerCase();

public:
    //重载=运行算符，使用=char*赋值
    tstring &operator=(const char *str);
    //重载+运算符，trstring结尾续加字符串
    tstring operator+(const char *str);
    //重载+运算符，trstring对象相加
    tstring operator+(const tstring &tstr);
    //重载>>运算符，trstring对象赋值
    tstring &operator>>(tstring &tstr);
    //重载<<运算符，trstring对象赋值
    tstring &operator<<(tstring &tstr);
    //重载<<运算符，trstring对象赋值
    tstring &operator<<(const char *str);
    //重载+=运算符，trstring对象相加
    tstring &operator+=(const tstring &tstr);
    //重载+=运算符，trstring加char*
    tstring &operator+=(const char *str);
    //友元ostream <<运算符
    friend std::ostream &operator<<(std::ostream &os, const tstring &tstr);
    //友元istream >>运算符
    friend std::istream &operator>>(std::istream &os, tstring &tstr);
};

#endif // !TSTRING_H_
