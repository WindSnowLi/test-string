#include "base64.hpp"

char *Encode(const char *Data, size_t DataByte, size_t &OutByte, size_t &max_length)
{
    //编码表
    const char EncodeTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    size_t current = BASICS_MAX_LENGTH_, needSize = DataByte * 1.4;
    while (true)
    {
        if (needSize >= current)
        {
            //默认两倍倍率扩大
            current *= 2;
        }
        else
        {
            max_length = current;
            break;
        }
    }
    //返回值
    char *encodeStr = new char[current + 10];
    char *tempStrEncodeTchar = encodeStr;
    unsigned char Tmp[4] = {0};
    int LineLength = 0;
    for (long long i = 0; i < (long long)(DataByte / 3); i++)
    {
        Tmp[1] = *Data++;
        Tmp[2] = *Data++;
        Tmp[3] = *Data++;
        *tempStrEncodeTchar++ = EncodeTable[Tmp[1] >> 2];
        *tempStrEncodeTchar++ = EncodeTable[((Tmp[1] << 4) | (Tmp[2] >> 4)) & 0x3F];
        *tempStrEncodeTchar++ = EncodeTable[((Tmp[2] << 2) | (Tmp[3] >> 6)) & 0x3F];
        *tempStrEncodeTchar++ = EncodeTable[Tmp[3] & 0x3F];
        if (LineLength += 4, LineLength == 76)
        {
            *tempStrEncodeTchar++ = '\r';
            *tempStrEncodeTchar++ = '\n';
            LineLength = 0;
        }
    }
    //对剩余数据进行编码
    long long Mod = DataByte % 3;
    if (Mod == 1)
    {
        Tmp[1] = *Data++;
        *tempStrEncodeTchar++ = EncodeTable[(Tmp[1] & 0xFC) >> 2];
        *tempStrEncodeTchar++ = EncodeTable[((Tmp[1] & 0x03) << 4)];
        *tempStrEncodeTchar++ = '=';
        *tempStrEncodeTchar++ = '=';
    }
    else if (Mod == 2)
    {
        Tmp[1] = *Data++;
        Tmp[2] = *Data++;
        *tempStrEncodeTchar++ = EncodeTable[(Tmp[1] & 0xFC) >> 2];
        *tempStrEncodeTchar++ = EncodeTable[((Tmp[1] & 0x03) << 4) | ((Tmp[2] & 0xF0) >> 4)];
        *tempStrEncodeTchar++ = EncodeTable[((Tmp[2] & 0x0F) << 2)];
        *tempStrEncodeTchar++ = '=';
    }
    OutByte = tempStrEncodeTchar - encodeStr;
    return encodeStr;
}

char *Decode(const char *Data, size_t DataByte, size_t &OutByte, size_t &max_length)
{
    //解码表
    const char DecodeTable[] =
        {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            62, // '+'
            0, 0, 0,
            63,                                     // '/'
            52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // '0'-'9'
            0, 0, 0, 0, 0, 0, 0,
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
            13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
            0, 0, 0, 0, 0, 0,
            26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
            39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
        };
    //返回值
    size_t current = BASICS_MAX_LENGTH_, needSize = DataByte / 1.2;
    while (true)
    {
        if (needSize >= current)
        {
            //默认两倍倍率扩大
            current *= 2;
        }
        else
        {
            max_length = current;
            break;
        }
    }

    char *strDecode = new char[current + 10];
    char *tempstrDecode = strDecode;
    long long nValue;
    long long i = 0;
    while (i < DataByte)
    {
        if (*Data != '\r' && *Data != '\n')
        {
            nValue = DecodeTable[*Data++] << 18;
            nValue += DecodeTable[*Data++] << 12;
            *tempstrDecode++ = (nValue & 0x00FF0000) >> 16;
            if (*Data != '=')
            {
                nValue += DecodeTable[*Data++] << 6;
                *tempstrDecode++ = (nValue & 0x0000FF00) >> 8;
                if (*Data != '=')
                {
                    nValue += DecodeTable[*Data++];
                    *tempstrDecode++ = nValue & 0x000000FF;
                }
            }
            i += 4;
        }
        else // 回车换行,跳过
        {
            Data++;
            i++;
        }
    }
    OutByte = tempstrDecode - strDecode;
    return strDecode;
}
