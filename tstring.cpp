#include "tstring.hpp"
#include <iostream>

/****************************************************************************
* 函数名   : tstring()
* 功    能 : 无参数初始化
* 输    入 : 无
* 输    出 : 无
* 日    期 : 2020-06-18 
*/
tstring::tstring()
{
}

/****************************************************************************
* 函数名   : tstring(const char *str)
* 功    能 : 构造函数初始化
* 输    入 : const char *
* 输    出 : 无
* 日    期 : 2020-06-18 
*/
//2020/06/20 windSnowLi 顺带为对象内置长度赋值
tstring::tstring(const char *str)
{
    this->loglength = GetPCharLength(str);
    tchar = new char[this->loglength + 1];
    Strcpy(tchar, str);
}

/****************************************************************************
* 函数名   : 拷贝构造函数
* 功    能 : 复制对象
* 输    入 : tstring &tstr
* 输    出 : 无
* 日    期 : 2020-06-18 
*/
//2020/06/20 windSnowLi 顺带为对象内置长度赋值
tstring::tstring(const tstring &tstr)
{
    this->loglength = GetLength();
    this->tchar = new char[this->loglength + 1];
    Strcpy(this->tchar, tstr.tchar);
}

/****************************************************************************
* 函数名   : 析构函数
* 功    能 : 释放对象时释放所属资源
* 输    入 : 无
* 输    出 : 无
* 日    期 : 2020-06-18 
*/
tstring::~tstring()
{
    if (this->tchar != NULL)
    {
        delete this->tchar;
        this->tchar = NULL;
    }
}

size_t tstring::GetPCharLength(const char *str)
{
    size_t length = 0;
    if (str != NULL)
    {
        while (*str != '\0')
        {
            length++;
            str++;
        }
    }
    return length;
}

//2020/6/19 windSnowLi 加入指针是否为空的判断
void tstring::Strcpy(char *newstr, const char *oldstr)
{
    if (oldstr != NULL)
    {
        while (*oldstr != '\0')
        {
            *newstr = *oldstr;
            newstr++;
            oldstr++;
        }
    }
    *newstr = '\0';
}

/****************************************************************************
    * 函数名   : cstr
    * 功    能 : 获取char*指针
    * 输    入 : 
    * 输    出 : char*
    * 日    期 : 2020-06-18 
    */
const char *tstring::cstr()
{
    return tchar;
}

/****************************************************************************
* 函数名   : Strcat
* 功    能 : 连接字符串
* 输    入 : char *before, char *after
* 输    出 : 无
* 日    期 : 2020-06-18 
*/
//2020/6/19 windSnowLi 加入指针是否为空的判断
void tstring::Strcat(char *before, const char *after)
{
    if (after != NULL && before != NULL)
    {
        while (*before != '\0')
        {
            before++;
        }

        while (*after != '\0')
        {
            *before = *after;
            before++;
            after++;
        }
        *before = '\0';
    }
}

/****************************************************************************
* 函数名   : GetLength()
* 功    能 : 获取对象得字符串长度
* 输    入 : 无
* 输    出 : size_t
* 日    期 : 2020-06-18 
*/

size_t tstring::GetLength()
{
    return GetPCharLength(this->cstr());
}

/****************************************************************************
* 函数名   : compare
* 功    能 : 比较两个对象是否相等
* 输    入 : const tstring &tstr
* 输    出 : bool
* 日    期 : 2020-06-18 
*/

bool tstring::compare(const tstring &tstr)
{
    return Strcmp(this->cstr(), tstr.tchar);
}

/****************************************************************************
* 函数名   : equalsIgnoreCase
* 功    能 : 比较内容是否相等，忽略大小写
* 输    入 : const tstring &tstr
* 输    出 : bool
* 日    期 : 2020-06-18 
*/
//2020/6/19 windSnowLi 加入指针是否为空的判断
bool tstring::compareIgnoreCase(const tstring &tstr)
{
    char *tempstr1 = this->tchar;
    char *tempstr2 = tstr.tchar;
    //如果指针有空的，则不进行大小写判断
    if (this->tchar != NULL && tstr.tchar != NULL)
    {
        while (*tempstr1 != '\0' && *tempstr2 != '\0')
        {
            //将在字母区域的转化为小写字母进行遍历比较，如果其中有一个不通，那说明字符串忽略大小写不同
            if (((*tempstr1 <= 'Z' && *tempstr1 >= 'A') ? *tempstr1 - 'A' + 'a' : *tempstr1) != ((*tempstr2 <= 'Z' && *tempstr2 >= 'A') ? *tempstr2 - 'A' + 'a' : *tempstr2))
            {
                return false;
            }
            tempstr1++;
            tempstr2++;
        }
        //循环遍历完成，并且目前全部相同，如果两个字符串不是都读到了结尾终止符，说明有一个还未比较完成，那就是忽略大小写不同
        //如果指针都为空也视为相等
        if ((this->tchar == NULL && tstr.tchar == NULL) || (*tempstr1 == '\0' && *tempstr2 == '\0'))
        {
            return true;
        }
    }
    return false;
}

/****************************************************************************
* 函数名   : Strcmp
* 功    能 : 比较字符串是否相等
* 输    入 : const char *str1, const char *str2
* 输    出 : bool
* 日    期 : 2020-06-18 
*/
//2020/6/19 windSnowLi 加入指针是否为空的判断
bool tstring::Strcmp(const char *str1, const char *str2)
{
    if ((str1 != NULL) && (str2 != NULL))
    {
        if ((*str1 != '\0') && (*str2 != '\0'))
        {
            return true;
        }
        while ((*str1 != '\0') && (*str2 != '\0'))
        {
            if (*str1 - *str2 != 0)
            {
                return false;
            }
        }
    }
    //如果指针都为空也视为相等
    else if (str1 == NULL && str2 == NULL)
    {
        return true;
    }
    return true;
}

/****************************************************************************
* 函数名   : Strlwr
* 功    能 : 将字符串转化为小写
* 输    入 : char *str
* 输    出 : 无
* 日    期 : 2020-06-18 
*/
//2020/6/19 windSnowLi 加入指针是否为空的判断
void tstring::Strlwr(char *str)
{
    if (str != NULL)
    {
        while (*str != '\0')
        {
            if (*str <= 'Z' && *str >= 'A')
            {
                *str -= 'A' - 'a';
            }
            str++;
        }
    }
}

/****************************************************************************
* 函数名   : Strupr
* 功    能 :转化为大写 
* 输    入 : char *str
* 输    出 : 无
* 日    期 : 2020-06-20 
*/

void tstring::Strupr(char *str)
{
    if (str != NULL)
    {
        while (*str != '\0')
        {
            if (*str <= 'z' && *str >= 'a')
            {
                *str -= 'a' - 'A';
            }
            str++;
        }
    }
}

/****************************************************************************
* 函数名   : charAt
* 功    能 : 获取字符串上某个字符
* 输    入 : int index
* 输    出 : char
* 日    期 : 2020-06-18 
*/

char tstring::charAt(int index)
{
    return *(this->tchar + index);
}

/****************************************************************************
* 函数名   : isEmpty
* 功    能 : 判断字符串是否为空
* 输    入 : 无
* 输    出 : bool
* 日    期 : 2020-06-18 
*/

bool tstring::isEmpty()
{
    return !this->GetLength();
}

/****************************************************************************
* 函数名   : find
* 功    能 : 查找字符串，返回首个字符位置,int参数为返回后的位置偏移量
* 输    入 : char *newstr, size_t move
* 输    出 : size_t
* 日    期 : 2020-06-18 
*/
//2020/6/19 windSnowLi 加入指针是否为空的判断
size_t tstring::find(const char *targetstr, size_t move = 0)
{
    if (targetstr != NULL && this->tchar != NULL)
    {
        char *ptempstr1 = this->tchar;
        char *ptempstr2 = (char *)targetstr;
        size_t index = 0;
        while (*ptempstr1 != '\0')
        {
            if (*ptempstr1 == *ptempstr2)
            {
                ptempstr2++;
            }
            else
            {
                ptempstr2 = (char *)targetstr;
            }
            ptempstr1++;
            index++;
            if (*ptempstr2 == '\0')
            {
                return index + move - GetPCharLength(targetstr);
            }
        }
    }
    return -1;
}

/****************************************************************************
* 函数名   : toLowerCase
* 功    能 : 将字符串全部转化为小写
* 输    入 : 无
* 输    出 : 无
* 日    期 : 2020-06-19 
*/
tstring &tstring::toLowerCase()
{
    this->Strlwr(this->tchar);
    return *this;
}

/****************************************************************************
* 函数名   : toUpperCase
* 功    能 : 将字符串全部转化为大写
* 输    入 : 无
* 输    出 : tstring&
* 日    期 : 2020-06-20 
*/
tstring &tstring::toUpperCase()
{
    this->Strupr(this->tchar);
    return *this;
}

/****************************************************************************
* 函数名   : getStrLength
* 功    能 : 返回对象内置的长度
* 输    入 : 无
* 输    出 : size_t
* 日    期 : 2020-06-20 
*/
size_t tstring::getStrLength()
{
    return loglength;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 重载=运行算符，使用=char*赋值
* 输    入 : const char*
* 输    出 : tstring对象
* 日    期 : 2020-06-18 
*/
//2020/06/16 windsnow 改为返回tstring自身引用
//2020/06/20 windSnowLi 顺带为对象内置长度赋值
tstring &tstring::operator=(const char *str)
{
    // tstring tempstr(str);
    // return tempstr;
    this->loglength = GetPCharLength(str);
    char *ptempstr = new char[this->getStrLength() + 1];
    Strcpy(ptempstr, str);
    if (this->tchar != NULL)
    {
        delete this->tchar;
        this->tchar = NULL;
    }
    this->tchar = ptempstr;
    return *this;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 重载+运算符，trstring结尾续加字符串
* 输    入 : const char *str
* 输    出 : trstring对象
* 日    期 : 2020-06-18 
*/
tstring tstring::operator+(const char *str)
{
    tstring tempstr;
    tempstr.loglength = GetPCharLength(str) + this->getStrLength();
    char *ptempstr = new char[tempstr.loglength + 1];
    Strcpy(ptempstr, this->cstr());
    Strcat(ptempstr, str);
    tempstr.tchar = ptempstr;
    return tempstr;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 重载+运算符，trstring对象相加
* 输    入 : 
* 输    出 : 
* 日    期 : 2020-06-18 
*/
tstring tstring::operator+(const tstring &tstr)
{
    tstring tempstr;
    tempstr.loglength = this->getStrLength() + tstr.loglength;
    char *ptempstr = new char[tempstr.loglength + 1];
    Strcpy(ptempstr, this->cstr());
    Strcat(ptempstr, tstr.tchar);
    tempstr.tchar = ptempstr;
    return tempstr;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 重载+运算符，trstring加char
* 输    入 : const char &tempch
* 输    出 : tstring
* 日    期 : 2020-06-20 
*/
tstring tstring::operator+(const char &ch)
{
    char tempch[2] = {ch, '\0'};
    char *ptemp = tempch;
    tstring tempstr;
    tempstr = *this + ptemp;
    return tempstr;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 重载<<运算符，trstring对象赋值
* 输    入 : tstring &tstr
* 输    出 : 无
* 日    期 : 2020-06-19 
*/
//2020/06/16 windsnow 改为返回tstring自身引用
tstring &tstring::operator>>(tstring &tstr)
{
    tstr.loglength = this->getStrLength();
    char *ptempstr = new char[tstr.getStrLength() + 1];
    Strcpy(ptempstr, this->tchar);
    if (tstr.tchar != NULL)
    {
        delete tstr.tchar;
        tstr.tchar = NULL;
    }
    tstr.tchar = ptempstr;
    return *this;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 重载<<运算符，trstring对象赋值
* 输    入 : tstring &tstr
* 输    出 : 无
* 日    期 : 2020-06-19 
*/
//2020/06/16 windsnow 改为返回tstring自身引用
tstring &tstring::operator<<(tstring &tstr)
{
    tstr.loglength = this->getStrLength();
    char *ptempstr = new char[this->getStrLength() + 1];
    Strcpy(ptempstr, tstr.tchar);
    if (this->tchar != NULL)
    {
        delete this->tchar;
        this->tchar = NULL;
    }
    this->tchar = ptempstr;
    return *this;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 重载<<运算符，trstring对象赋值
* 输    入 : const char *str
* 输    出 : 无
* 日    期 : 2020-06-19 
*/
//2020/06/16 windsnow 改为返回tstring自身引用
tstring &tstring::operator<<(const char *str)
{
    this->loglength = GetPCharLength(str);
    char *ptempstr = new char[this->getStrLength() + 1];
    Strcpy(ptempstr, str);
    if (this->tchar != NULL)
    {
        delete this->tchar;
        this->tchar = NULL;
    }
    this->tchar = ptempstr;
    return *this;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 重载+=运算符，trstring对象相加
* 输    入 : const tstring &tstr
* 输    出 : 无
* 日    期 : 2020-06-19 
*/
//2020/06/20 windSnowLi 顺带为对象内置长度赋值
tstring &tstring::operator+=(const tstring &tstr)
{
    this->loglength = this->getStrLength() + tstr.loglength;
    char *ptempstr = new char[this->getStrLength() + 1];
    Strcpy(ptempstr, this->cstr());
    Strcat(ptempstr, tstr.tchar);
    if (this->tchar != NULL)
    {
        delete this->tchar;
        this->tchar = NULL;
    }
    this->tchar = ptempstr;
    return *this;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 友元fstream部分函数
* 输    入 : ostream &os, const tstring &t
* 输    出 : ostream&
* 日    期 : 2020-06-19 
*/

std::ostream &operator<<(std::ostream &os, const tstring &tstr)
{
    os << tstr.tchar;
    return os;
}
/****************************************************************************
* 函数名   : 
* 功    能 : 友元istream >>运算符
* 输    入 : std::istream &is, const tstring &tstr
* 输    出 : 无
* 日    期 : 2020-06-19 
*/
//2020/06/20 windSnowLi 顺带为对象内置长度赋值
std::istream &operator>>(std::istream &is, tstring &tstr)
{
    //currentbig为分配空间的初始大小，默认100
    size_t currentbig = 100;
    //当前读取的位数
    size_t templength = 0;
    //当前分配空间次数，执行时为1
    size_t allocatetimes = 1;
    //初始空间分配100字符
    char *ptempstr = new char[currentbig];
    while (!is.eof())
    {
        is.read(&ptempstr[templength], 1);
        templength++;
        if (templength == currentbig - 1)
        {
            ptempstr[templength] = '\0';
            //分配次数加一
            allocatetimes++;
            //申请翻倍
            char *temp = new char[currentbig * 2];
            currentbig *= 2;
            tstring::Strcpy(temp, ptempstr);
            delete ptempstr;
            ptempstr = temp;
        }
    }
    if (tstr.tchar != NULL)
    {
        delete tstr.tchar;
        tstr.tchar = NULL;
    }
    tstr.tchar = ptempstr;
    //每读取完一位都会++，所以-1回至实际长度
    tstr.loglength = templength - 1;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 重载+=运算符，trstring加char*
* 输    入 : const char *str
* 输    出 : tstring &
* 日    期 : 2020-06-19 
*/
//2020/06/20 windSnowLi 顺带为对象内置长度赋值
tstring &tstring::operator+=(const char *str)
{
    this->loglength = GetPCharLength(str) + this->getStrLength();
    char *ptempstr = new char[this->getStrLength() + 1];
    Strcpy(ptempstr, this->cstr());
    Strcat(ptempstr, str);
    if (this->tchar != NULL)
    {
        delete this->tchar;
        this->tchar = NULL;
    }
    this->tchar = ptempstr;
    return *this;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 重载==运算符，判断两trstring对象是否相等
* 输    入 : tstring &tstr
* 输    出 : bool
* 日    期 : 2020-06-20 
*/
bool tstring::operator==(const tstring &tstr)
{
    return this->compare(tstr);
}