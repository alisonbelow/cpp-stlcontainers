#include <forward_list>

#include <gtest/gtest.h>
#include "forward_list/ForwardList.h"

TEST(FORWARD_LIST, EMPTY_CREATION_DEFAULT_CONSTRUCTOR)
{
    stlcontainer::ForwardList<int> list;
    std::forward_list<int> listCompare;

    ASSERT_EQ(list.empty(), listCompare.empty());
}

TEST(FORWARD_LIST, FILL_CONSTRUCTOR)
{
    stlcontainer::ForwardList<int> list(5, 6);
    std::forward_list<int> listCompare(5, 6);

    auto compareIter = listCompare.begin();
    auto iter = list.begin();
    while(iter != list.end())
    {
        ASSERT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
    }
}

TEST(FORWARD_LIST, COPY_CONSTRUCTOR)
{
    stlcontainer::ForwardList<int> listCopyee(5, 6);
    std::forward_list<int> listCompareCopyee(5, 6);
    stlcontainer::ForwardList<int> list(listCopyee);
    std::forward_list<int> listCompare(listCompareCopyee);

    auto compareIter = listCompare.begin();
    auto iter = list.begin();
    while(iter != list.end())
    {
        ASSERT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
    }
}

TEST(FORWARD_LIST, MOVE_CONSTRUCTOR)
{
    stlcontainer::ForwardList<int> listMovee(5, 6);
    std::forward_list<int> listCompareMovee(5, 6);
    stlcontainer::ForwardList<int> list(std::move(listMovee));
    std::forward_list<int> listCompare(std::move(listCompareMovee));

    auto compareIter = listCompare.begin();
    auto iter = list.begin();
    while(iter != list.end())
    {
        ASSERT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
    }
}

TEST(FORWARD_LIST, INITLIST_CONSTRUCTOR)
{
    stlcontainer::ForwardList<int> list({5, 6, 3, 6, 8, 1});
    std::forward_list<int> listCompare({5, 6, 3, 6, 8, 1});

    auto compareIter = listCompare.begin();
    auto iter = list.begin();
    while(iter != list.end())
    {
        ASSERT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
    }
}

TEST(FORWARD_LIST, CLEAR)
{
    stlcontainer::ForwardList<int> list({5, 6, 3, 6, 8, 1});
    std::forward_list<int> listCompare({5, 6, 3, 6, 8, 1});

    list.clear();
    listCompare.clear();
    ASSERT_EQ(list.empty(), listCompare.empty());
}

TEST(FORWARD_LIST, ASSIGN_OPERATOR)
{
    stlcontainer::ForwardList<int> list({5, 6, 3, 6, 8, 1});
    std::forward_list<int> listCompare({5, 6, 3, 6, 8, 1});

    list = {8,4,3};
    listCompare = {8,4,3};

    ASSERT_EQ(list.front(), 8);
    ASSERT_EQ(list.front(), listCompare.front());

    stlcontainer::ForwardList<int> listCopy({5, 6, 3, 6, 8, 1});
    std::forward_list<int> listCompareCopy({5, 6, 3, 6, 8, 1});

    list = listCopy;
    listCompare = listCompareCopy;

    ASSERT_EQ(list.front(), 5);
    ASSERT_EQ(list.front(), listCompare.front());

    stlcontainer::ForwardList<int> listMove({1, 2, 3, 4, 5});
    std::forward_list<int> listCompareMove({1, 2, 3, 4, 5});

    list = std::move(listMove);
    listCompare = std::move(listCompareMove);

    ASSERT_EQ(list.front(), 1);
    ASSERT_EQ(list.front(), listCompare.front());
}

TEST(FORWARD_LIST, ASSIGN)
{
    stlcontainer::ForwardList<int> list({5, 6, 3, 6, 8, 1});
    std::forward_list<int> listCompare({5, 6, 3, 6, 8, 1});

    // Test fill assign
    list.assign(4, 3);
    listCompare.assign(4, 3);
    ASSERT_EQ(list.front(), 3);
    ASSERT_EQ(list.front(), listCompare.front());

    // Test init list assign
    list.assign({4, 3});
    listCompare.assign({4, 3});
    ASSERT_EQ(list.front(), 4);
    ASSERT_EQ(list.front(), listCompare.front());    
}

TEST(FORWARD_LIST, ITERATORS)
{
    stlcontainer::ForwardList<int> list({0, 4, 6, 2, 3});
    std::forward_list<int> listCompare({0, 4, 6, 2, 3});

    ASSERT_EQ(*list.begin(), *listCompare.begin());
}

TEST(FORWARD_LIST, INSERT_AFTER)
{
    stlcontainer::ForwardList<int> list({0, 4, 6, 2, 3});
    std::forward_list<int> listCompare({0, 4, 6, 2, 3});

    // Test copy insert
    list.insert_after(list.begin(), 88);
    listCompare.insert_after(listCompare.begin(), 88);

    ASSERT_EQ(list.front(), listCompare.front());

    auto compareIter = listCompare.begin();
    auto iter = list.begin();
    auto size = 0;
    while(iter != list.end())
    {
        ASSERT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
        ++size;
    }
    ASSERT_EQ(size, 6);

    // Test move insert
    list.insert_after(list.begin(), std::move(7));
    listCompare.insert_after(listCompare.begin(), std::move(7));

    ASSERT_EQ(list.front(), listCompare.front());

    compareIter = listCompare.begin();
    iter = list.begin();
    size = 0;
    while(iter != list.end())
    {
        ASSERT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
        ++size;
    }
    ASSERT_EQ(size, 7);

    // Test fill insert
    list.insert_after(list.begin(), 4, 2);
    listCompare.insert_after(listCompare.begin(), 4, 2);

    ASSERT_EQ(list.front(), listCompare.front());

    compareIter = listCompare.begin();
    iter = list.begin();
    size = 0;
    while(iter != list.end())
    {
        ASSERT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
        ++size;
    }
    ASSERT_EQ(size, 11);

    // Test range insert
    stlcontainer::ForwardList<int> testList = {0,1,2};
    std::forward_list<int> testListCompare = {0,1,2};

    list.insert_after(list.begin(), testList.begin(), testList.end());
    listCompare.insert_after(listCompare.begin(), testListCompare.begin(), testListCompare.end());

    ASSERT_EQ(list.front(), listCompare.front());

    compareIter = listCompare.begin();
    iter = list.begin();
    size = 0;
    while(iter != list.end())
    {
        EXPECT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
        ++size;
    }
    ASSERT_EQ(size, 14);

    // Test init list insert
    list.insert_after(list.begin(), {4,5});
    listCompare.insert_after(listCompare.begin(), {4,5});

    ASSERT_EQ(list.front(), listCompare.front());

    compareIter = listCompare.begin();
    iter = list.begin();
    size = 0;
    while(iter != list.end())
    {
        EXPECT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
        ++size;
    }
    ASSERT_EQ(size, 16);
}

TEST(FORWARD_LIST, ERASE_AFTER)
{
    stlcontainer::ForwardList<int> list({0, 4, 6, 2, 3});
    std::forward_list<int> listCompare({0, 4, 6, 2, 3});

    list.erase_after(list.begin());
    listCompare.erase_after(listCompare.begin());

    ASSERT_EQ(list.front(), listCompare.front());
    
    auto compareIter = listCompare.begin();
    auto iter = list.begin();
    size_t size = 0;
    while(iter != list.end())
    {
        ASSERT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
        ++size;
    }
    ASSERT_EQ(size, 4);

    list = {0, 4, 6, 2, 3};
    listCompare = {0, 4, 6, 2, 3};

    iter = list.begin();
    compareIter = listCompare.begin();
    
    auto endIter = ++iter;
    endIter = ++(++endIter);
    auto compareEndIter = ++compareIter;
    compareEndIter = ++(++compareEndIter);

    list.erase_after(iter, endIter);
    listCompare.erase_after(compareIter, compareEndIter);

    size = 0;
    iter = list.begin();
    compareIter = listCompare.begin();
    while(iter != list.end())
    {
        ASSERT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
        ++size;
    }
    ASSERT_EQ(size, 4);

    list = {0, 4, 6, 2, 3};
    listCompare = {0, 4, 6, 2, 3};
    list.erase_after(list.begin(), list.end());
    listCompare.erase_after(listCompare.begin(), listCompare.end());

    size = 0;
    iter = list.begin();
    compareIter = listCompare.begin();
    while(iter != list.end())
    {
        ASSERT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
        ++size;
    }
    ASSERT_EQ(size, 1);
}

TEST(FORWARD_LIST, PUSH_FRONT)
{
    stlcontainer::ForwardList<int> list({8, 5, 3, 2});
    std::forward_list<int> listCompare({8, 5, 3, 2});

    list.push_front(9);
    listCompare.push_front(9);

    ASSERT_EQ(list.front(), listCompare.front());

    list.push_front(std::move(10));
    listCompare.push_front(std::move(10));

    ASSERT_EQ(list.front(), listCompare.front());
}

TEST(FORWARD_LIST, POP_FRONT)
{
    stlcontainer::ForwardList<int> list({8, 5, 3, 2});
    std::forward_list<int> listCompare({8, 5, 3, 2});

    list.pop_front();
    listCompare.pop_front();

    ASSERT_EQ(list.front(), listCompare.front());
    ASSERT_EQ(list.front(), 5);
}

TEST(FORWARD_LIST, RESIZE)
{
    stlcontainer::ForwardList<int> list({8, 5, 3, 2});
    std::forward_list<int> listCompare({8, 5, 3, 2});

    // Resize scenario 1 - resize smaller
    list.resize(3);
    listCompare.resize(3);
    
    auto compareIter = listCompare.begin();
    auto iter = list.begin();
    auto size = 0;
    while(compareIter != listCompare.end())
    {
        ASSERT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
        ++size;
    }
    ASSERT_EQ(size, 3);

   // Resize scenario 2 - make larger
    list.resize(8);
    listCompare.resize(8);
    // 
    compareIter = listCompare.begin();
    iter = list.begin();
    size = 0;
    while(compareIter != listCompare.end())
    {
        ASSERT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
        ++size;
    }
    ASSERT_EQ(size, 8);
}

TEST(FORWARD_LIST, SWAP)
{
    stlcontainer::ForwardList<int> list1 = {9,3,4,5};
    stlcontainer::ForwardList<int> list2 = {0,0};

    std::forward_list<int> listCompare1 = {9,3,4,5};
    std::forward_list<int> listCompare2 = {0,0};

    list1.swap(list2);
    listCompare1.swap(listCompare2);

    auto compareIter = listCompare1.begin();
    auto iter = list1.begin();
    auto size = 0;
    while(compareIter != listCompare1.end())
    {
        ASSERT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
        ++size;
    }
    ASSERT_EQ(size, 2);

    compareIter = listCompare2.begin();
    iter = list2.begin();
    size = 0;
    while(compareIter != listCompare1.end())
    {
        ASSERT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
        ++size;
    }
    ASSERT_EQ(size, 4);
}

TEST(FORWARD_LIST, MERGE)
{
    stlcontainer::ForwardList<int> list1 = {0,3,5,6};
    stlcontainer::ForwardList<int> list2 = {1,2,3,7,9,9,9};
    std::forward_list<int> list1Compare = {0,3,5,6};
    std::forward_list<int> list2Compare = {1,2,3,7,9,9,9};
    list1.merge(list2);
    list1Compare.merge(list2Compare);

    auto compareIter = list1Compare.begin();
    auto iter = list1.begin();
    auto size = 0;
    while(compareIter != list1Compare.end())
    {
        EXPECT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
        ++size;
    }
    ASSERT_EQ(size, 11);
}

TEST(FORWARD_LIST, REMOVE)
{
    stlcontainer::ForwardList<int> list = {1,9,2,3,7,9,0,9};
    std::forward_list<int> listCompare = {1,9,2,3,7,9,0,9};
    
    list.remove(9);
    listCompare.remove(9);
    
    auto compareIter = listCompare.begin();
    auto iter = list.begin();
    auto size = 0;
    while(compareIter != listCompare.end())
    {
        EXPECT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
        ++size;
    }
    ASSERT_EQ(size, 5);
}

TEST(FORWARD_LIST, REVERSE)
{
    stlcontainer::ForwardList<int> list = {1,9,2,3,7,9,0,9};
    std::forward_list<int> listCompare = {1,9,2,3,7,9,0,9};

    list.reverse();
    listCompare.reverse();

    auto compareIter = listCompare.begin();
    auto iter = list.begin();
    auto size = 0;
    while(compareIter != listCompare.end())
    {
        EXPECT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
        ++size;
    }
    ASSERT_EQ(size, 8);
}

TEST(FORWARD_LIST, UNIQUE)
{
    stlcontainer::ForwardList<int> list = {1,9,9,9,0,1,1,0,9};
    std::forward_list<int> listCompare = {1,9,9,9,0,1,1,0,9};

    list.unique();
    listCompare.unique();

    auto compareIter = listCompare.begin();
    auto iter = list.begin();
    auto size = 0;
    while(compareIter != listCompare.end())
    {
        EXPECT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
        ++size;
    }
    ASSERT_EQ(size, 6);

    list = {3,4,4,5,1,6,6,6};
    listCompare = {3,4,4,5,1,6,6,6};
    list.unique();
    listCompare.unique();

    compareIter = listCompare.begin();
    iter = list.begin();
    size = 0;
    while(compareIter != listCompare.end())
    {
        EXPECT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
        ++size;
    }
    ASSERT_EQ(size, 5);
}

TEST(FORWARD_LIST, SWAP_NM)
{
    stlcontainer::ForwardList<int> list1 = {9,3,4,5};
    stlcontainer::ForwardList<int> list2 = {0,0};

    std::forward_list<int> listCompare1 = {9,3,4,5};
    std::forward_list<int> listCompare2 = {0,0};

    stlcontainer::swap(list1,list2);
    std::swap(listCompare1, listCompare2);

    auto compareIter = listCompare1.begin();
    auto iter = list1.begin();
    auto size = 0;
    while(compareIter != listCompare1.end())
    {
        ASSERT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
        ++size;
    }
    ASSERT_EQ(size, 2);

    compareIter = listCompare2.begin();
    iter = list2.begin();
    size = 0;
    while(compareIter != listCompare1.end())
    {
        ASSERT_EQ(*iter, *compareIter);
        ++iter;
        ++compareIter;
        ++size;
    }
    ASSERT_EQ(size, 4);
}