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
    /*

    -   获得源数据指针
    -   Source data pointer

    */
    char *_ptstr;

public:
    /*

    -   后续初始化
    -   Subsequent initialization

    */
    tstringiterator();

    /*

    -   使用指针初始化迭代器
    -   Initializes the iterator using a pointer

    */
    tstringiterator(char *ptstr);

    /*

    -   正向迭代器初始化
    -   Positive iterator initialization

    */
    tstringiterator &operator=(const tstringiterator &iter);

    /*

    -   迭代器判断是否不等于
    -   The iterator determines if not equal to

    */
    bool operator!=(const tstringiterator &iter);

    /*

    -   迭代器判断是否等于
    -   The iterator determines if is equal to

    */
    bool operator==(const tstringiterator &iter);

    /*

    -   前缀自加
    -   Prefix the add

    */
    tstringiterator &operator++();

    /*

    -   后缀自加
    -   Since the suffix added

    */
    tstringiterator operator++(int);

    /*

    -   取值
    -   The values   

    */
    char &operator*();

    /*

    -   迭代器+数字
    -   Iterator + number

    */
    tstringiterator operator+(int temp);

    /*

    -   迭代器-数字
    -   Iterator - number

    */
    tstringiterator operator-(int temp);

    /*

    -   返回源指针
    -   Return source pointer

    */
    char *base();
};

class reverse_tstringiterator : public std::reverse_iterator<std::iterator<std::input_iterator_tag, tstringiterator>>
{
private:
    /*

    -   获得源数据指针
    -   Source data pointer

    */
    char *_ptstr;

    /*

    -   私有利用指针初始化
    -   Private is initialized with a pointer

    */
    reverse_tstringiterator(char *temp);

public:
    /*

    -   后续初始化
    -   Subsequent initialization

    */
    reverse_tstringiterator();

    /*

    -   正向迭代器初始化
    -   Positive iterator initialization

    */
    reverse_tstringiterator(tstringiterator &iter);

    /*

    -   反向迭代器初始化
    -   Reverse iterator initialization

    */
    reverse_tstringiterator &operator=(const reverse_tstringiterator &iter);

    /*

    -   迭代器判断是否不等于
    -   The iterator determines if not equal to

    */
    bool operator!=(const reverse_tstringiterator &iter);

    /*

    -   迭代器判断是否等于
    -   The iterator determines if is equal to

    */
    bool operator==(const reverse_tstringiterator &iter);

    /*

    -   前缀自加
    -   Prefix the add

    */
    reverse_tstringiterator &operator++();

    /*

    -   后缀自加
    -   Since the suffix added

    */
    reverse_tstringiterator operator++(int);

    /*

    -   取值
    -   The values   

    */
    char &operator*();

    /*

    -   迭代器+数字
    -   Iterator + number

    */
    reverse_tstringiterator operator+(int temp);

    /*

    -   返回正迭代器
    -   Returns a positive iterator

    */
    tstringiterator base();

    /*

    -   迭代器-数字
    -   Iterator - number

    */
    reverse_tstringiterator operator-(int temp);
};
#endif // !TSTRINGITERATOR_H_
