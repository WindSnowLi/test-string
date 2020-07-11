# TString

A custom String library for yourself

自己定制的字符串类

## v0.0.0

Basic function implementation

基本功能实现

## v0.0.1

Modify some functions to optimize user experience. Optimize on a daily basis

修改部分函数，优化使用体验。在日常使用的基础上进行优化

## v0.0.1.1

### add 增加

``` 
    //清空函数，将字符串信息清空
    tstring &clear();
    //交换函数，交换两个tstring的信息
    void swap(tstring &tstr);

```

### repair 修复

    Determines if the pointer type is null when an empty string is printed

    输出空字符串时，判断指针类型是否为空
    

``` 
    //Determines if it is a null pointer
    //2020/06/23 windSnowLi 判断是否为空指针
    std::ostream &operator<<(std::ostream &os, const tstring &tstr)
    {
        if (tstr.tchar != NULL)
        {
            os << tstr.tchar;
        }
        return os;
    }
```

## v0.0.2

### add 增加

``` 
    //当前最大空间长度, 默认128
    //Current maximum space length, default 128
    size_t max_length = 128;

    //返回当前空间最大程度
    //Returns the maximum current space
    size_t getMaxSize();

    //摘要信息 MD5
    //Summary information MD5
    tstring getMD5();

    //重载[]运算符，用于下标取值
    //Overload the [] operator for subscript values
    char& operator[](int move);

    //使用标准库std::string初始化
    //Class using the standard library std::string
    tstring(const std::string &stdstr);

    //重载=运算符,使用标准库std::string赋值
    //Overload the = operator, using the standard library STD ::string assignment
    tstring &operator=(const std::string &stdstr);

    //重载+=运算符,tstring+标准库std::string赋值,使用默认的转化为tstring相加耗费资源
    //Overload += operator, TString + standard library STD :: String assignment, using the default conversion to TString add cost
    //resources
    tstring &operator+=(const std::string &stdstr);
```

### modify 修改

1. Change of space request to double request
2. Compare strings to determine length first
3. Change the string operand space request method

1. 空间申请更改为二倍申请
2. 对比字符串优先进行长度判断
3. 更改字符串运算空间申请方式

### repair 修复

1. Fixed some bugs in TString += TString
2. Fix the default parameter function of Find
3. Fixed an uninitialized BUG using TString to assign a length to a new string   

1. 修复tstring+=tstring的部分BUG
2. 修复find的缺省参数功能
3. 修复使用tstring为新字符串赋值长度未初始化的BUG

## v0.0.2.1

### add 增加

``` 
    /*

    -   替换指定字符串
    -   Replace the specified string

    */
    void replace(const char *targetstr, const char *newstr);

    /*

    -   重载+=运算符，trstring加char
    -   Overload += operator, trstring plus char

    */
    tstring &operator+=(const char &ch);

    /*

    -   重载+运算符,=tstring+标准库std::string
    -   Overload + operator,= Tstring + std::string

    */
    tstring operator+(const std::string &stdstr);
```

## v0.0.2.2

### add 增加

``` 
    /*

    -   将基本类型参数内容转化为tstring
    -   Converts the basic type parameter content to a tstring

    */
    template <typename Type>
    tstring toTstring(const Type &val);
```

## v0.0.2.3

### modify 修改

``` 
    /*

    -   将基本类型参数内容转化为tstring
    -   Converts the basic type parameter content to a TString

    */
    template <typename Type>
    tstring toTstring(const Type &val)
    {
        /*

        *   只允许值类型进行转化
        *   Conversions are only allowed for allowed value types

        */
        static_assert(std::is_arithmetic<Type>::value, "It's not a numeric type");
    }
```

### add 增加

``` 
    /*

    -   返回最后一个字符
    -   Returns the last character

    */
    char back();
    
    /*

    -   追加字符串
    -   Append string

    */
    tstring &append(const char *str);
```

*** 
<font size=5 color=blue>至此基础功能接近完成，后续继续扩大可使用性</font>
<font size=5 color=blue>At this point, the basic functions are nearly completed and the usability continues to be expanded</font>
***

## v0.1.0 Initial application of iterators    初步应用迭代器

### add 增加

### tstring

``` 
    /*

    -  起始迭代器
    -   Initial iterator

    */
    iterator begin();

    /*

    -    b结尾迭代器
    -   End iterator

    */
    iterator end();

    /*

    -   返回反向迭代器起始迭代器
    -   Returns the reverse iterator starting iterator

    */
    reverse_iterator rbegin();

    /*

    -   返回反向迭代器末尾迭代器
    -   Returns the reverse iterator end iterator

    */
    reverse_iterator rend();
```

### add 新增

``` 
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
    char* base();
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
```

***

``` 
    /*

    -   获得BASE64编码
    -   Get BASE64 encoding

    */
    tstring getEncodeBase64();

    /*

    -   解BASE64码
    -   Solution BASE64 code

    */
    tstring getDecodeBase64();
```

## v0.1.0.1  Add insert function  添加插入功能

### add built-in functions 增加内置函数 

``` 
    /*

    -   在主字符串的指定位置插入副字符串， 并把内容拷贝到目标字符串
    -   Inserts the secondary string at the specified position of the main string and copies the contents to the target string

    */
    static void Strinsert(char *mainstr, const char *insertstr, char *targetstr, size_t site);
```

### add

``` 
    /*

    -   删除指定位置的字符 
    -   Deletes the character at the specified position

    */
    iterator erase(iterator iter);
```

***

``` 
    /*
    *

    -   将参数字符串插入指定位置
    -   Inserts the parameter string at the specified location

    */
    tstring &insert(const tstring &tstr, size_t site);
    tstring &insert(const char *str, size_t site);
    tstring &insert(const std::string &str, size_t site);
```

***

``` 
    /*

    -  比较两个正向迭代器位置，如果前者小于后者，则后者正向迭代器更接近末尾
    -   Compare two forward iterator positions, if the former is less than the latter, the latter is closer to the end.

    */
    bool operator<(const tstringiterator &iter);

    /*

    -  比较两个正向迭代器位置，如果前者大于后者，则前者正向迭代器更接近末尾
    -   Comparing two forward iterator positions, if the former is greater than the latter, the former forward iterator is closer to the end.

    */
    bool operator>(const tstringiterator &iter);

    /*

    -  比较两个正向迭代器位置，如果前者小于等于于后者，则返回true
    -   Compares two forward iterator positions and returns "true" if the former is less than or equal to the latter

    */
    bool operator<=(const tstringiterator &iter);

    /*

    -  比较两个正向迭代器位置，如果前者大于等于于后者，则返回“true”
    -   Compares two forward iterator positions and returns "true" if the former is greater than or equal to the latter

    */
    bool operator>=(const tstringiterator &iter);

```

***

``` 
     /*

    -  比较两个反向迭代器位置，如果前者小于后者，则前者者地址值更大，此时返回true
    -  Comparing two reverse iterator positions, if the former is less than the latter, the address value of the former is larger, and this returns true

    */
    bool operator<(const reverse_tstringiterator &iter);

    /*

    -   比较两个反向迭代器位置，如果前者大于后者，则后者地址值更大，此时返回true
    -   Compares two reverse iterator positions, returning true if the former is greater than the latter, and the latter has a larger address value

    */
    bool operator>(const reverse_tstringiterator &iter);

    /*

    -  比较两个反向迭代器位置，如果前者小于等于后者，则前者者地址值更大，此时返回true
    -  Comparing two reverse iterator positions, if the former is less than or equal to the latter, then the former has a larger address value and returns true

    */
    bool operator<=(const reverse_tstringiterator &iter);

    /*

    -  比较两个反向迭代器位置，如果前者大于等于后者，则后者地址值更大，此时返回true
    -  Compares two reverse iterator positions, and returns true if the former is greater than or equal to the latter

    */
    bool operator>=(const reverse_tstringiterator &iter);
```

### repair

***
修复查找函数find的BUG
Fix a BUG in find
***

## v0.1.0.2 FIX BUG AND MODIFY

***

1. replace()含有隐藏BUG，已初步修复
2. 修复部分内存释放时的BUG
3. 优化查找字符串算法
4. 优化流输入的速度,优化后接char的速度

1. replace() contains hidden bugs, which have been preliminarily fixed
2. Fixed some memory release bugs
3. Optimize the search string algorithm
4. Optimized flow input speed, optimized speed of char

***

## v0.1.1 FIX BUG AND MODIFY AND OPTIMIZE

### add

``` 
    /*

    -   指定字符串长度
    -  Specify the length of the string

    */
    void reSize(size_t size);
```

### optimize

***

1. 优化BASE64编码和解码的速度

1. Optimize the speed of BASE64 encoding and decoding

***
