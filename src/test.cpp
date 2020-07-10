#include <iostream>
#include "tstring.hpp"
#include <sstream>
#include <cstring>
#include <fstream>
using namespace std;
int main(int argc, char const *argv[])
{
    /*
    *  直接初始化测试  
    *  Directly initialize the test.
    */
    tstring ini_test("我喜欢你");
    cout << ini_test.cstr() << endl;

    /*
    *   拷贝初始化测试 
    *  Copy the initialization tests.
    */
    tstring copy_test(ini_test);
    cout << copy_test.cstr() << endl;

    /*
    *   tstring对象直接赋值测试 
    *  The tstring object is a direct assignment test.
    */
    tstring tstring_copy_test = copy_test;
    cout << tstring_copy_test.cstr() << endl;

    /*
    *   重载运算符测试 
    *  Overload operator test.
    */
    tstring operator_test1 = "我喜欢你";
    cout << operator_test1.cstr() << endl;
    tstring operator_test2 = tstring_copy_test + "我爱你";
    cout << operator_test2.cstr() << endl;

    tstring operator_test3 = operator_test2 + "我爱你啊" + operator_test1;
    cout << operator_test3.cstr() << endl;

    /*
    *   tstring对象对比测试 
    *  tstring object contrast test
    */
    if (ini_test == operator_test1)
    {
        cout << "I Love You!!!!!" << endl;
    }

    /*
    *   指定取值测试 
    *  Specified value test
    */
    tstring chaAt_test = "I Love You";
    cout << chaAt_test.charAt(2) << endl;

    /*
    *   判断是否非空测试 
    *  Determine if the test is not null.
    */
    tstring isEmpty_test;
    if (isEmpty_test.isEmpty())
    {
        cout << "我想看到你!" << endl;
    }
    else
    {
        cout << "I want look you!" << endl;
    }

    /*
    *   忽略大小写对比测试 
    *  Ignore case-comparison tests.
    */
    tstring compareIgnore_test1 = "I love you!";
    tstring compareIgnore_test2 = "I Love You!";
    tstring compareIgnore_test3 = "I Love You!!";
    if (compareIgnore_test1.compareIgnoreCase(compareIgnore_test2))
    {
        cout << "me too" << endl;
    }
    if (compareIgnore_test2.compareIgnoreCase(compareIgnore_test3))
    {
        cout << "me too too " << endl;
    }
    if (compareIgnore_test1.compareIgnoreCase(compareIgnore_test3))
    {
        cout << "me too too!! " << endl;
    }

    /*
    *   查找字符串测试 
    *  Find string test.
    */
    tstring find_test = "bbc abcdab abcdabcdabde";
    cout << find_test.find("abcdabd") << endl;

    /*
    *   流输入测试
    *  Stream input test.
    */
    tstring stream_test1 = "windSnowLi", stream_test2;
    stream_test1 >> stream_test2;
    cout << stream_test2 << endl;

    /*
    *   自叠加测试 
    *  Self stacking test.
    */
    tstring stack_test1;
    stack_test1 += stream_test2;
    cout << "LOVE\t" << stack_test1 << endl;

    tstring stack_test2 = "I ";
    stack_test2 += "LOVE ";
    cout << stack_test2 << endl;

    tstring test29;
    test29 += 'a';
    cout << test29 << endl;

    /*
    *   流输入测试
    *  Stream input test.
    */
    tstring stream_input_test1;
    stream_input_test1 << "我爱你";
    tstring stream_input_test2 = "我喜欢你";
    tstring stream_input_test3 = stream_input_test1 + stream_input_test2;
    cout << stream_input_test3 << endl;

    cout << "*********************" << endl;
    tstring stream_input_test4 = "ILoveYouILoveYouILoveYouILoveYouILoveYouILoveYouILoveYouILoveYou";

    istringstream is(stream_input_test4.cstr());

    tstring stream_input_test5;
    is >> stream_input_test5;
    cout << stream_input_test5 << endl;

    /*
    *   获取长度测试 
    *  Get length test.
    */
    cout << compareIgnore_test3.getLength() << "\t" << strlen(compareIgnore_test3.cstr()) << endl;
    tstring get_length_test = "I Love Yo";
    get_length_test = get_length_test + 'u';
    cout << get_length_test << endl;
    cout << stream_input_test4.getMaxSize() << "\t" << stream_input_test4.getLength() << endl;
    cout << compareIgnore_test3.getMaxSize() << "\t" << compareIgnore_test3.getLength() << endl;
    tstring temp_MD5 = stream_input_test4.getMD5();
    cout << temp_MD5 << endl;

    /*
    *   字符重赋值测试 
    *  Character reassignment test.
    */
    tstring operator_test;
    operator_test += "I Love You。";
    cout << operator_test << endl;
    operator_test[10] = '.';
    cout << operator_test << endl;

    /*
    *   std::string向tstring赋值测试 
    *  std::string to tstring assignment test
    */
    std::string string_to_tstring_test = "windSnowLi";
    cout << string_to_tstring_test << endl;

    tstring test25 = string_to_tstring_test;
    tstring test26(string_to_tstring_test);
    test26 += string_to_tstring_test;
    cout << test25 << "\t||\t" << test26 << endl;

    /*
    *   字符串替换测试 
    *  String replacement test
    */
    tstring string_replace_test1 = "aab";
    char *string_replace_test2 = (char *)string_replace_test1.cstr();
    string_replace_test2[2] = 'a';
    cout << string_replace_test2 << endl;

    cout << stream_input_test4.getLength() << endl;
    stream_input_test4.replace("ILoveYou", " I LOVE YOU");
    cout << stream_input_test4.getLength() << "\t" << stream_input_test4 << endl;
    stream_input_test4.replace("LOVE", "");
    cout << stream_input_test4.getLength() << "\t" << stream_input_test4 << endl;

    /*
    *   数值类型转化为tstring 
    *  The numeric type is converted to tstring.
    */
    tstring numeric_to_tstring_test;
    numeric_to_tstring_test = toTstring(125.5);
    cout << numeric_to_tstring_test << endl;

    /*
    *   返回末尾测试 
    *  Back to the end test.
    */
    cout << numeric_to_tstring_test.back() << endl;

    /*
    *   迭代器初步测试 
    *  Initial testing of the iterator.
    */
    for (auto iter = stream_input_test4.begin(); iter != stream_input_test4.end(); iter++)
    {
        cout << *iter << " ";
    }
    cout << "\n正向迭代器访问结束" << endl;
    for (auto iter = stream_input_test4.rbegin(); iter != stream_input_test4.rend(); iter++)
    {
        cout << *iter << " ";
    }
    cout << "\n反向迭代器访问结束" << endl;

    /*
    *   Base64编码、解码测试
    *  Base64 encoding, decoding test.
    */
    tstring tstring_base64_test = "0000ILoveYouILoveYouILoveYouILoveYouILoveYouILoveYouILoveYouILoveYou0000";
    tstring tstring_base64 = tstring_base64_test.getEncodeBase64();
    cout << tstring_base64 << endl;
    cout << tstring_base64.getDecodeBase64() << endl;

    /*
    *   字符串插入测试 
    *  String insertion test
    */
    tstring tstring_insert_test = "123456789";
    tstring_insert_test.insert("abc", 5);
    tstring_insert_test.insert("abc", 0);
    cout << tstring_insert_test << "\t" << tstring_insert_test.getLength() << endl;

    /*
    *  迭代器删除数据测试
    *  Iterator removes data tests
    */
    tstring::iterator tstring_insert_testiter = tstring_insert_test.begin() + 5;
    cout << *tstring_insert_testiter << "\t" << endl;
    cout << tstring_insert_test << endl;
    tstring_insert_test.erase(tstring_insert_testiter);
    cout << tstring_insert_test << endl;
    tstring_insert_test.erase(tstring_insert_test.begin());
    cout << tstring_insert_test << endl;
    tstring_insert_test.erase(tstring_insert_test.end() - 1);
    cout << tstring_insert_test << endl;

    /*
    *   文件Base64编码测试 
    *   File Base64 encoding test.
    */
    ifstream Base64_File_test1;
    Base64_File_test1.open("E:\\Desktop\\test.txt", std::ios::in);
    if (Base64_File_test1)
    {
        string Base64_File_test2;
        Base64_File_test1 >> Base64_File_test2;
        ofstream Base64_File_test4("E:\\Desktop\\test1.txt", std::ios::out | std::ios::trunc);
        tstring Base64_File_test3 = Base64_File_test2;
        Base64_File_test4 << Base64_File_test3.getEncodeBase64();
        cout << "Base64 size:" << Base64_File_test3.getLength() << endl
             << "Base64_tstring MAX size:" << Base64_File_test3.getMaxSize() << endl;
        Base64_File_test4.close();
    }
    else
    {
        cout << "file don't found!" << endl;
    }
    Base64_File_test1.close();

    cout << "endl" << endl;
    getchar();
    return 0;
}
