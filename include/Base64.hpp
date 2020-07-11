#ifndef BASE64_H_
#define BASE64_H_
#include "tstring.hpp"
class tstring;
/*编码
   DataByte
    [in]输入的数据长度,以字节为单位
    */
char *Encode(const char *Data, size_t DataByte, size_t &OutByte, size_t &max_length);

/*解码
    DataByte
    [in]输入的数据长度,以字节为单位
    OutByte
    */
char *Decode(const char *Data, size_t DataByte, size_t &OutByte, size_t &max_length);

#endif