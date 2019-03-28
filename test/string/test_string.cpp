#include <string>

#include <gtest/gtest.h>
#include "string/String.h"

// ------------------------------------------------------------------
// Member Functions: Constructors
// ------------------------------------------------------------------
TEST(STRING, EMPTY_CREATION)
{
    stlcontainer::String s;
    ASSERT_TRUE(s.size() == 0);
    ASSERT_TRUE(s.length() == 0);

    std::string sCompare;
    ASSERT_EQ(s.capacity(), sCompare.capacity());
}

TEST(STRING, FILL_CONSTRUCTOR)
{
    stlcontainer::String s(3, 'a');
    ASSERT_TRUE(s.size() == 3);
    ASSERT_TRUE(s.length() == 3);
    ASSERT_TRUE(s[0] == 'a');
    ASSERT_TRUE(s[1] == 'a');
    ASSERT_TRUE(s[2] == 'a');

    std::string sCompare = "aaa";

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }
    ASSERT_EQ(s.capacity(), sCompare.capacity());

    stlcontainer::String s2(17, 'a');
    std::string sCompare2(17, 'a');
    ASSERT_EQ(s2.capacity(), sCompare2.capacity());
}

TEST(STRING, COPY_CONSTRUCTOR)
{
    stlcontainer::String sBase(3, 'a');
    
    stlcontainer::String s(sBase);

    ASSERT_TRUE(s.size() == 3);
    ASSERT_TRUE(s.length() == 3);
    ASSERT_TRUE(s[0] == 'a');
    ASSERT_TRUE(s[1] == 'a');
    ASSERT_TRUE(s[2] == 'a');

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sBase[index]);
    }

    std::string sCompare = "aaa";
    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }
    ASSERT_EQ(s.capacity(), sCompare.capacity());
}


TEST(STRING, INIT_LIST_CONSTRUCTOR)
{
    stlcontainer::String s({'m', 'y', 's', 't', 'r', 'i', 'n', 'g'});
    std::string sCompare({'m', 'y', 's', 't', 'r', 'i', 'n', 'g'});

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }
    ASSERT_TRUE(s.size() == 8);
    ASSERT_TRUE(s.length() == 8);
    ASSERT_EQ(s.capacity(), sCompare.capacity());
}

TEST(STRING, C_STR_CONSTRUCTOR)
{
    stlcontainer::String s("mystring");
    std::string sCompare("mystring");

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }
    ASSERT_TRUE(s.size() == 8);
    ASSERT_TRUE(s.length() == 8);
    ASSERT_EQ(s.capacity(), sCompare.capacity());
}

TEST(STRING, BUFFER_CONSTRUCTOR)
{
    const char* char_array("mystring");
    size_t count = 6; 

    stlcontainer::String s(char_array, count);
    std::string sCompare(char_array, count);

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }
    ASSERT_TRUE(s.size() == 6);
    ASSERT_TRUE(s.length() == 6);
    ASSERT_EQ(s.capacity(), sCompare.capacity());
}

TEST(STRING, MOVE_CONSTRUCTOR)
{
    stlcontainer::String moveStr("mystring");
    auto savedCount = moveStr.size();
    auto savedCapacity = moveStr.capacity();
    auto savedElems = moveStr.data();

    stlcontainer::String s(std::move(moveStr));

    ASSERT_EQ(savedCount, s.size());
    ASSERT_EQ(savedCapacity, s.capacity());
    ASSERT_EQ(savedElems, s.data());

    std::string compareMoveStr("mystring");
    std::string sCompare(std::move(compareMoveStr));
    ASSERT_EQ(s.size(), sCompare.size());
    ASSERT_EQ(s.capacity(), sCompare.capacity());
    ASSERT_EQ(*(s.data()), *(sCompare.data()));
}

TEST(STRING, SUBSTR_CONSTRUCTOR)
{
    size_t pos = 2;
    size_t count = 6;
    stlcontainer::String sSubstring({'m', 'y', 's', 't', 'r', 'i', 'n', 'g'});
    stlcontainer::String s(sSubstring, pos, count);

    std::string sCompareSubstring("mystring");
    std::string sCompare(sCompareSubstring, pos, count);

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sSubstring[index + pos]);
        ASSERT_EQ(s[index], sCompare[index]);
    }
    ASSERT_TRUE(s.size() == count);
    ASSERT_TRUE(s.length() == count);
    ASSERT_EQ(s.capacity(), sCompare.capacity());

    pos = 0;
    count = 2;
    stlcontainer::String s2(sSubstring, pos, count);
    std::string sCompare2(sCompareSubstring, pos, count);

    for (auto index = 0; index < s2.size(); ++index)
    {
        ASSERT_EQ(s2[index], sSubstring[index + pos]);
        ASSERT_EQ(s2[index], sCompare2[index]);
    }
    ASSERT_TRUE(s2.size() == count);
    ASSERT_TRUE(s2.length() == count);
    ASSERT_EQ(s2.capacity(), sCompare2.capacity());

    // Test default arg count = npos
    pos = 0;
    count = 8;
    stlcontainer::String s3(sSubstring, pos);
    std::string sCompare3(sCompareSubstring, pos);

    for (auto index = 0; index < s3.size(); ++index)
    {
        ASSERT_EQ(s3[index], sSubstring[index + pos]);
        ASSERT_EQ(s3[index], sCompare3[index]);
    }
    ASSERT_TRUE(s3.size() == count);
    ASSERT_TRUE(s3.length() == count);
    ASSERT_EQ(s3.capacity(), sCompare3.capacity());

    // Test when pos + count goes past end of substring
    pos = 0;
    count = 120;
    stlcontainer::String s4(sSubstring, pos, count);
    std::string sCompare4(sCompareSubstring, pos, count);

    for (auto index = 0; index < s4.size(); ++index)
    {
        ASSERT_EQ(s4[index], sSubstring[index + pos]);
        ASSERT_EQ(s4[index], sCompare4[index]);
    }
    ASSERT_TRUE(s4.size() == sSubstring.length());
    ASSERT_TRUE(s4.length() == sSubstring.length());
    ASSERT_EQ(s4.capacity(), sCompare4.capacity());
}

// ------------------------------------------------------------------
// Member Functions: Assignment Operators
// ------------------------------------------------------------------
TEST(STRING, COPY_ASSIGNMENT)
{
    stlcontainer::String s("mystring");
    std::string sCompare("mystring");

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }

    stlcontainer::String rval_str("mystringtwo");    
    std::string compareRvalStr("mystringtwo");
    s = rval_str;
    sCompare = compareRvalStr;

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }

    ASSERT_EQ(s.size(), sCompare.size());
    ASSERT_EQ(s.capacity(), sCompare.capacity());
}

TEST(STRING, MOVE_ASSIGNMENT)
{
    stlcontainer::String s("mystring");
    std::string sCompare("mystring");

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }

    stlcontainer::String lval_str("mystringtwo");    
    std::string compareLvalStr("mystringtwo");
    s = std::move(lval_str);
    sCompare = std::move(compareLvalStr);

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }

    ASSERT_EQ(s.size(), sCompare.size());
    ASSERT_EQ(s.capacity(), sCompare.capacity());
}

TEST(STRING, C_STR_ASSIGNMENT)
{
    stlcontainer::String s("mystring");
    std::string sCompare("mystring");

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }

    const char* char_array("mystringtwo");    
    s = char_array;
    sCompare = char_array;

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }

    ASSERT_EQ(11, s.size());
    ASSERT_EQ(s.size(), sCompare.size());
    ASSERT_EQ(s.capacity(), sCompare.capacity());
}

TEST(STRING, CHAR_ASSIGNMENT)
{
    stlcontainer::String s("mystring");
    std::string sCompare("mystring");

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }

    const char oneChar = 'b';    
    s = oneChar;
    sCompare = oneChar;

    ASSERT_TRUE(s[0] == sCompare[0]);
    ASSERT_EQ(s.size(), sCompare.size());
    ASSERT_EQ(s.capacity(), sCompare.capacity());
    ASSERT_EQ(1, s.size());
}

TEST(STRING, INIT_LIST_ASSIGNMENT)
{
    stlcontainer::String s("mystring");
    std::string sCompare("mystring");

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }

    s = {'c', 'h', 'a', 'r', 's'};
    sCompare ={'c', 'h', 'a', 'r', 's'};

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }

    ASSERT_EQ(s.size(), sCompare.size());
    ASSERT_EQ(5, s.size());
    ASSERT_EQ(s.capacity(), sCompare.capacity());
}

// ------------------------------------------------------------------
// Member Functions: Assignment Operators
// ------------------------------------------------------------------
TEST(STRING, ASSIGN_STRING)
{
    stlcontainer::String s("mystring");
    std::string sCompare("mystring");
    stlcontainer::String sAssign("anotherstring");
    std::string sCompareAssign("anotherstring");
    
    s.assign(sAssign);
    sCompare.assign(sCompareAssign);
    
    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    } 
    ASSERT_EQ(s.size(), sCompare.size());
    ASSERT_EQ(s.capacity(), sCompare.capacity());
}

TEST(STRING, ASSIGN_SUBSTR)
{
    stlcontainer::String s("mystring");
    std::string sCompare("mystring");
    stlcontainer::String sAssign("anotherstring");
    std::string sCompareAssign("anotherstring");
    
    size_t pos = 1;
    size_t count = 3;
    s.assign(sAssign, pos, count);
    sCompare.assign(sCompareAssign, pos, count);
    
    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    } 
    ASSERT_EQ(s.size(), sCompare.size());
    ASSERT_EQ(s.capacity(), sCompare.capacity());

    // Check count + pos > str.size()
    pos = 5;
    count = 8;
    s.assign(sAssign, pos, count);
    sCompare.assign(sCompareAssign, pos, count);
    
    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    } 

    // Check defaulting count
    pos = 0;
    s.assign(sAssign, pos);
    
    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sAssign[index]);
    } 
}

TEST(STRING, ASSIGN_CSTR)
{
    stlcontainer::String s("mystring");
    std::string sCompare("mystring");
    const char* charArray("helloworld");
    
    s.assign(charArray);
    sCompare.assign(charArray);
    
    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    } 
    ASSERT_EQ(s.size(), sCompare.size());
    ASSERT_EQ(s.capacity(), sCompare.capacity());
}

TEST(STRING, ASSIGN_BUFFER)
{
    stlcontainer::String s("mystring");
    std::string sCompare("mystring");
    const char* charArray("helloworld");
    size_t count = 4;
    
    s.assign(charArray, count);
    sCompare.assign(charArray, count);
    
    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }
    ASSERT_EQ(s.size(), sCompare.size());
    ASSERT_EQ(s.capacity(), sCompare.capacity());
}

TEST(STRING, ASSIGN_FILL)
{
    stlcontainer::String s("mystring");
    std::string sCompare("mystring");
    size_t count = 100;
    char ch = 'g';

    s.assign(count, ch);
    sCompare.assign(count, ch);
    
    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }
    ASSERT_EQ(s.size(), sCompare.size());
    ASSERT_EQ(s.capacity(), sCompare.capacity());
}

// ------------------------------------------------------------------
// Member Functions: Element Access
// ------------------------------------------------------------------
TEST(STRING, BRACKETS)
{
    stlcontainer::String s("mystring");
    ASSERT_EQ(s[0], 'm');
    ASSERT_EQ(s[1], 'y');
    ASSERT_EQ(s[2], 's');
    ASSERT_EQ(s[3], 't');
    ASSERT_NO_THROW(s[99]);
}

TEST(STRING, AT)
{
    stlcontainer::String s("mystring");
    ASSERT_EQ(s.at(0), 'm');
    ASSERT_EQ(s.at(1), 'y');
    ASSERT_EQ(s.at(2), 's');
    ASSERT_EQ(s.at(3), 't');
    ASSERT_THROW(s.at(99), std::out_of_range);
}

TEST(STRING, FRONT_AND_BACK)
{
    stlcontainer::String s("mystring");
    ASSERT_EQ(s.front(), 'm');
    ASSERT_EQ(s.back(), 'g');
}

TEST(STRING, DATA)
{
    stlcontainer::String s("mystring");
    std::string sCompare("mystring");
    
    auto data = s.data();
    auto compareData = sCompare.data();

    while (*data)
    {
        ASSERT_EQ(*(++data), *(++compareData));
    }
}

TEST(STRING, CSTR)
{
    stlcontainer::String s("mystring");
    std::string sCompare("mystring");
    auto cstr = s.c_str();
    auto compareCstr = sCompare.c_str();

    while (*cstr)
    {
        ASSERT_EQ(*(++cstr), *(++compareCstr));
    }
}

// ------------------------------------------------------------------
// Iterators
// ------------------------------------------------------------------
// TEST(STRING, BEGIN_END)
// {
//     // TODO
// }

// ------------------------------------------------------------------
// Member Functions: Capacity
// ------------------------------------------------------------------
TEST(STRING, EMPTY)
{
    stlcontainer::String s("mystring");
    ASSERT_FALSE(s.empty());

    stlcontainer::String s2;
    ASSERT_TRUE(s2.empty());
}

TEST(STRING, SIZE_LENGTH)
{
    stlcontainer::String s("mystring");
    ASSERT_TRUE(s.size() == 8);
    ASSERT_TRUE(s.length() == 8);
    
    s = 's';
    ASSERT_TRUE(s.size() == 1);
    ASSERT_TRUE(s.length() == 1);

    s = "qwertyuiopasdfghjklzxcvbnm";
    ASSERT_TRUE(s.size() == 26);
    ASSERT_TRUE(s.length() == 26);
}

TEST(STRING, SHRINK_TO_FIT)
{
    stlcontainer::String s(100, 'x');
    s.resize(10);
    ASSERT_TRUE(s.capacity() > s.size());    
    s.shrink_to_fit();
    ASSERT_TRUE(s.capacity() == s.size());
}

// ------------------------------------------------------------------
// Member Functions: Operations
// ------------------------------------------------------------------
int return_zero_elem(char* elems)
{
    return elems[0];
}

TEST(STRING, CLEAR)
{
    stlcontainer::String s("mystring");
    s.clear();

    ASSERT_TRUE(s.size() == 0);
    ASSERT_TRUE(s.empty());
    
    // Should seg fault
    auto elems = s.data();
    ASSERT_EXIT(return_zero_elem(elems), ::testing::KilledBySignal(SIGSEGV), ".*");

}

TEST(STRING, INSERT)
{
    stlcontainer::String s = "string";
    std::string sCompare = "string";
    s.insert(4, "HERE");
    sCompare.insert(4, "HERE");
    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }
    ASSERT_EQ(s.size(), sCompare.size());
    ASSERT_EQ(s.capacity(), sCompare.capacity());
}

// TEST(STRING, ERASE)
// {

// }

TEST(STRING, PUSH_BACK)
{   
    stlcontainer::String s;
    s.push_back('h');
    s.push_back('e');
    s.push_back('l');
    s.push_back('l');
    s.push_back('o');

    std::string sCompare;
    sCompare.push_back('h');
    sCompare.push_back('e');
    sCompare.push_back('l');
    sCompare.push_back('l');
    sCompare.push_back('o');

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }

    ASSERT_TRUE(s.size() == 5);
    ASSERT_EQ(s.capacity(), sCompare.capacity());
}

TEST(STRING, POP_BACK)
{
    stlcontainer::String s("hello");
    std::string sCompare("hel");

    s.pop_back();
    s.pop_back();

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }

    ASSERT_TRUE(s.size() == 3);
    ASSERT_EQ(s.size(), sCompare.size());
    ASSERT_EQ(s.capacity(), sCompare.capacity());
}   

TEST(STRING, APPEND)
{
    stlcontainer::String s("abc");
    stlcontainer::String appendMe("defg");
    stlcontainer::String sCompare("abcdefg");
    s.append(appendMe);

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    } 
    ASSERT_TRUE(s.size() == sCompare.size());

    sCompare = "abcdefghij";
    appendMe = "hij";
    size_t pos = 0;
    size_t count = 3;
    s.append(appendMe, pos, count);

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    } 
    ASSERT_TRUE(s.size() == sCompare.size());

    sCompare = "abcdefghijklm";
    appendMe = "88klm";
    pos = 2;
    s.append(appendMe, pos);

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    } 
    ASSERT_TRUE(s.size() == sCompare.size());

    const char* appendCharStr("nop");
    sCompare = "abcdefghijklmnop";
    s.append(appendCharStr);
    
    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }
    ASSERT_TRUE(s.size() == sCompare.size());

    const char* appendCharStr2("qrs444434");
    sCompare = "abcdefghijklmnopqrs";
    s.append(appendCharStr2, 3);
    
    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }
    ASSERT_TRUE(s.size() == sCompare.size());

    char appendChar = 't'; 
    sCompare = "abcdefghijklmnopqrst";
    s.append(1, appendChar);
    
    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }
    ASSERT_TRUE(s.size() == sCompare.size());

    sCompare = "abcdefghijklmnopqrstuvwxyz";
    s.append({'u', 'v', 'w', 'x', 'y', 'z'});

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }
    ASSERT_TRUE(s.size() == sCompare.size());    
}

TEST(STRING, PLUS_EQUALS_OPERATOR)
{
    stlcontainer::String s("abc");
    stlcontainer::String appendMe("defg");
    stlcontainer::String sCompare("abcdefg");
    s += appendMe;

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    } 
    ASSERT_TRUE(s.size() == sCompare.size());
}

TEST(STRING, REPLACE)
{
    stlcontainer::String s("replaceXXXX!");
    stlcontainer::String replacementStr("here");
    stlcontainer::String sCompare = "replacehere!";
    s.replace(7, 4, replacementStr);

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    } 
    ASSERT_EQ(s.size(), sCompare.size());


    std::string stlstr = "replaceXXXX!";
    stlstr.replace(7, 2, "ABCDEFGHI");

    s = "replaceXXXX!";
    replacementStr = "ABCDEFGHI";
    s.replace(7, 2, replacementStr);
    
    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], stlstr[index]);
    } 
    ASSERT_EQ(s.size(), stlstr.size());
}

TEST(STRING, SUBSTR_REPLACE)
{
    stlcontainer::String s("replaceXXXX!");
    stlcontainer::String replacementStr("ABCDEFG");
    std::string sCompare = "replaceXXXX!";
    std::string compareReplacementStr = "ABCDEFG";

    // Compare when count == count2
    s.replace(7, 4, replacementStr, 0, 4);
    sCompare.replace(7, 4, compareReplacementStr, 0, 4);

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    } 
    ASSERT_EQ(s.size(), sCompare.size());

    // Compare when count < count2
    s = "replaceXXXX!"; sCompare = "replaceXXXX!";
    s.replace(7, 4, replacementStr, 0, 5);
    sCompare.replace(7, 4, compareReplacementStr, 0, 5);

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    } 
    ASSERT_EQ(s.size(), sCompare.size());

    // Compare when count > count2
    s = "replaceXXXX!"; sCompare = "replaceXXXX!";
    s.replace(7, 4, replacementStr, 2, 4);
    sCompare.replace(7, 4, compareReplacementStr, 2, 4);

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    } 
    ASSERT_EQ(s.size(), sCompare.size());
}

TEST(STRING, CSTR_REPLACE)
{
    stlcontainer::String s("replaceXXXX!");
    stlcontainer::String sCompare = "replacehere!";
    s.replace(7, 4, "here");

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    } 
    ASSERT_EQ(s.size(), sCompare.size());

    std::string stlstr = "replaceXXXX!";
    stlstr.replace(7, 2, "ABCDEFGHI");

    s = "replaceXXXX!";
    s.replace(7, 2, "ABCDEFGHI");
    
    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], stlstr[index]);
    } 
    ASSERT_EQ(s.size(), stlstr.size());
}

TEST(STRING, BUFFER_REPLACE)
{
    stlcontainer::String s("replaceXXXX!");
    std::string sCompare = "replaceXXXX!";

    // Compare when count == count2
    s.replace(7, 4, "ABCDEFG", 4);
    sCompare.replace(7, 4, "ABCDEFG", 4);
    
    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    } 
    ASSERT_EQ(s.size(), sCompare.size());
    ASSERT_EQ(s.capacity(), sCompare.capacity());

    // Compare when count < count2
    s = "replaceXXXX!"; sCompare = "replaceXXXX!";
    s.replace(7, 4, "ABCDEFG", 5);
    sCompare.replace(7, 4, "ABCDEFG", 5);
    

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    } 
    ASSERT_EQ(s.size(), sCompare.size());
    ASSERT_EQ(s.capacity(), sCompare.capacity());

    // Compare when count > count2
    s.replace(7, 4, "ABCDEFG", 2);
    sCompare.replace(7, 4, "ABCDEFG", 2);

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    } 
    ASSERT_EQ(s.size(), sCompare.size());
    ASSERT_EQ(s.capacity(), sCompare.capacity());
}

TEST(STRING, FILL_REPLACE)
{
    stlcontainer::String s("replacehere!");
    const char ch = 'X';
    std::string sCompare = "replacehere!";

    // Compare when count == count2
    s.replace(7, 4, ch, 4);
    sCompare.replace(7, 4, ch, 4);

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    } 
    ASSERT_EQ(s.size(), sCompare.size());

    // Compare when count < count2
    s = "replacehere!"; sCompare = "replacehere!";
    s.replace(7, 4, ch, 5);
    sCompare.replace(7, 4, ch, 5);
    

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    } 
    ASSERT_EQ(s.size(), sCompare.size());

    // Compare when count > count2
    s.replace(7, 4, ch, 2);
    sCompare.replace(7, 4, ch, 2);

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    } 
    ASSERT_EQ(s.size(), sCompare.size());
}

TEST(STRING, SUBSTR)
{
    stlcontainer::String s("hello");
    auto newString = s.substr(0, 3);
    stlcontainer::String sCompare("hel");
    for(auto index = 0; index < newString.size(); ++index)
    {
        ASSERT_EQ(newString[index], sCompare[index]);
    }

    newString = s.substr(0);
    sCompare = "hello";
    for(auto index = 0; index < newString.size(); ++index)
    {
        ASSERT_EQ(newString[index], sCompare[index]);
    }
}

TEST(STRING, COPY)
{
    stlcontainer::String s("teststring");
    stlcontainer::String sCompare("tests");
    char dest[100];
    s.copy(dest, 5, 0);
    stlcontainer::String sCopied(dest);

    for(auto index = 0; index < stlcontainer::cstr_len(dest); ++index)
    {
        ASSERT_EQ(sCompare[index], sCopied[index]);
    }   
}

TEST(STRING, RESIZE)
{
    stlcontainer::String s("teststring");
    auto initialCap = s.capacity();

    s.resize(16);
    ASSERT_TRUE(s.capacity() > initialCap);
    ASSERT_TRUE(s.size() == 16);

    auto sCompareing("test");
    s.resize(4);
    ASSERT_TRUE(s.size() == 4);
    
    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompareing[index]);
    }

    auto sCompareing2("testggg");
    s.resize(7, 'g');
    ASSERT_TRUE(s.size() == 7);

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompareing2[index]);
    }
}

TEST(STRING, SWAP)
{
    stlcontainer::String s1("stringone");
    stlcontainer::String s2("stringtwo");
    std::string sCompare1("stringone");
    std::string sCompare2("stringtwo");

    s1.swap(s2);
    ASSERT_TRUE(s1.size() == sCompare2.size());
    for(auto index = 0; index < s1.size(); ++index)
    {
        ASSERT_EQ(s1[index], sCompare2[index]);
    }

    ASSERT_TRUE(s2.size() == sCompare1.size());
    for(auto index = 0; index < s2.size(); ++index)
    {
        ASSERT_EQ(s2[index], sCompare1[index]);
    }
}


// ------------------------------------------------------------------
// Member Functions: Search
// ------------------------------------------------------------------
// TEST(STRING, FIND)
// {

// }

// ------------------------------------------------------------------
// Non-Member Functions
// ------------------------------------------------------------------
TEST(STRING, CONCATENATION_OPERATOR)
{
    stlcontainer::String s1("string");
    stlcontainer::String s2("!");

    auto s = s1 + s2;

    std::string sCompare1("string");
    std::string sCompare2("!");

    auto sCompare = sCompare1 + sCompare2;

    ASSERT_EQ(s.size(), sCompare.size());
    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }

    s = s + "!";
    sCompare = sCompare + "!";

    ASSERT_EQ(s.size(), sCompare.size());
    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }

    s = s + 'a';
    sCompare = sCompare + 'a';

    ASSERT_EQ(s.size(), sCompare.size());
    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sCompare[index]);
    }
}

TEST(STRING, STRSWAP)
{
    stlcontainer::String s1("stringone");
    stlcontainer::String s2("stringtwo");
    std::string sCompare1("stringone");
    std::string sCompare2("stringtwo");

    stlcontainer::swap(s1, s2);
    std::swap(sCompare1, sCompare2);

    ASSERT_TRUE(s1.size() == sCompare1.size());
    for(auto index = 0; index < s1.size(); ++index)
    {
        ASSERT_EQ(s1[index], sCompare1[index]);
    }

    ASSERT_TRUE(s2.size() == sCompare2.size());
    for(auto index = 0; index < s2.size(); ++index)
    {
        ASSERT_EQ(s2[index], sCompare2[index]);
    }
}

// TEST(STRING, STRERASE)
// {

// }

TEST(STRING, RELATIONAL_OPERATORS)
{
    stlcontainer::String s = "aaaaa";
    stlcontainer::String s2 = "bbbbb";
    ASSERT_TRUE(s < s2);
    ASSERT_TRUE(s <= s2);
    ASSERT_TRUE(s != s2);
    ASSERT_FALSE(s > s2);
    ASSERT_FALSE(s >= s2);
    ASSERT_FALSE(s == s2);
}




