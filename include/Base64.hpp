#ifndef BASE64_H_
#define BASE64_H_
#include "tstring.hpp"
class tstring;
/*编码
   DataByte
    [in]输入的数据长度,以字节为单位
    */
tstring Encode(const char *Data, int DataByte);

/*解码
    DataByte
    [in]输入的数据长度,以字节为单位
    OutByte
    */
tstring Decode(const char *Data, int DataByte);

#endif