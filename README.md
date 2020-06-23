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
