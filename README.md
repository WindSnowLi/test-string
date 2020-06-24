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
```

### 修改

空间申请更改为二倍申请
对比字符串优先进行长度判断
更改字符串运算空间申请方式
