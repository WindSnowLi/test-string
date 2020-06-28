# TString
自己定制的字符串类

## v0.0.0

基本功能实现

## v0.0.1

修改部分函数，优化使用体验。在日常使用的基础上进行优化

## v0.0.1.1

### 增加

``` 

    //清空函数，将字符串信息清空
    tstring &clear();
    //交换函数，交换两个tstring的信息
    void swap(tstring &tstr);

```

### 修复

    输出空字符串时，判断指针类型是否为空
    

``` 
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

### 增加

``` 
    //当前最大空间长度, 默认128
    size_t max_length = 128;

    //返回当前空间最大程度
    size_t getMaxSize();

    //摘要信息 MD5
    tstring getMD5();

    //重载[]运算符，用于下标取值
    char& operator[](int move);

    //使用标准库std::string初始化
    tstring(const std::string &stdstr);

    //重载=运算符,使用标准库std::string赋值
    tstring &operator=(const std::string &stdstr);

    //重载+=运算符,tstring+标准库std::string赋值,使用默认的转化为tstring相加耗费资源
    tstring &operator+=(const std::string &stdstr);
```

### 修改

空间申请更改为二倍申请
对比字符串优先进行长度判断
更改字符串运算空间申请方式

### 修复

修复tstring+=tstring的部分BUG
修复find的缺省参数功能
修复使用tstring为新字符串赋值长度未初始化的BUG

## v0.0.2.1

### 增加

``` 
    //替换指定字符串
    void replace(const char *targetstr, const char *newstr);

    //重载+=运算符，trstring加char
    tstring &operator+=(const char &ch);

    //重载+运算符,=tstring+标准库std::string
    tstring operator+(const std::string &stdstr);
```

## v0.0.2.2

### 增加

``` 
    //将基本类型参数内容转化为tstring
    template <typename Type>
    tstring toTstring(const Type &val);
```

## v0.0.2.3

### 修改

``` 
 //将基本类型参数内容转化为tstring
template <typename Type>
tstring toTstring(const Type &val)
{
    //只允许值类型进行转化
    static_assert(std::is_arithmetic<Type>::value, "It's not a numeric type");
}
```

### 增加

``` 
    //返回最后一个字符
    char back();
    //追加字符串
    tstring &append(const char *str);
```

*** 
<font size=5 color=blue>至此基础功能接近完成，后续继续扩大可使用性</font>
***

## v0.1.0 初步应用迭代器

### 增加

### tstring类

``` 
    //起始迭代器
    iterator begin();
    //结尾迭代器
    iterator end();

    //返回反向迭代器起始迭代器
    reverse_iterator rbegin();
    //返回反向迭代器末尾迭代器
    reverse_iterator rend();
```

### 新增

``` 
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
```
***
```
    //获得BASE64编码
    tstring getEncodeBase64();

    //解BASE64码
    tstring getDecodeBase64();
```
