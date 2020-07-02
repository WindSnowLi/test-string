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
    char *_ptstr = NULL;

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

    /*
    *  比较两个正向迭代器位置，如果前者小于后者，则后者正向迭代器更接近末尾
    *   Compare two forward iterator positions, if the former is less than the latter, the latter is closer to the end.
    */
    bool operator<(const tstringiterator &iter);

    /*
    *  比较两个正向迭代器位置，如果前者大于后者，则前者正向迭代器更接近末尾
    *   Comparing two forward iterator positions, if the former is greater than the latter, the former forward iterator is closer to the end.
    */
    bool operator>(const tstringiterator &iter);

    /*
    *  比较两个正向迭代器位置，如果前者小于等于于后者，则返回true
    *   Compares two forward iterator positions and returns "true" if the former is less than or equal to the latter
    */
    bool operator<=(const tstringiterator &iter);

    /*
    *  比较两个正向迭代器位置，如果前者大于等于于后者，则返回“true”
    *   Compares two forward iterator positions and returns "true" if the former is greater than or equal to the latter
    */
    bool operator>=(const tstringiterator &iter);
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

    /*
    *  比较两个反向迭代器位置，如果前者小于后者，则前者者地址值更大，此时返回true
    *  Comparing two reverse iterator positions, if the former is less than the latter, the address value of the former is larger, and this returns true
    */
    bool operator<(const reverse_tstringiterator &iter);

    /*
    *   比较两个反向迭代器位置，如果前者大于后者，则后者地址值更大，此时返回true
    *   Compares two reverse iterator positions, returning true if the former is greater than the latter, and the latter has a larger address value
    */
    bool operator>(const reverse_tstringiterator &iter);

    /*
    *  比较两个反向迭代器位置，如果前者小于等于后者，则前者者地址值更大，此时返回true
    *  Comparing two reverse iterator positions, if the former is less than or equal to the latter, then the former has a larger address value and returns true
    */
    bool operator<=(const reverse_tstringiterator &iter);

    /*
    *  比较两个反向迭代器位置，如果前者大于等于后者，则后者地址值更大，此时返回true
    *  Compares two reverse iterator positions, and returns true if the former is greater than or equal to the latter
    */
    bool operator>=(const reverse_tstringiterator &iter);
};
#endif // !TSTRINGITERATOR_H_
