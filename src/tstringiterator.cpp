#include "tstringiterator.hpp"

/****************************************************************************
* Name     : 构造函数
* Describe : 后续初始化
* parameter: 无
* @return  : 无
* date     : 2020-06-28 
*/

tstringiterator::tstringiterator() {}

/****************************************************************************
* Name     : 初始化构造函数
* Describe : 初始化迭代器
* parameter: char *ptstr
* @return  : 无
* date     : 2020-06-28 
*/
tstringiterator::tstringiterator(char *ptstr)
{
    _ptstr = ptstr;
}

/****************************************************************************
* Name     : 
* Describe : 迭代器赋值
* parameter: const tstringiterator &iter
* @return  : tstringiterator &
* date     : 2020-06-28 
*/
tstringiterator &tstringiterator::operator=(const tstringiterator &iter)
{
    this->_ptstr = iter._ptstr;
    return *this;
}

/****************************************************************************
* Name     : 
* Describe : 迭代器判断是否不等于
* parameter: const tstringiterator &iter
* @return  : bool
* date     : 2020-06-28 
*/

bool tstringiterator::operator!=(const tstringiterator &iter)
{
    return _ptstr != iter._ptstr;
}

/****************************************************************************
* Name     : 
* Describe : 迭代器判断是否等于
* parameter: const tstringiterator &iter
* @return  : bool
* date     : 2020-06-28 
*/

bool tstringiterator::operator==(const tstringiterator &iter)
{
    return _ptstr == iter._ptstr;
}

/****************************************************************************
    * Name     : 
    * Describe : 前缀自加
    * parameter: 
    * @return  : tstringiterator &
    * date     : 2020-06-28 
    */

tstringiterator &tstringiterator::operator++()
{
    _ptstr++;
    return *this;
}

/****************************************************************************
    * Name     : 
    * Describe : 后缀自加
    * parameter: 
    * @return  : tstringiterator
    * date     : 2020-06-28 
    */

tstringiterator tstringiterator::operator++(int)
{
    tstringiterator tmp = *this;
    _ptstr++;
    return tmp;
}

/****************************************************************************
    * Name     : 
    * Describe : 取值
    * parameter: 
    * @return  : char
    * date     : 2020-06-28 
    */

char &tstringiterator::operator*()
{
    return *_ptstr;
}

/****************************************************************************
* Name     : 
* Describe : 迭代器+数字
* parameter: int
* @return  : tstringiterator
* date     : 2020-06-28 
*/

tstringiterator tstringiterator::operator+(int temp)
{
    tstringiterator tempiter = this->_ptstr + temp;
    return tempiter;
}

/****************************************************************************
* Name     : 
* Describe : 迭代器-
* parameter: int
* @return  :  tstringiterator
* date     : 2020-06-28 
*/
tstringiterator tstringiterator::operator-(int temp)
{
    tstringiterator tempiter = this->_ptstr - temp;
    return tempiter;
}

/****************************************************************************
* Name     : 
* Describe : Compare two forward iterator positions, if the former is less than the latter, the latter is closer to the end
* 描     述:比较两个正向迭代器位置，如果前者小于后者，则后者正向迭代器更接近末尾
* parameter: const tstringiterator &iter
* @return  : bool
* date     : 2020-07-02 
*/

bool tstringiterator::operator<(const tstringiterator &iter)
{
    if (this->_ptstr - iter._ptstr < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/****************************************************************************
* Name     : 
* Describe : Comparing two forward iterator positions, if the former is greater than the latter, the former forward iterator is closer to the end
* 描     述:比较两个正向迭代器位置，如果前者大于后者，则前者正向迭代器更接近末尾
* parameter: const tstringiterator &iter
* @return  : bool
* date     : 2020-07-02 
*/

bool tstringiterator::operator>(const tstringiterator &iter)
{
    if (this->_ptstr - iter._ptstr > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/****************************************************************************
* Name     : 
* Describe : Compares two forward iterator positions and returns "true" if the former is less than or equal to the latter
* 描     述:比较两个正向迭代器位置，如果前者小于等于于后者，则返回“true”
* parameter: const tstringiterator &iter
* @return  : bool
* date     : 2020-07-02 
*/

bool tstringiterator::operator<=(const tstringiterator &iter)
{
    if (this->_ptstr - iter._ptstr <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/****************************************************************************
* Name     : 
* Describe : Compares two forward iterator positions and returns "true" if the former is greater than or equal to the latter
* 描     述:比较两个正向迭代器位置，如果前者大于等于于后者，则返回“true”
* parameter: const tstringiterator &iter
* @return  : bool
* date     : 2020-07-02 
*/

bool tstringiterator::operator>=(const tstringiterator &iter)
{
    if (this->_ptstr - iter._ptstr >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/****************************************************************************
* Name     : base()
* Describe : 返回内容指针
* parameter: 无
* @return  : char*
* date     : 2020-06-28 
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
* Name     : 
* Describe : 私有利用指针初始化
* parameter: char *temp
* @return  : 无
* date     : 2020-06-28 
*/
reverse_tstringiterator::reverse_tstringiterator(char *temp)
{
    this->_ptstr = temp;
}

/****************************************************************************
* Name     : 构造函数
* Describe : 后续初始化
* parameter: 无
* @return  : 无
* date     : 2020-06-28 
*/

reverse_tstringiterator::reverse_tstringiterator() {}

/****************************************************************************
* Name     : 初始化构造函数
* Describe : 初始化构造函数
* parameter: const reverse_tstringiterator &iter
* @return  : reverse_tstringiterator &
* date     : 2020-06-28 
*/
reverse_tstringiterator::reverse_tstringiterator(tstringiterator &iter)
{
    this->_ptstr = iter.base();
}

/****************************************************************************
* Name     : 
* Describe : 迭代器赋值
* parameter: const tstringiterator &iter
* @return  : tstringiterator &
* date     : 2020-06-28 
*/
reverse_tstringiterator &reverse_tstringiterator::operator=(const reverse_tstringiterator &iter)
{
    this->_ptstr = iter._ptstr;
    return *this;
}

/****************************************************************************
* Name     : 
* Describe : 迭代器判断是否不等于
* parameter: const reverse_tstringiterator &iter
* @return  : bool
* date     : 2020-06-28 
*/

bool reverse_tstringiterator::operator!=(const reverse_tstringiterator &iter)
{
    return _ptstr != iter._ptstr;
}

/****************************************************************************
* Name     : 
* Describe : 迭代器判断是否等于
* parameter: const reverse_tstringiterator &iter
* @return  : bool
* date     : 2020-06-28 
*/

bool reverse_tstringiterator::operator==(const reverse_tstringiterator &iter)
{
    return _ptstr == iter._ptstr;
}

/****************************************************************************
    * Name     : 
    * Describe : 前缀自加
    * parameter: 
    * @return  : reverse_tstringiterator &
    * date     : 2020-06-28 
    */

reverse_tstringiterator &reverse_tstringiterator::operator++()
{
    _ptstr--;
    return *this;
}

/****************************************************************************
    * Name     : 
    * Describe : 后缀自加
    * parameter: 
    * @return  : reverse_tstringiterator
    * date     : 2020-06-28 
    */

reverse_tstringiterator reverse_tstringiterator::operator++(int)
{
    reverse_tstringiterator tmp = *this;
    _ptstr--;
    return tmp;
}

/****************************************************************************
    * Name     : 
    * Describe : 取值
    * parameter: 
    * @return  : char
    * date     : 2020-06-28 
    */

char &reverse_tstringiterator::operator*()
{
    return *_ptstr;
}

/****************************************************************************
* Name     : 
* Describe : 迭代器+数字
* parameter: int
* @return  : reverse_tstringiterator
* date     : 2020-06-28 
*/

reverse_tstringiterator reverse_tstringiterator::operator+(int temp)
{
    reverse_tstringiterator tempiter = this->_ptstr - temp;
    return tempiter;
}

/****************************************************************************
* Name     : base()
* Describe : 返回正迭代器
* parameter: 无
* @return  : tstringiterator
* date     : 2020-06-28 
*/

tstringiterator reverse_tstringiterator::base()
{
    tstringiterator tempiter;
    tempiter = this->_ptstr + 1;
    return tempiter;
}

/****************************************************************************
* Name     : 
* Describe : 迭代器-
* parameter: int
* @return  : reverse_tstringiterator
* date     : 2020-06-28 
*/

reverse_tstringiterator reverse_tstringiterator::operator-(int temp)
{
    reverse_tstringiterator tempiter = this->_ptstr + temp;
    return tempiter;
}

/****************************************************************************
* Name     : 
* Describe : Comparing two reverse iterator positions, if the former is less than the latter, the address value of the former is larger, and this returns true
* 描     述:比较两个反向迭代器位置，如果前者小于后者，则前者者地址值更大，此时返回true
* parameter: const reverse_tstringiterator &iter
* @return  : bool
* date     : 2020-07-02 
*/

bool reverse_tstringiterator::operator<(const reverse_tstringiterator &iter)
{
    if (this->_ptstr - iter._ptstr > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/****************************************************************************
* Name     : 
* Describe : Compares two reverse iterator positions, returning true if the former is greater than the latter, and the latter has a larger address value
* 描     述:比较两个反向迭代器位置，如果前者大于后者，则后者地址值更大，此时返回true
* parameter: const reverse_tstringiterator &iter
* @return  : bool
* date     : 2020-07-02 
*/

bool reverse_tstringiterator::operator>(const reverse_tstringiterator &iter)
{
    if (this->_ptstr - iter._ptstr < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/****************************************************************************
* Name     : 
* Describe : Comparing two reverse iterator positions, if the former is less than or equal to the latter, then the former has a larger address value and returns true
* 描     述:比较两个反向迭代器位置，如果前者小于等于后者，则前者者地址值更大，此时返回true
* parameter: const reverse_tstringiterator &iter
* @return  : bool
* date     : 2020-07-02 
*/

bool reverse_tstringiterator::operator<=(const reverse_tstringiterator &iter)
{
    if (this->_ptstr - iter._ptstr >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/****************************************************************************
* Name     : 
* Describe : Compares two reverse iterator positions, and returns true if the former is greater than or equal to the latter
* 描     述:比较两个反向迭代器位置，如果前者大于等于后者，则后者地址值更大，此时返回true
* parameter: const reverse_tstringiterator &iter
* @return  : bool
* date     : 2020-07-02 
*/
bool reverse_tstringiterator::operator>=(const reverse_tstringiterator &iter)
{
    if (this->_ptstr - iter._ptstr <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}