/****************************************************************************
* Copyright (C), windSnowLi
* 文件名: tstring.hpp
* 内容简述：tstring类主要声明
* 创建日期：2020-06-23 
*
* 文件历史：
* 版本号     日期         作者          说明
* v0.0.2    2020/06/23  windSnowLi      局部算法修改
*/

#ifndef TSTRING_H_
#define TSTRING_H_
#include <iostream>
#include <ostream>
#include <sstream>
#include <iterator>
#include "tstringiterator.hpp"
#include "Base64.hpp"
class tstringiterator;
class reverse_tstringiterator;
class tstring
{
private:
    //信息存储指针
    //char *tchar = NULL;
    //2020/06/23 windSnowLi 修改为默认值128
    char *tchar = new char[128];

    //字符串的长度记录
    size_t loglength = 0;
    //当前最大空间长度,默认128
    size_t max_length = 128;
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
    //转化为大写
    static void Strupr(char *str);

    //检查下一次需要的空间是否需要变动，如果变动，将老信息转存至新空间并将tstr新空间指针,否则不做改变,参数为要接受的新的字符串长度
    void checkNextMaxSizeSpace(size_t newstrsize);

public:
    //无参数
    tstring();
    //直接初始化
    tstring(const char *str);

    //使用另一个对象初始化
    tstring(const tstring &tstr);

    //使用标准库std::string初始化
    tstring(const std::string &stdstr);

    //析构函数
    ~tstring();
    //转化为char*
    const char *cstr();

    //比较两个对象是否相等
    bool compare(const tstring &tstr);
    //比较内容是否相等，忽略大小写
    bool compareIgnoreCase(const tstring &tstr);
    //获取字符串上某个字符
    char charAt(int index);
    //判断字符串是否为空
    bool isEmpty();
    //查找字符串，返回首个字符位置,size_t参数为返回后的位置偏移量
    size_t find(const char *targetstr, size_t move = 0);
    //将字符串全部转化为小写
    tstring &toLowerCase();
    //将字符串全部转化为大写
    tstring &toUpperCase();

    //返回对象内置的长度
    //2020/06/23 windSnowLi 将名称更改为getLength()
    size_t getLength();

    //清空函数，将字符串信息清空
    tstring &clear();
    //交换函数，交换两个tstring的信息
    void swap(tstring &tstr);
    //返回当前空间最大长度
    size_t getMaxSize();

    //摘要信息 MD5
    tstring getMD5();

    //替换指定字符串
    void replace(const char *targetstr, const char *newstr);

    //返回最后一个字符
    char back();

    //追加字符串
    tstring &append(const char *str);

    //获得BASE64编码
    tstring getEncodeBase64();

    //解BASE64码
    tstring getDecodeBase64();

    //迭代器相关
public:
    //定义正向迭代器类型
    typedef tstringiterator iterator;
    //起始迭代器
    iterator begin();
    //结尾迭代器
    iterator end();
    //定义反向迭代器类型
    typedef reverse_tstringiterator reverse_iterator;
    //返回反向迭代器起始迭代器
    reverse_iterator rbegin();
    //返回反向迭代器末尾迭代器
    reverse_iterator rend();

public:
    //重载=运行算符，使用=char*赋值
    tstring &operator=(const char *str);
    //重载+运算符，trstring结尾续加字符串
    tstring operator+(const char *str);
    //重载+运算符，trstring对象相加
    tstring operator+(const tstring &tstr);
    //重载+运算符，trstring加char
    tstring operator+(const char &tempch);
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
    //重载==运算符，判断两trstring对象是否相等
    bool operator==(const tstring &tstr);

    //重载=运算符,使用标准库std::string赋值
    tstring &operator=(const std::string &stdstr);

    //重载+运算符,=tstring+标准库std::string
    tstring operator+(const std::string &stdstr);

    //重载+=运算符,tstring+=标准库std::string赋值
    tstring &operator+=(const std::string &stdstr);

    //重载[]运算符，用于下标取值
    char &operator[](int move);

    //重载+=运算符，trstring加char
    tstring &operator+=(const char &ch);

    //友元ostream <<运算符
    friend std::ostream &operator<<(std::ostream &os, const tstring &tstr);
    //友元istream >>运算符
    friend std::istream &operator>>(std::istream &os, tstring &tstr);
};

//将基本类型参数内容转化为tstring
template <typename Type>
tstring toTstring(const Type &val);

/****************************************************************************
* 函数名   : 
* 功    能 : 将参数内容转化为tstring
* 输    入 : typename val
* 输    出 : tstring
* 日    期 : 2020-06-26 
*/

template <typename Type>
tstring toTstring(const Type &val)
{
    static_assert(std::is_arithmetic<Type>::value, "It's not a numeric type");
    std::stringstream ss;
    ss << val;
    tstring temptstr;
    ss >> temptstr;
    return temptstr;
}
#endif // !TSTRING_H_
