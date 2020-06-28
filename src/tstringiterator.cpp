#include "tstringiterator.hpp"

/****************************************************************************
* 函数名   : 构造函数
* 功    能 : 后续初始化
* 输    入 : 无
* 输    出 : 无
* 日    期 : 2020-06-28 
*/

tstringiterator::tstringiterator() {}

/****************************************************************************
* 函数名   : 初始化构造函数
* 功    能 : 初始化迭代器
* 输    入 : char *ptstr
* 输    出 : 无
* 日    期 : 2020-06-28 
*/
tstringiterator::tstringiterator(char *ptstr)
{
    _ptstr = ptstr;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 迭代器赋值
* 输    入 : const tstringiterator &iter
* 输    出 : tstringiterator &
* 日    期 : 2020-06-28 
*/
tstringiterator &tstringiterator::operator=(const tstringiterator &iter)
{
    this->_ptstr = iter._ptstr;
    return *this;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 迭代器判断是否不等于
* 输    入 : const tstringiterator &iter
* 输    出 : bool
* 日    期 : 2020-06-28 
*/

bool tstringiterator::operator!=(const tstringiterator &iter)
{
    return _ptstr != iter._ptstr;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 迭代器判断是否等于
* 输    入 : const tstringiterator &iter
* 输    出 : bool
* 日    期 : 2020-06-28 
*/

bool tstringiterator::operator==(const tstringiterator &iter)
{
    return _ptstr == iter._ptstr;
}

/****************************************************************************
    * 函数名   : 
    * 功    能 : 前缀自加
    * 输    入 : 
    * 输    出 : tstringiterator &
    * 日    期 : 2020-06-28 
    */

tstringiterator &tstringiterator::operator++()
{
    _ptstr++;
    return *this;
}

/****************************************************************************
    * 函数名   : 
    * 功    能 : 后缀自加
    * 输    入 : 
    * 输    出 : tstringiterator
    * 日    期 : 2020-06-28 
    */

tstringiterator tstringiterator::operator++(int)
{
    tstringiterator tmp = *this;
    _ptstr++;
    return tmp;
}

/****************************************************************************
    * 函数名   : 
    * 功    能 : 取值
    * 输    入 : 
    * 输    出 : char
    * 日    期 : 2020-06-28 
    */

char &tstringiterator::operator*()
{
    return *_ptstr;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 迭代器+数字
* 输    入 : int
* 输    出 : tstringiterator
* 日    期 : 2020-06-28 
*/

tstringiterator tstringiterator::operator+(int temp)
{
    tstringiterator tempiter = this->_ptstr + temp;
    return tempiter;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 迭代器-
* 输    入 : int
* 输    出 :  tstringiterator
* 日    期 : 2020-06-28 
*/
tstringiterator tstringiterator::operator-(int temp)
{
    tstringiterator tempiter = this->_ptstr - temp;
    return tempiter;
}

/****************************************************************************
* 函数名   : base()
* 功    能 : 返回内容指针
* 输    入 : 无
* 输    出 : char*
* 日    期 : 2020-06-28 
*/

char *tstringiterator::base()
{
    return this->_ptstr;
}

/*
*
*反向迭代器
*
*/
/****************************************************************************
* 函数名   : 
* 功    能 : 私有利用指针初始化
* 输    入 : char *temp
* 输    出 : 无
* 日    期 : 2020-06-28 
*/
reverse_tstringiterator::reverse_tstringiterator(char *temp)
{
    this->_ptstr = temp;
}

/****************************************************************************
* 函数名   : 构造函数
* 功    能 : 后续初始化
* 输    入 : 无
* 输    出 : 无
* 日    期 : 2020-06-28 
*/

reverse_tstringiterator::reverse_tstringiterator() {}

/****************************************************************************
* 函数名   : 初始化构造函数
* 功    能 : 初始化构造函数
* 输    入 : const reverse_tstringiterator &iter
* 输    出 : reverse_tstringiterator &
* 日    期 : 2020-06-28 
*/
reverse_tstringiterator::reverse_tstringiterator(tstringiterator &iter)
{
    this->_ptstr = iter.base();
}

/****************************************************************************
* 函数名   : 
* 功    能 : 迭代器赋值
* 输    入 : const tstringiterator &iter
* 输    出 : tstringiterator &
* 日    期 : 2020-06-28 
*/
reverse_tstringiterator &reverse_tstringiterator::operator=(const reverse_tstringiterator &iter)
{
    this->_ptstr = iter._ptstr;
    return *this;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 迭代器判断是否不等于
* 输    入 : const reverse_tstringiterator &iter
* 输    出 : bool
* 日    期 : 2020-06-28 
*/

bool reverse_tstringiterator::operator!=(const reverse_tstringiterator &iter)
{
    return _ptstr != iter._ptstr;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 迭代器判断是否等于
* 输    入 : const reverse_tstringiterator &iter
* 输    出 : bool
* 日    期 : 2020-06-28 
*/

bool reverse_tstringiterator::operator==(const reverse_tstringiterator &iter)
{
    return _ptstr == iter._ptstr;
}

/****************************************************************************
    * 函数名   : 
    * 功    能 : 前缀自加
    * 输    入 : 
    * 输    出 : reverse_tstringiterator &
    * 日    期 : 2020-06-28 
    */

reverse_tstringiterator &reverse_tstringiterator::operator++()
{
    _ptstr--;
    return *this;
}

/****************************************************************************
    * 函数名   : 
    * 功    能 : 后缀自加
    * 输    入 : 
    * 输    出 : reverse_tstringiterator
    * 日    期 : 2020-06-28 
    */

reverse_tstringiterator reverse_tstringiterator::operator++(int)
{
    reverse_tstringiterator tmp = *this;
    _ptstr--;
    return tmp;
}

/****************************************************************************
    * 函数名   : 
    * 功    能 : 取值
    * 输    入 : 
    * 输    出 : char
    * 日    期 : 2020-06-28 
    */

char &reverse_tstringiterator::operator*()
{
    return *_ptstr;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 迭代器+数字
* 输    入 : int
* 输    出 : reverse_tstringiterator
* 日    期 : 2020-06-28 
*/

reverse_tstringiterator reverse_tstringiterator::operator+(int temp)
{
    reverse_tstringiterator tempiter = this->_ptstr - temp;
    return tempiter;
}

/****************************************************************************
* 函数名   : base()
* 功    能 : 返回正迭代器
* 输    入 : 无
* 输    出 : tstringiterator
* 日    期 : 2020-06-28 
*/

tstringiterator reverse_tstringiterator::base()
{
    tstringiterator tempiter;
    tempiter = this->_ptstr + 1;
    return tempiter;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 迭代器-
* 输    入 : int
* 输    出 : reverse_tstringiterator
* 日    期 : 2020-06-28 
*/

reverse_tstringiterator reverse_tstringiterator::operator-(int temp)
{
    reverse_tstringiterator tempiter = this->_ptstr + temp;
    return tempiter;
}