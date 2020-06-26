#include <iostream>
#include "tstring.hpp"
#include <sstream>
#include <cstring>
using namespace std;
int main(int argc, char const *argv[])
{
    tstring test1("我喜欢你");
    cout << test1.cstr() << endl;

    tstring test2(test1);
    cout << test2.cstr() << endl;

    tstring test3 = test2;
    cout << test3.cstr() << endl;

    tstring test4 = "我喜欢你";
    cout << test4.cstr() << endl;

    tstring test5 = test3 + "我爱你";
    cout << test5.cstr() << endl;

    tstring test6 = test5 + "我爱你啊" + test4;
    cout << test6.cstr() << endl;

    if (test1 == test4)
    {
        cout << "I Love You!!!!!" << endl;
    }
    tstring test7 = "I Love You";
    cout << test7.charAt(2) << endl;

    tstring test8;
    if (test8.isEmpty())
    {
        cout << "我想看到你!" << endl;
    }
    else
    {
        cout << "I want look you!" << endl;
    }

    tstring test9 = "I love you!";
    tstring test10 = "I Love You!";
    tstring test11 = "I Love You!!";
    if (test9.compareIgnoreCase(test10))
    {
        cout << "me too" << endl;
    }
    if (test10.compareIgnoreCase(test11))
    {
        cout << "me too too " << endl;
    }
    if (test9.compareIgnoreCase(test11))
    {
        cout << "me too too!! " << endl;
    }

    cout << test11.find("Love") << endl;

    tstring test15 = "windSnowLi", test16;
    test15 >> test16;
    cout << test16 << endl;

    tstring test17;
    test17 += test16;
    cout << "LOVE\t" << test17 << endl;

    tstring test18 = "I ";
    test18 += "LOVE ";
    cout << test18 << endl;

    tstring test12;
    test12 << "我爱你";
    tstring test13 = "我喜欢你";
    tstring test14 = test12 + test13;
    cout << test14 << endl;

    cout << "*********************" << endl;
    tstring test19 = "ILoveYouILoveYouILoveYouILoveYouILoveYouILoveYouILoveYouILoveYou";

    istringstream is(test19.cstr());

    tstring test20;
    is >> test20;
    cout << test20 << endl;

    cout << test11.getLength() << "\t" << strlen(test11.cstr()) << endl;
    char a = '5';
    char tt[2];
    tstring temp22 = "I Love Yo";
    temp22 = temp22 + 'u';
    cout << temp22 << endl;
    tstring aaa;
    cout << aaa;
    cout << test19.getMaxSize() << "\t" << test19.getLength() << endl;
    cout << test11.getMaxSize() << "\t" << test11.getLength() << endl;
    cout << test19.getMD5() << endl;

    tstring test23;
    test23 += "I Love You。";
    cout << test23 << endl;
    test23[10] = '.';
    cout << test23 << endl;

    std::string test24 = "windSnowLi";
    cout << test24 << endl;


    tstring test25 = test24;
    tstring test26(test24);
    test26 += test24;
    cout << test25 << "\t||\t" << test26 << endl;

    tstring test27 = "aab";
    char *test28 = (char *)test27.cstr();
    test28[2] = 'a';
    cout << test28 << endl;

    test19.replace("ILoveYou", " I LOVE YOU");
    cout << test19 << endl;
    test19.replace("LOVE", "");
    cout << test19 << endl;

    tstring test29;
    test29 += 'a';
    cout << test29 << endl;
    tstring test30;
    test30 = toTstring(125.5);
    cout << test30 << endl;
    cout << "end" << endl;
    getchar();
    return 0;
}
