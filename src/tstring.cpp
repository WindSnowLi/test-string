#include "tstring.hpp"
#include <iostream>
#include "tstringiterator.hpp"
#include "MD5.hpp"

/****************************************************************************
* Name     : tstring()
* Describe :无参数初始化
* parameter: 无
* @return  : 无
* date     : 2020-06-18 
*/
tstring::tstring()
{
}

/****************************************************************************
* Name     : tstring(const char *str)
* Describe :构造函数初始化
* parameter: const char *
* @return  : 无
* date     : 2020-06-18 
*/
//2020/06/20 windSnowLi 顺带为对象内置长度赋值
//v0.0.2 2020/06/23 windSnowLi 修改空间申请定义

tstring::tstring(const char *str)
{
    /*
    *   需要存储的字符串长度 
    *  The length of the string to store.
    */
    size_t templength = GetPCharLength(str);
    //检查空间是否需要变动
    this->checkNextMaxSizeSpace(templength);

    this->loglength = templength;

    Strcpy(this->tchar, str);
}

/****************************************************************************
* Name     : 拷贝构造函数
* Describe :复制对象
* parameter: tstring &tstr
* @return  : 无
* date     : 2020-06-18 
*/
//2020/06/20 windSnowLi 顺带为对象内置长度赋值
//v0.0.2 2020/06/23 windSnowLi 修改空间申请定义
//v0.0.2 2020/06/25 windSnowLi 修复使用tstring为新字符串赋值长度未初始化的BUG
tstring::tstring(const tstring &tstr)
{
    /*
    *   检查是否需要扩容 
    *   Check to see if expansion is needed.
    */
    this->checkNextMaxSizeSpace(tstr.loglength);
    std::cout << this->loglength << "\t" << tstr.loglength << std::endl;
    this->loglength = tstr.loglength;
    std::cout << this->getMaxSize() << "\t" << tstr.max_length << std::endl;
    Strcpy(this->tchar, tstr.tchar);
}

/****************************************************************************
* Name     : 使用std::string的构造函数
* Describe :使用标准库std::string初始化
* parameter: const std::string &stdstr
* @return  : 
* date     : 2020-06-25 
*/

tstring::tstring(const std::string &stdstr)
{
    /*
    *   检查是否需要扩容 
    *   Check to see if expansion is needed.
    */
    this->checkNextMaxSizeSpace(stdstr.length());

    this->loglength = stdstr.length();

    Strcpy(this->tchar, stdstr.c_str());
}

/****************************************************************************
* Name     : 析构函数
* Describe :释放对象时释放所属资源
* parameter: 无
* @return  : 无
* date     : 2020-06-18 
*/
tstring::~tstring()
{
    if (this->tchar != NULL)
    {
        delete[] this->tchar;
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
    * Name     : cstr
    * Describe :获取char*指针
    * parameter: 
    * @return  : char*
    * date     : 2020-06-18 
    */
const char *tstring::cstr()
{
    return tchar;
}

/****************************************************************************
* Name     : Strcat
* Describe :连接字符串
* parameter: char *before, char *after
* @return  : 无
* date     : 2020-06-18 
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
* Name     : compare
* Describe :比较两个对象是否相等
* parameter: const tstring &tstr
* @return  : bool
* date     : 2020-06-18 
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
* Name     : equalsIgnoreCase
* Describe :比较内容是否相等，忽略大小写
* parameter: const tstring &tstr
* @return  : bool
* date     : 2020-06-18 
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
* Name     : Strcmp
* Describe :比较字符串是否相等
* parameter: const char *str1, const char *str2
* @return  : bool
* date     : 2020-06-18 
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
* Name     : Strlwr
* Describe :将字符串转化为小写
* parameter: char *str
* @return  : 无
* date     : 2020-06-18 
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
* Name     : Strupr
* function :转化为大写 
* parameter: char *str
* @return  : 无
* date     : 2020-06-20 
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
* Name     : Strinsert
* Describe : Inserts the secondary string at the specified position of the main string and copies the contents to the target string
* 描     述: 在主字符串的指定位置插入副字符串， 并把内容拷贝到目标字符串
* parameter: char *mainstr, const char *insertstr, char *targetstr, size_t site
* @return  : 无
* date     : 2020-06-29 
*/
void tstring::Strinsert(char *mainstr, const char *insertstr, char *targetstr, size_t site)
{
    char *tempinsertstr = (char *)insertstr;
    int i = 0;
    for (i = 0; i < site; i++, mainstr++)
    {
        targetstr[i] = *mainstr;
    }

    for (int j = 0; tempinsertstr[j] != '\0'; j++, i++)
    {
        targetstr[i] = tempinsertstr[j];
    }

    for (; *mainstr != '\0'; mainstr++, i++)
    {
        targetstr[i] = *mainstr;
    }
}

/****************************************************************************
* Name     : checkNextMaxSizeSpace
* Describe :检查下一次需要的空间是否需要变动，如果变动，将老信息转存至新空间并将tstr新空间指针,否则不做改变,参数为要接受的新的字符串长度
* parameter: char *newstr
* @return  : char *
* date     : 2020-06-23 
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
    if (temp_max_length != this->getMaxSize())
    {
        //新申请的空间
        char *tempstrspace = new char[this->getMaxSize() + 10]{'\0'};
        if (this->tchar != NULL)
        {
            Strcpy(tempstrspace, this->tchar);
            delete[] this->tchar;
        }
        this->tchar = tempstrspace;
    }
}

/****************************************************************************
* Name     : charAt
* Describe :获取字符串上某个字符
* parameter: int index
* @return  : char
* date     : 2020-06-18 
*/
//2020/07/04 windSnowLi 使用重载运算直接返回
char tstring::charAt(size_t index)
{
    return operator[](index);
}

/****************************************************************************
* Name     : isEmpty
* Describe :判断字符串是否为空
* parameter: 无
* @return  : bool
* date     : 2020-06-18 
*/
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数
bool tstring::isEmpty()
{
    return !this->getLength();
}

/****************************************************************************
* Name     : find
* Describe :查找字符串，返回首个字符位置,int参数为返回后的位置偏移量
* parameter: char *newstr, long long move=0
* @return  : long long
* date     : 2020-06-18 
*/
//2020/6/19 windSnowLi 加入指针是否为空的判断
//2020/07/05 windSnowLi 修复查找的BUG,使用KMP算法
/*
*    targetstr为需要查找的字符串，tstr为主字符串
*  "targetstr" is the string to look for, and "tstr" is the primary string
*/
long long tstring::find(const char *targetstr, long long move)
{
    if (targetstr != NULL && this->tchar != NULL)
    {
        long long targetstr_len = GetPCharLength(targetstr);
        long long targetstr_i = 0;
        long long targetstr_j = -1;
        long long *next = new long long[targetstr_len + 10];
        next[0] = -1;

        while (targetstr_i < targetstr_len)
        {
            if (targetstr_j == -1 || targetstr[targetstr_i] == targetstr[targetstr_j])
            {
                targetstr_i++;
                targetstr_j++;
                if (targetstr[targetstr_i] != targetstr[targetstr_j])
                {
                    next[targetstr_i] = targetstr_j;
                }
                else
                {
                    next[targetstr_i] = next[targetstr_j];
                }
            }
            else
            {
                targetstr_j = next[targetstr_j];
            }
        }

        long long tstr_i = 0;
        targetstr_j = 0;
        long long tstr_len = this->getLength();

        while (tstr_i < tstr_len && targetstr_j < targetstr_len)
        {
            if (targetstr_j == -1 || this->tchar[tstr_i] == targetstr[targetstr_j])
            {
                tstr_i++;
                targetstr_j++;
            }
            else
            {
                /*
                *   当前字符匹配失败，进行跳转 
                *   The current character match fails, jump
                */
                targetstr_j = next[targetstr_j];
            }
        }
        delete[] next;
        /*
        *   匹配成功 
        *  The match is successful
        */
        if (targetstr_j == targetstr_len)
        {
            return tstr_i - targetstr_j + move;
        }
    }
    return -1;
}

/****************************************************************************
* Name     : toLowerCase
* Describe :将字符串全部转化为小写
* parameter: 无
* @return  : 无
* date     : 2020-06-19 
*/
tstring &tstring::toLowerCase()
{
    this->Strlwr(this->tchar);
    return *this;
}

/****************************************************************************
* Name     : toUpperCase
* Describe :将字符串全部转化为大写
* parameter: 无
* @return  : tstring&
* date     : 2020-06-20 
*/
tstring &tstring::toUpperCase()
{
    this->Strupr(this->tchar);
    return *this;
}

/****************************************************************************
* Name     : getLength
* Describe :返回对象内置的长度
* parameter: 无
* @return  : size_t
* date     : 2020-06-20 
*/
//2020/06/23 windSnowLi 将名称更改为getLength()
size_t tstring::getLength()
{
    return loglength;
}

/****************************************************************************
* Name     : 
* Describe :清空函数，将字符串信息清空
* parameter: 无
* @return  : 自身引用
* date     : 2020-06-21 
*/
tstring &tstring::clear()
{
    for (size_t i = 0; i < this->getLength(); i++)
    {
        this->tchar[i] = '\0';
    }
    this->loglength = 0;
    return *this;
}

/****************************************************************************
* Name     : swap
* Describe :交换函数，交换两个tstring的信息
* parameter: tstring &
* @return  : 无
* date     : 2020-06-21 
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
* Name     : getMaxSize()
* Describe :返回当前空间最大长度
* parameter: 无
* @return  : size_t
* date     : 2020-06-23 
*/

size_t tstring::getMaxSize()
{
    return max_length;
}

/****************************************************************************
* Name     : getMD5()
* Describe :摘要信息 MD5
* parameter: 无
* @return  : tstring
* date     : 2020-06-24 
*/
tstring tstring::getMD5()
{
    return ToMD5GetStr((unsigned char *)this->tchar);
}

/****************************************************************************
* Name     : replace
* Describe :替换指定字符串
* parameter: const char *targetstr, const char *newstr
* @return  : 无
* date     : 2020-06-26 
*/
//2020/07/10 windSnowLi 修复查找的隐藏BUG
void tstring::replace(const char *targetstr, const char *newstr)
{
    //需要替换的字符串长度
    size_t targetlength = GetPCharLength(targetstr);
    if (targetlength == 0)
    {
        return;
    }
    tstring temptstr;

    char *pMainStr = this->tchar;
    char *pTargetstr = (char *)targetstr;
    char *pprogram = this->tchar;
    while (*pMainStr != '\0')
    {
        if (*pMainStr == *pTargetstr)
        {
            pTargetstr++;
            pMainStr++;
        }
        else
        {
            pTargetstr = (char *)targetstr;
            pMainStr = pprogram + 1;
            while (pprogram < pMainStr)
            {
                temptstr += *pprogram;
                pprogram++;
            }
        }

        if (*pTargetstr == '\0')
        {
            pTargetstr = (char *)targetstr;
            pprogram = pprogram + targetlength;
            temptstr += newstr;
        }
    }
    this->swap(temptstr);
}

/****************************************************************************
* Name     : back
* Describe :返回最后一个字符
* parameter: 无
* @return  : char&
* date     : 2020-06-27 
*/
//2020/07/04 windSnowLi 改为返回引用
char &tstring::back()
{
    return operator[](this->loglength - 1);
}

/****************************************************************************
* Name     : append
* Describe :追加字符串
* parameter: char*
* @return  : tstring &
* date     : 2020-06-27 
*/
tstring &tstring::append(const char *str)
{
    *this += str;
    return *this;
}

/****************************************************************************
* Name     : getEncodeBase64
* Describe :获得BASE64编码
* parameter: 无
* @return  : tstring
* date     : 2020-06-28 
*/

tstring tstring::getEncodeBase64()
{
    tstring tempTstr;
      if (tempTstr.tchar != NULL)
      {
          delete[] tempTstr.tchar;
          tempTstr.tchar = Encode(this->cstr(), this->getLength(), tempTstr.loglength, tempTstr.max_length);
      }
    return tempTstr;
}

/****************************************************************************
* Name     : 
* Describe :解BASE64码
* parameter: 无
* @return  : tstring
* date     : 2020-06-28 
*/

tstring tstring::getDecodeBase64()
{
    tstring tempTstr;
    if (tempTstr.tchar != NULL)
    {
        delete[] tempTstr.tchar;
        tempTstr.tchar = Decode(this->cstr(), this->getLength(), tempTstr.loglength, tempTstr.max_length);
    }
    return tempTstr;
}

/****************************************************************************
* Name     : insert
* Describe : Inserts the parameter string at the specified location
* 描     述: 将参数字符串插入指定位置
* parameter: const tstring tstr, size_t site
* @return  : tstring&
* date     : 2020-06-29 
*/
//v0.1.0.1 2020/07/02 windSnowLi 修复长度赋值时的BUG
tstring &tstring::insert(const tstring &tstr, size_t site)
{
    tstring temptstr;
    /*
    *   字符插入后的长度
    *   The length of the inserted character
    */
    size_t templength = this->loglength + tstr.loglength;

    /*
    *   检查或扩容扩容临时对象空间
    *   Check or expand temporary object space
    */
    temptstr.checkNextMaxSizeSpace(templength);

    /*
    *   使用内置的Strinsert将数据合并到临时tstring对象 
    *   Use the built-in Strinsert to merge the data into a temporary TString object
    */
    Strinsert(this->tchar, tstr.tchar, temptstr.tchar, site);

    /*
    *   更新临时对象实际长度
    *   Updates the actual length of the temporary object
    */
    temptstr.loglength = templength;

    /*
    *   将临时字符串输入到本tstring对象 
    *   Enter a temporary string into this TString object
    */
    *this << temptstr;

    return *this;
}

/****************************************************************************
* Name     : insert
* Describe : Inserts the parameter string at the specified location
* 描     述: 将参数字符串插入指定位置
* parameter: const char *str, size_t site
* @return  : tstring&
* date     : 2020-06-29 
*/
//v0.1.0.1 2020/07/02 windSnowLi 修复长度赋值时的BUG
tstring &tstring::insert(const char *str, size_t site)
{
    tstring temptstr;
    /*
    *   字符插入后的长度
    *   The length of the inserted character
    */
    size_t templength = this->loglength + GetPCharLength(str);

    /*
    *   检查或扩容扩容临时对象空间
    *   Check or expand temporary object space
    */
    temptstr.checkNextMaxSizeSpace(templength);

    /*
    *   使用内置的Strinsert将数据合并到临时tstring对象 
    *   Use the built-in Strinsert to merge the data into a temporary TString object
    */
    Strinsert(this->tchar, str, temptstr.tchar, site);

    /*
    *   更新临时对象实际长度
    *   Updates the actual length of the temporary object
    */
    temptstr.loglength = templength;

    /*
    *   将临时字符串输入到本tstring对象 
    *   Enter a temporary string into this TString object
    */
    *this << temptstr;

    return *this;
}

/****************************************************************************
* Name     : insert
* Describe : Inserts the parameter string at the specified location
* 描     述: 将参数字符串插入指定位置
* parameter: const std::string &str, size_t site
* @return  : tstring&
* date     : 2020-06-29 
*/
//v0.1.0.1 2020/07/02 windSnowLi 修复长度赋值时的BUG
tstring &tstring::insert(const std::string &str, size_t site)
{
    tstring temptstr;
    /*
    *   字符插入后的长度
    *   The length of the inserted character
    */
    size_t templength = this->loglength + str.length();

    /*
    *   检查或扩容扩容临时对象空间
    *   Check or expand temporary object space
    */
    temptstr.checkNextMaxSizeSpace(templength);

    /*
    *   使用内置的Strinsert将数据合并到临时tstring对象 
    *   Use the built-in Strinsert to merge the data into a temporary TString object
    */
    Strinsert(this->tchar, str.c_str(), temptstr.tchar, site);

    /*
    *   更新临时对象实际长度
    *   Updates the actual length of the temporary object
    */
    temptstr.loglength = templength;

    /*
    *   将临时字符串输入到本tstring对象 
    *   Enter a temporary string into this TString object
    */
    *this << temptstr;

    return *this;
}

/****************************************************************************
* Name     : erase
* Describe : Deletes the character at the specified position
* 描     述: 删除指定位置的字符 
* parameter: iterator
* @return  : iterator
* date     : 2020-07-02 
*/
tstringiterator tstring::erase(iterator iter)

{
    tstring temptstr;
    temptstr.checkNextMaxSizeSpace(this->getLength());
    char *temptstr_j = temptstr.tchar;
    size_t del_index = 0, record_index = 0;
    for (tstring::iterator i = this->begin(); i < this->end(); i++, temptstr_j++, record_index++)
    {
        if (i == iter)
        {
            temptstr_j--;
            del_index = record_index;
            continue;
        }
        *temptstr_j = *i;
    }
    temptstr.loglength = this->getLength() - 1;
    temptstr >> *this;
    return iterator(this->tchar + del_index);
}

/****************************************************************************
* Name     : reSize
* Describe : Specify the length of the string
* 描     述:指定字符串长度
* parameter: size_t size
* @return  : void
* date     : 2020-07-11 
*/

void tstring::reSize(size_t size)
{
    this->checkNextMaxSizeSpace(size);
}

/****************************************************************************
* Name     : begin
* Describe :起始迭代器
* parameter: 无
* @return  : tstringiterator
* date     : 2020-06-28 
*/
tstringiterator tstring::begin()
{
    return iterator(this->tchar);
}

/****************************************************************************
* Name     : end
* Describe :结尾迭代器
* parameter: 无
* @return  : tstringiterator
* date     : 2020-06-28 
*/
tstringiterator tstring::end()
{
    return iterator(this->tchar + this->loglength);
}
/****************************************************************************
* Name     : rbegin()
* Describe :返回反向迭代器起始迭代器
* parameter: 无
* @return  : reverse_tstringiterator
* date     : 2020-06-28 
*/
reverse_tstringiterator tstring::rbegin()
{
    iterator tempiter;
    tempiter = this->end() - 1;
    return reverse_iterator(tempiter);
}

/****************************************************************************
* Name     : rend()
* Describe :返回反向迭代器末尾迭代器
* parameter: 无
* @return  : reverse_tstringiterator
* date     : 2020-06-28 
*/

reverse_tstringiterator tstring::rend()
{
    iterator tempiter;
    tempiter = this->begin() - 1;
    return reverse_iterator(tempiter);
}

/****************************************************************************
* Name     : 
* Describe :重载=运行算符，使用=char*赋值
* parameter: const char*
* @return  : tstring对象
* date     : 2020-06-18 
*/
//2020/06/16 windsnow 改为返回tstring自身引用
//2020/06/20 windSnowLi 顺带为对象内置长度赋值
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数，更改空间申请方式

tstring &tstring::operator=(const char *str)
{
    /*
    *   获得将要赋值的字符串长度 
    *  Gets the length of the string to be assigned.
    */
    size_t templength = GetPCharLength(str);

    /*
    *   清空自身字符串 
    *  Empty the string itself.
    */
    this->clear();

    //检查当前最大空间是否够用
    this->checkNextMaxSizeSpace(templength);

    if (templength != 0)
    {
        //将即将接收的字符串长度设为新字符串的长度
        this->loglength = templength;

        //将接收到的char*复制到新字符串
        Strcpy(this->tchar, str);
    }
    return *this;
}

/****************************************************************************
* Name     : 
* Describe :重载+运算符，trstring结尾续加字符串
* parameter: const char *str
* @return  : trstring对象
* date     : 2020-06-18 
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
* Name     : 
* Describe :重载+运算符，trstring对象相加
* parameter: 
* @return  : 
* date     : 2020-06-18 
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
* Name     : 
* Describe :重载+运算符，trstring加char
* parameter: const char &tempch
* @return  : tstring
* date     : 2020-06-20 
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
* Name     : 
* Describe :重载<<运算符，trstring对象赋值
* parameter: tstring &tstr
* @return  : 无
* date     : 2020-06-19 
*/
//2020/06/16 windsnow 改为返回tstring自身引用
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数，更改空间申请方式
//v0.1.0.1 2020/07/02 windSnowLi tstring>>tstring与tstring<<tstring本质相同，修改为一致
tstring &tstring::operator>>(tstring &tstr)
{
    tstr << *this;
    return *this;
}

/****************************************************************************
* Name     : 
* Describe :重载<<运算符，trstring对象赋值
* parameter: tstring &tstr
* @return  : 无
* date     : 2020-06-19 
*/
//2020/06/16 windsnow 改为返回tstring自身引用
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数，更改空间申请方式
//v0.1.0.1 2020/07/02 windSnowLi 修复<<长度未正确赋值的BUG
tstring &tstring::operator<<(tstring &tstr)
{
    //识别是否需要清空
    if (this->loglength != 0)
    {
        delete[] this->tchar;
        this->max_length = 128;
        this->loglength = 0;
        this->tchar = new char[this->max_length]{'\0'};
    }

    //判断空间是否足够
    this->checkNextMaxSizeSpace(this->getLength());

    //将<<右边的长度信息给左边
    this->loglength = tstr.getLength();

    //将信息拷贝至<<左边
    Strcpy(this->tchar, tstr.tchar);

    return *this;
}

/****************************************************************************
* Name     : 
* Describe :重载<<运算符，trstring对象赋值
* parameter: const char *str
* @return  : 无
* date     : 2020-06-19 
*/
//2020/06/16 windsnow 改为返回tstring自身引用
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数，更改空间申请方式
tstring &tstring::operator<<(const char *str)
{

    //识别是否需要清空
    if (this->loglength != 0)
    {
        delete[] this->tchar;
        this->max_length = 128;
        this->loglength = 0;
        this->tchar = new char[this->max_length]{'\0'};
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
* Name     : 
* Describe :重载+=运算符，trstring对象相加
* parameter: const tstring &tstr
* @return  : 无
* date     : 2020-06-19 
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
* Name     : 
* Describe :友元fstream部分函数
* parameter: ostream &os, const tstring &t
* @return  : ostream&
* date     : 2020-06-19 
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
* Name     : 
* Describe :友元istream >>运算符
* parameter: std::istream &is, const tstring &tstr
* @return  : 无
* date     : 2020-06-19 
*/
//2020/06/20 windSnowLi 顺带为对象内置长度赋值
//v0.0.2 2020/06/23 windSnowLi 更改获取长度的函数，更改空间申请方式
std::istream &operator>>(std::istream &is, tstring &tstr)
{
    //识别是否需要清空
    if (tstr.loglength != 0)
    {
        delete[] tstr.tchar;
        tstr.max_length = 128;
        tstr.loglength = 0;
        tstr.tchar = new char[tstr.max_length]{'\0'};
    }

    /*
    *   获取数据总长度 
    *  Gets the total length of the data.
    */
    is.seekg(0, is.end);
    size_t allLength = is.tellg();
    is.seekg(0, is.beg);
    if (allLength != 0)
    {
        /*
        *   将字符串长度设置为可容纳数据的长度 
        *  Sets the string length to the length that can hold data.
        */
        tstr.reSize(allLength);

        /*
        *   一次性读取
        *  One-time read.
        */
        is.read(tstr.tchar, allLength);

        /*
        *   更新tstring长度 
        *  Update the tstring length.
        */
        tstr.loglength = allLength;
    }
    return is;
}

/****************************************************************************
* Name     : 
* Describe :重载+=运算符，trstring加char*
* parameter: const char *str
* @return  : tstring &
* date     : 2020-06-19 
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
* Name     : 
* Describe :重载==运算符，判断两trstring对象是否相等
* parameter: tstring &tstr
* @return  : bool
* date     : 2020-06-20 
*/
bool tstring::operator==(const tstring &tstr)
{
    return this->compare(tstr);
}

/****************************************************************************
* Name     : 
* Describe :重载=运算符,使用标准库std::string赋值
* parameter: 
* @return  : 
* date     : 2020-06-25 
*/
tstring &tstring::operator=(const std::string &stdstr)
{
    //如果字符串本身不为零，释放已有内存，长度置为零
    if (this->loglength != 0)
    {
        delete[] this->tchar;
        this->tchar = new char[128]{'\0'};
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
* Name     : 
* Describe :重载+运算符,=tstring+标准库std::string
* parameter: onst std::string &stdstr
* @return  : tstring
* date     : 2020-06-26 
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
* Name     : 
* Describe :重载+=运算符,tstring+=标准库std::string
* parameter: 
* @return  : 
* date     : 2020-06-25 
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
* Name     : 
* Describe :重载[]，用于下标取值
* parameter: int
* @return  : char&
* date     : 2020-06-24 
*/

char &tstring::operator[](size_t index)
{
    return *(this->tchar + index);
}

/****************************************************************************
* Name     : 
* Describe :重载+=运算符，trstring加char
* parameter: const char &ch
* @return  : tstring
* date     : 2020-06-26 
*/

tstring &tstring::operator+=(const char &ch)
{
    //获得相加后的总长度
    size_t templength = this->loglength + 1;

    //检查临时对象空间是否够用
    this->checkNextMaxSizeSpace(templength);

    //末尾追加字符
    this->tchar[this->getLength()] = ch;

    //将相加后的总长度设为对象的长度
    this->loglength = templength;
    return *this;
}