#include "tstring.hpp"
#include <iostream>
#include "tstringiterator.hpp"
#include "MD5.hpp"

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
//v0.0.2 2020/06/23 windSnowLi 修改空间申请定义

tstring::tstring(const char *str)
{
    size_t templength = GetPCharLength(str);
    //检查空间是否需要变动
    this->checkNextMaxSizeSpace(templength);

    this->loglength = templength;

    Strcpy(this->tchar, str);
}

/****************************************************************************
* 函数名   : 拷贝构造函数
* 功    能 : 复制对象
* 输    入 : tstring &tstr
* 输    出 : 无
* 日    期 : 2020-06-18 
*/
//2020/06/20 windSnowLi 顺带为对象内置长度赋值
//v0.0.2 2020/06/23 windSnowLi 修改空间申请定义
//v0.0.2 2020/06/25 windSnowLi 修复使用tstring为新字符串赋值长度未初始化的BUG
tstring::tstring(const tstring &tstr)
{
    this->checkNextMaxSizeSpace(tstr.loglength);

    this->loglength = tstr.loglength;

    Strcpy(this->tchar, tstr.tchar);
}

/****************************************************************************
* 函数名   : 使用std::string的构造函数
* 功    能 : 使用标准库std::string初始化
* 输    入 : const std::string &stdstr
* 输    出 : 
* 日    期 : 2020-06-25 
*/

tstring::tstring(const std::string &stdstr)
{
    this->checkNextMaxSizeSpace(stdstr.length());

    this->loglength = stdstr.length();

    Strcpy(this->tchar, stdstr.c_str());
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
//2020/06/24 windSnowLi 修复新指针为空的BUG
void tstring::Strcpy(char *newstr, const char *oldstr)
{
    if (oldstr != NULL && newstr != NULL)
    {
        while (*oldstr != '\0')
        {
            *newstr = *oldstr;
            newstr++;
            oldstr++;
        }
        *newstr = '\0';
    }
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
* 函数名   : compare
* 功    能 : 比较两个对象是否相等
* 输    入 : const tstring &tstr
* 输    出 : bool
* 日    期 : 2020-06-18 
*/
//v0.0.2  2020/06/23 windSnowLi 优先进行长度匹配
bool tstring::compare(const tstring &tstr)
{
    if (this->loglength != tstr.loglength)
    {
        return false;
    }
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
//v0.0.2  2020/06/23 windSnowLi 优先进行长度匹配
bool tstring::compareIgnoreCase(const tstring &tstr)
{
    if (this->loglength != tstr.loglength)
    {
        return false;
    }
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
* 函数名   : checkNextMaxSizeSpace
* 功    能 : 检查下一次需要的空间是否需要变动，如果变动，将老信息转存至新空间并将tstr新空间指针,否则不做改变,参数为要接受的新的字符串长度
* 输    入 : char *newstr
* 输    出 : char *
* 日    期 : 2020-06-23 
*/
void tstring::checkNextMaxSizeSpace(size_t newstrsize)
{
    size_t temp_max_length = this->max_length;
    while (true)
    {
        if (this->loglength + newstrsize >= this->max_length)
        {
            //默认两倍倍率扩大
            this->max_length *= 2;
        }
        else
        {
            break;
        }
    }
    if (temp_max_length != max_length)
    {
        //新申请的空间
        char *tempstrspace = new char[max_length];
        Strcpy(tempstrspace, this->tchar);
        delete this->tchar;
        this->tchar = tempstrspace;
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
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数
bool tstring::isEmpty()
{
    return !this->getLength();
}

/****************************************************************************
* 函数名   : find
* 功    能 : 查找字符串，返回首个字符位置,int参数为返回后的位置偏移量
* 输    入 : char *newstr, size_t move=0
* 输    出 : size_t
* 日    期 : 2020-06-18 
*/
//2020/6/19 windSnowLi 加入指针是否为空的判断
size_t tstring::find(const char *targetstr, size_t move)
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
* 函数名   : getLength
* 功    能 : 返回对象内置的长度
* 输    入 : 无
* 输    出 : size_t
* 日    期 : 2020-06-20 
*/
//2020/06/23 windSnowLi 将名称更改为getLength()
size_t tstring::getLength()
{
    return loglength;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 清空函数，将字符串信息清空
* 输    入 : 无
* 输    出 : 自身引用
* 日    期 : 2020-06-21 
*/
tstring &tstring::clear()
{
    if (this->loglength != 0)
    {
        delete this->tchar;
        this->tchar = new char[128];
        this->loglength = 0;
        this->max_length = 128;
    }
    return *this;
}

/****************************************************************************
* 函数名   : swap
* 功    能 : 交换函数，交换两个tstring的信息
* 输    入 : tstring &
* 输    出 : 无
* 日    期 : 2020-06-21 
*/
void tstring::swap(tstring &tstr)
{
    char *ptempstr = this->tchar;
    size_t temp_loglength = this->loglength;
    size_t temp_max_length = this->getMaxSize();

    this->tchar = tstr.tchar;
    this->loglength = tstr.loglength;
    this->max_length = tstr.getMaxSize();

    tstr.max_length = temp_max_length;
    tstr.tchar = ptempstr;
    tstr.loglength = temp_loglength;
}

/****************************************************************************
* 函数名   : getMaxSize()
* 功    能 : 返回当前空间最大长度
* 输    入 : 无
* 输    出 : size_t
* 日    期 : 2020-06-23 
*/

size_t tstring::getMaxSize()
{
    return max_length;
}

/****************************************************************************
* 函数名   : getMD5()
* 功    能 : 摘要信息 MD5
* 输    入 : 无
* 输    出 : tstring
* 日    期 : 2020-06-24 
*/
tstring tstring::getMD5()
{
    return ToMD5GetStr((unsigned char *)this->tchar);
}

/****************************************************************************
* 函数名   : replace
* 功    能 : 替换指定字符串
* 输    入 : const char *targetstr, const char *newstr
* 输    出 : 无
* 日    期 : 2020-06-26 
*/

void tstring::replace(const char *targetstr, const char *newstr)
{
    tstring temptstr;

    //需要替换成的字符串长度
    size_t targetlength = GetPCharLength(targetstr);

    char *ptempstr1 = this->tchar;
    char *ptempstr2 = (char *)targetstr;

    while (*ptempstr1 != '\0')
    {
        if (*ptempstr1 == *ptempstr2)
        {
            ptempstr2++;
        }
        else
        {
            ptempstr2 = (char *)targetstr;
            temptstr += *ptempstr1;
        }
        ptempstr1++;
        if (targetlength == 0)
        {
            //需要替换成的字符串长度为0，所以不管上述匹配过程需要替换成的字符串指针是否改变，都重新指向目标字符串
            ptempstr2 = (char *)targetstr;
        }
        else if (*ptempstr2 == '\0')
        {
            ptempstr2 = (char *)targetstr;
            temptstr += newstr;
        }
    }

    //释放已有内存，长度置为零,已有空间置为0，用于直接接收临时对象内容，减少浪费
    if (this->tchar != NULL)
    {
        delete this->tchar;
    }
    this->tchar = NULL;
    this->loglength = 0;
    this->max_length = 0;

    //将临时对象内容赋值给原有对象
    this->tchar = temptstr.tchar;
    this->loglength = temptstr.loglength;
    this->max_length = temptstr.max_length;
}

/****************************************************************************
* 函数名   : back
* 功    能 : 返回最后一个字符
* 输    入 : 无
* 输    出 : char
* 日    期 : 2020-06-27 
*/
char tstring::back()
{
    if (this->loglength != 0)
    {
        return *(this->tchar + this->loglength - 1);
    }
    return '\0';
}

/****************************************************************************
* 函数名   : append
* 功    能 : 追加字符串
* 输    入 : char*
* 输    出 : tstring &
* 日    期 : 2020-06-27 
*/
tstring &tstring::append(const char *str)
{
    *this += str;
    return *this;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 获得BASE64编码
* 输    入 : 无
* 输    出 : tstring
* 日    期 : 2020-06-28 
*/

tstring tstring::getEncodeBase64()
{
    return Encode(this->cstr(), this->getLength());
}

/****************************************************************************
* 函数名   : 
* 功    能 : 解BASE64码
* 输    入 : 无
* 输    出 : tstring
* 日    期 : 2020-06-28 
*/

tstring tstring::getDecodeBase64()
{
    return Decode(this->cstr(), this->getLength());
}

/****************************************************************************
* 函数名   : begin
* 功    能 : 起始迭代器
* 输    入 : 无
* 输    出 : tstringiterator
* 日    期 : 2020-06-28 
*/
tstringiterator tstring::begin()
{
    return iterator(this->tchar);
}

/****************************************************************************
* 函数名   : end
* 功    能 : 结尾迭代器
* 输    入 : 无
* 输    出 : tstringiterator
* 日    期 : 2020-06-28 
*/
tstringiterator tstring::end()
{
    return iterator(this->tchar + this->loglength + 1);
}
/****************************************************************************
* 函数名   : rbegin()
* 功    能 : 返回反向迭代器起始迭代器
* 输    入 : 无
* 输    出 : reverse_tstringiterator
* 日    期 : 2020-06-28 
*/
reverse_tstringiterator tstring::rbegin()
{
    iterator tempiter;
    tempiter = this->end() - 1;
    return reverse_iterator(tempiter);
}

/****************************************************************************
* 函数名   : rend()
* 功    能 : 返回反向迭代器末尾迭代器
* 输    入 : 无
* 输    出 : reverse_tstringiterator
* 日    期 : 2020-06-28 
*/

reverse_tstringiterator tstring::rend()
{
    iterator tempiter;
    tempiter = this->begin() - 1;
    return reverse_iterator(tempiter);
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
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数，更改空间申请方式

tstring &tstring::operator=(const char *str)
{
    //如果字符串本身不为零，释放已有内存，长度置为零
    if (this->loglength != 0)
    {
        delete this->tchar;
        this->tchar = new char[128];
        this->loglength = 0;
        this->max_length = 128;
    }
    size_t templength = GetPCharLength(str);

    //检查当前最大空间是否够用
    this->checkNextMaxSizeSpace(templength);

    //将即将接收的字符串长度设为新字符串的长度
    this->loglength = templength;

    //将接收到的char*复制到新字符串
    Strcpy(this->tchar, str);

    return *this;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 重载+运算符，trstring结尾续加字符串
* 输    入 : const char *str
* 输    出 : trstring对象
* 日    期 : 2020-06-18 
*/
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数，更改空间申请方式
tstring tstring::operator+(const char *str)
{
    //创建临时对象
    tstring tempstr;

    //获得相加后的总长度
    size_t templength = GetPCharLength(str) + this->getLength();

    //检查临时对象空间是否够用
    tempstr.checkNextMaxSizeSpace(tempstr.loglength);

    //将相加后的总长度设为临时对象的长度
    tempstr.loglength = templength;

    //将+前字符串拷贝纸临时对象
    Strcpy(tempstr.tchar, this->tchar);

    //将+后char*追加到临时对象
    Strcat(tempstr.tchar, str);

    return tempstr;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 重载+运算符，trstring对象相加
* 输    入 : 
* 输    出 : 
* 日    期 : 2020-06-18 
*/
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数，更改空间申请方式
tstring tstring::operator+(const tstring &tstr)
{
    //创建临时对象
    tstring tempstr;

    //获得相加后的总长度
    size_t templength = this->getLength() + tstr.loglength;

    //检查临时对象空间是否够用
    tempstr.checkNextMaxSizeSpace(templength);

    //将相加后的总长度设为临时对象的长度
    tempstr.loglength = templength;

    //将+前字符串拷贝纸临时对象
    Strcpy(tempstr.tchar, this->tchar);

    //将+后char*追加到临时对象
    Strcat(tempstr.tchar, tstr.tchar);

    return tempstr;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 重载+运算符，trstring加char
* 输    入 : const char &tempch
* 输    出 : tstring
* 日    期 : 2020-06-20 
*/
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数，更改空间申请方式
tstring tstring::operator+(const char &ch)
{
    //将char转化为指针类型
    char tempch[2] = {ch, '\0'};
    char *ptemp = tempch;

    return *this + ptemp;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 重载<<运算符，trstring对象赋值
* 输    入 : tstring &tstr
* 输    出 : 无
* 日    期 : 2020-06-19 
*/
//2020/06/16 windsnow 改为返回tstring自身引用
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数，更改空间申请方式
tstring &tstring::operator>>(tstring &tstr)
{

    //识别是否需要清空
    if (tstr.loglength != 0)
    {
        delete tstr.tchar;
        tstr.max_length = 128;
        tstr.loglength = 0;
        tstr.tchar = new char[tstr.max_length];
    }

    //判断>>后的字符串空间是否足够
    tstr.checkNextMaxSizeSpace(this->getLength());

    //将长度信息赋值给>>后的字符串
    tstr.loglength = this->getLength();

    //将>>左边的字符串拷贝给右边的字符串
    Strcpy(tstr.tchar, this->tchar);

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
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数，更改空间申请方式
tstring &tstring::operator<<(tstring &tstr)
{
    //识别是否需要清空
    if (this->loglength != 0)
    {
        delete this->tchar;
        this->max_length = 128;
        this->loglength = 0;
        this->tchar = new char[this->max_length];
    }

    //判断空间是否足够
    this->checkNextMaxSizeSpace(this->getLength());

    //将<<右边的长度信息给左边
    this->loglength = this->getLength();

    //将信息拷贝至<<左边
    Strcpy(this->tchar, tstr.tchar);

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
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数，更改空间申请方式
tstring &tstring::operator<<(const char *str)
{

    //识别是否需要清空
    if (this->loglength != 0)
    {
        delete this->tchar;
        this->max_length = 128;
        this->loglength = 0;
        this->tchar = new char[this->max_length];
    }

    size_t templength = GetPCharLength(str);

    //判断空间是否足够
    this->checkNextMaxSizeSpace(templength);

    //将<<右边的长度信息给左边
    this->loglength = templength;

    //将信息拷贝至<<左边
    Strcpy(this->tchar, str);

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
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数，更改空间申请方式
tstring &tstring::operator+=(const tstring &tstr)
{

    //获得相加后的总长度
    size_t templength = this->getLength() + tstr.loglength;

    //检查奔对象最大空间是否足够
    this->checkNextMaxSizeSpace(templength);

    //更新字符串长度
    this->loglength = templength;

    //将接收到的字符串追加上去
    Strcat(this->tchar, tstr.tchar);
    return *this;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 友元fstream部分函数
* 输    入 : ostream &os, const tstring &t
* 输    出 : ostream&
* 日    期 : 2020-06-19 
*/
//2020/06/23 windSnowLi 判断是否为空指针
std::ostream &operator<<(std::ostream &os, const tstring &tstr)
{
    if (tstr.tchar != NULL)
    {
        os << tstr.tchar;
    }
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
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数，更改空间申请方式
std::istream &operator>>(std::istream &is, tstring &tstr)
{
    //识别是否需要清空
    if (tstr.loglength != 0)
    {
        delete tstr.tchar;
        tstr.max_length = 128;
        tstr.loglength = 0;
        tstr.tchar = new char[tstr.max_length];
    }

    //当前读取的位数
    size_t templength = 0;

    while (!is.eof())
    {
        is.read(&tstr.tchar[templength], 1);
        templength++;
        if (templength == tstr.max_length - 1)
        {
            //检查扩容
            tstr.checkNextMaxSizeSpace(templength);
        }
    }
    //每读取完一位都会++，所以-1回至实际长度
    tstr.loglength = templength - 1;
    return is;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 重载+=运算符，trstring加char*
* 输    入 : const char *str
* 输    出 : tstring &
* 日    期 : 2020-06-19 
*/
//2020/06/20 windSnowLi 顺带为对象内置长度赋值
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数，更改空间申请方式
tstring &tstring::operator+=(const char *str)
{

    //获得相加后的总长度
    size_t templength = GetPCharLength(str) + this->getLength();

    //检查是否需要扩容
    this->checkNextMaxSizeSpace(templength);

    //更新字符串长度
    this->loglength = templength;

    //追加新数据
    Strcat(this->tchar, str);

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

/****************************************************************************
* 函数名   : 
* 功    能 : 重载=运算符,使用标准库std::string赋值
* 输    入 : 
* 输    出 : 
* 日    期 : 2020-06-25 
*/
tstring &tstring::operator=(const std::string &stdstr)
{
    //如果字符串本身不为零，释放已有内存，长度置为零
    if (this->loglength != 0)
    {
        delete this->tchar;
        this->tchar = new char[128];
        this->loglength = 0;
        this->max_length = 128;
    }
    size_t templength = stdstr.length();

    //检查当前最大空间是否够用
    this->checkNextMaxSizeSpace(templength);

    //将即将接收的字符串长度设为新字符串的长度
    this->loglength = templength;

    //将接收到的std::string复制到新字符串
    Strcpy(this->tchar, stdstr.c_str());

    return *this;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 重载+运算符,=tstring+标准库std::string
* 输    入 : onst std::string &stdstr
* 输    出 : tstring
* 日    期 : 2020-06-26 
*/

tstring tstring::operator+(const std::string &stdstr)
{
    //创建临时对象
    tstring tempstr;

    //获得相加后的总长度
    size_t templength = stdstr.length() + this->getLength();

    //检查临时对象空间是否够用
    tempstr.checkNextMaxSizeSpace(tempstr.loglength);

    //将相加后的总长度设为临时对象的长度
    tempstr.loglength = templength;

    //将+前字符串拷贝纸临时对象
    Strcpy(tempstr.tchar, this->tchar);

    //将+后char*追加到临时对象
    Strcat(tempstr.tchar, stdstr.c_str());

    return tempstr;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 重载+=运算符,tstring+=标准库std::string
* 输    入 : 
* 输    出 : 
* 日    期 : 2020-06-25 
*/
tstring &tstring::operator+=(const std::string &stdstr)
{
    //获得相加后的总长度
    size_t templength = stdstr.length() + this->getLength();

    //检查是否需要扩容
    this->checkNextMaxSizeSpace(templength);

    //更新字符串长度
    this->loglength = templength;

    //追加新数据
    Strcat(this->tchar, stdstr.c_str());

    return *this;
}

/****************************************************************************
* 函数名   : 
* 功    能 : 重载[]，用于下标取值
* 输    入 : int
* 输    出 : char&
* 日    期 : 2020-06-24 
*/

char &tstring::operator[](int move)
{
    return *(this->tchar + move);
}

/****************************************************************************
* 函数名   : 
* 功    能 : 重载+=运算符，trstring加char
* 输    入 : const char &ch
* 输    出 : tstring
* 日    期 : 2020-06-26 
*/

tstring &tstring::operator+=(const char &ch)
{
    //将char转化为指针类型
    char tempch[2] = {ch, '\0'};
    char *ptemp = tempch;

    //获得相加后的总长度
    size_t templength = this->loglength + 1;

    //检查临时对象空间是否够用
    this->checkNextMaxSizeSpace(templength);

    //将相加后的总长度设为对象的长度
    this->loglength = templength;

    //将+后字符追加到对象
    Strcat(this->tchar, ptemp);

    return *this;
}