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
}

TEST(STRING, FILL_CONSTRUCTOR)
{
    stlcontainer::String s(3, 'a');
    ASSERT_TRUE(s.size() == 3);
    ASSERT_TRUE(s.length() == 3);
    ASSERT_TRUE(s[0] == 'a');
    ASSERT_TRUE(s[1] == 'a');
    ASSERT_TRUE(s[2] == 'a');

    std::string sTest = "aaa";

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sTest[index]);
    }
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

    std::string sTest = "aaa";
    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sTest[index]);
    }
}


TEST(STRING, INIT_LIST_CONSTRUCTOR)
{
    stlcontainer::String s({'m', 'y', 's', 't', 'r', 'i', 'n', 'g'});
    std::string sTest({'m', 'y', 's', 't', 'r', 'i', 'n', 'g'});

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sTest[index]);
    }
    ASSERT_TRUE(s.size() == 8);
    ASSERT_TRUE(s.length() == 8);

}

TEST(STRING, C_STR_CONSTRUCTOR)
{
    const char* char_array("mystring");
    stlcontainer::String s(char_array);
    std::string sTest(char_array);

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sTest[index]);
    }
    ASSERT_TRUE(s.size() == 8);
    ASSERT_TRUE(s.length() == 8);

}

TEST(STRING, BUFFER_CONSTRUCTOR)
{
    const char* char_array("mystring");
    size_t count = 6; 

    stlcontainer::String s(char_array, count);
    std::string sTest(char_array, count);

    for (auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], sTest[index]);
    }
    ASSERT_TRUE(s.size() == 6);
    ASSERT_TRUE(s.length() == 6);

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
}

// ------------------------------------------------------------------
// Member Functions: Assignment Operators
// ------------------------------------------------------------------
TEST(STRING, COPY_ASSIGNMENT)
{
    stlcontainer::String s("mystring");
    std::string compareStr("mystring");

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], compareStr[index]);
    }

    stlcontainer::String rval_str("mystringtwo");    
    std::string compareRvalStr("mystringtwo");
    s = rval_str;
    compareStr = compareRvalStr;

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], compareStr[index]);
    }

    ASSERT_TRUE(s.size() == compareStr.size());
}

TEST(STRING, MOVE_ASSIGNMENT)
{
    stlcontainer::String s("mystring");
    std::string compareStr("mystring");

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], compareStr[index]);
    }

    stlcontainer::String lval_str("mystringtwo");    
    std::string compareLvalStr("mystringtwo");
    s = std::move(lval_str);
    compareStr = std::move(compareLvalStr);

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], compareStr[index]);
    }

    ASSERT_TRUE(s.size() == compareStr.size());
}

TEST(STRING, C_STR_ASSIGNMENT)
{
    stlcontainer::String s("mystring");
    std::string compareStr("mystring");

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], compareStr[index]);
    }

   const char* char_array("mystringtwo");    
    s = char_array;
    compareStr = char_array;

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], compareStr[index]);
    }

    ASSERT_TRUE(s.size() == compareStr.size());
    ASSERT_EQ(11, s.size());
}

TEST(STRING, CHAR_ASSIGNMENT)
{
    stlcontainer::String s("mystring");
    std::string compareStr("mystring");

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], compareStr[index]);
    }

    const char oneChar = 'b';    
    s = oneChar;
    compareStr = oneChar;

    ASSERT_TRUE(s[0] == compareStr[0]);
    ASSERT_TRUE(s.size() == compareStr.size());
    ASSERT_EQ(1, s.size());
}

TEST(STRING, INIT_LIST_ASSIGNMENT)
{
    stlcontainer::String s("mystring");
    std::string compareStr("mystring");

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], compareStr[index]);
    }

    s = {'c', 'h', 'a', 'r', 's'};
    compareStr ={'c', 'h', 'a', 'r', 's'};

    for(auto index = 0; index < s.size(); ++index)
    {
        ASSERT_EQ(s[index], compareStr[index]);
    }

    ASSERT_TRUE(s.size() == compareStr.size());
    ASSERT_EQ(5, s.size());
}


// ------------------------------------------------------------------
// Element Access
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

// ------------------------------------------------------------------
// Member Functions: Operations
// ------------------------------------------------------------------
// TEST(STRING, CLEAR)
// {

// }

// TEST(STRING, INSERT)
// {

// }

// TEST(STRING, ERASE)
// {

// }

// TEST(STRING, PUSH_BACK)
// {

// }

// TEST(STRING, POP_BACK)
// {

// }

// TEST(STRING, APPEND)
// {

// }

// TEST(STRING, PLUS_EQUALS_OPERATOR)
// {

// }

// TEST(STRING, REPLACE)
// {

// }

// TEST(STRING, SUBSTR)
// {

// }

// TEST(STRING, COPY)
// {

// }

// TEST(STRING, RESIZE)
// {

// }

// TEST(STRING, SWAP)
// {

// }


// ------------------------------------------------------------------
// Member Functions: Search
// ------------------------------------------------------------------
// TEST(STRING, FIND)
// {

// }

// ------------------------------------------------------------------
// Non-Member Functions
// ------------------------------------------------------------------
// TEST(STRING, CONCATENATION_OPERATOR)
// {

// }

// TEST(STRING, STRSWAP)
// {

// }

// TEST(STRING, STRERASE)
// {

// }

// TEST(STRING, RELATIONAL_OPERATORS)
// {

// }

// TEST(STRING, STRINGSTREAM)
// {

// }





