#ifndef TSTRINGITERATOR_H_
#define TSTRINGITERATOR_H_

#include "tstring.hpp"
#include <iterator>
#include <iostream>
class tstring;
class tstringiterator;
class reverse_tstringiterator;
class tstringiterator : public std::iterator<std::input_iterator_tag, tstringiterator>
{
private:
    //获得源数据指针
    char *_ptstr;

public:
    //后续初始化
    tstringiterator();
    //使用指针初始化迭代器
    tstringiterator(char *ptstr);
    //迭代器赋值
    tstringiterator &operator=(const tstringiterator &iter);
    //迭代器判断是否不等于
    bool operator!=(const tstringiterator &iter);
    //迭代器判断是否等于
    bool operator==(const tstringiterator &iter);
    //前缀自加
    tstringiterator &operator++();
    //后缀自加
    tstringiterator operator++(int);
    //取值
    char &operator*();
    //迭代器+数字
    tstringiterator operator+(int temp);
    //迭代器-
    tstringiterator operator-(int temp);
    //返回内容指针
    char* base();
};

class reverse_tstringiterator : public std::reverse_iterator<std::iterator<std::input_iterator_tag, tstringiterator>>
{
private:
    //获得源数据指针
    char *_ptstr;
    //私有利用指针初始化
    reverse_tstringiterator(char *temp);

public:
    //后续初始化
    reverse_tstringiterator();
    //迭代器初始化
    reverse_tstringiterator(tstringiterator &iter);
    //迭代器赋值
    reverse_tstringiterator &operator=(const reverse_tstringiterator &iter);
    //迭代器判断是否不等于
    bool operator!=(const reverse_tstringiterator &iter);
    //迭代器判断是否等于
    bool operator==(const reverse_tstringiterator &iter);
    //前缀自加
    reverse_tstringiterator &operator++();
    //后缀自加
    reverse_tstringiterator operator++(int);
    //取值
    char &operator*();
    //迭代器+数字
    reverse_tstringiterator operator+(int temp);
    //返回正迭代器
    tstringiterator base();
    //迭代器-
    reverse_tstringiterator operator-(int temp);
};

#endif // !TSTRINGITERATOR_H_
