#include <algorithm>
#include <exception>
#include <random>
#include <vector>

#include <gtest/gtest.h>
#include "vector/Vector.h"

TEST(VECTOR, EMPTY_CREATION)
{
    stlcontainer::Vector<int> int_vector;
}

// ------------------------------------------------------------------
// Constructors
// ------------------------------------------------------------------
TEST(VECTOR, FILL_CONSTRUCTOR)
{
    stlcontainer::Vector<int> vecZeroes(5);
    ASSERT_TRUE(vecZeroes.size() == 5);
    ASSERT_TRUE(vecZeroes[0] == 0);
    ASSERT_TRUE(vecZeroes.capacity() >= vecZeroes.size());
    
    std::vector<int> compareVecZeroes(5);
    ASSERT_EQ(vecZeroes.size(), compareVecZeroes.size());
    ASSERT_EQ(vecZeroes.capacity(), compareVecZeroes.capacity());

    stlcontainer::Vector<int> vecFours(10, 4);
    ASSERT_TRUE(vecFours.size() == 10);
    for (auto index = 0; index < vecFours.size(); ++index)
    {
        ASSERT_TRUE(vecFours[index] == 4);
    }
    ASSERT_TRUE(vecFours.capacity() >= vecFours.size());

    std::vector<int> compareVecFours(10, 4);
    ASSERT_EQ(vecFours.capacity(), compareVecFours.capacity());
    ASSERT_EQ(vecFours.size(), compareVecFours.size());
}

TEST(VECTOR, COPY_CONSTRUCTOR)
{
    stlcontainer::Vector<int> vecOne(5);
    stlcontainer::Vector<int> vecCopy(vecOne);
    for (auto index = 0; index < vecCopy.size(); ++index)
    {
        ASSERT_EQ(vecOne[index], vecCopy[index]);
    }
}


TEST(VECTOR, INITIALIZER_LIST_CONSTRUCTOR)
{
    stlcontainer::Vector<int> vec({3,5,6,7,1});
    std::vector<int> compareVec = {3,5,6,7,1};
    
    for(auto index = 0; index < vec.size(); ++index)
    {
        ASSERT_EQ(vec[index], compareVec[index]);
    }

    ASSERT_EQ(vec.capacity(), compareVec.capacity());
    ASSERT_EQ(vec.size(), compareVec.size());
}

TEST(VECTOR, ITERATOR)
{
    stlcontainer::Vector<int> vec({3,5,6,7,1});

    // begin() and end()
    ASSERT_EQ(3, *vec.begin());

    // Arithmetic operators
    ASSERT_EQ(5, *(vec.begin()+1));
    ASSERT_EQ(1, *(vec.end()-1));
    ASSERT_EQ(1, *(vec.begin()+vec.size()-1));
    ASSERT_EQ(vec.end(), (vec.begin()+vec.size()));

    // Test for loop with iterators
    EXPECT_NO_THROW({
        for (auto num = vec.begin(); num != vec.end(); ++num) 
        {
            continue;
        }
    });
    
    // Test auto range-based for loop
    EXPECT_NO_THROW({
        for (auto& num: vec)
        {
            continue;
        }
    });
}

TEST(VECTOR, MOVE_CONSTRUCTOR)
{
    stlcontainer::Vector<int> dummyvec(5);
    auto savedCount = dummyvec.size();
    auto savedCapacity = dummyvec.capacity();
    auto savedElems = dummyvec.data();

    stlcontainer::Vector<int> move_vec(std::move(dummyvec));

    ASSERT_EQ(savedCount, move_vec.size());
    ASSERT_EQ(savedCapacity, move_vec.capacity());
    ASSERT_EQ(savedElems, move_vec.data());
}

// ------------------------------------------------------------------
// Assignment
// ------------------------------------------------------------------
TEST(VECTOR, COPY_ASSIGNMENT)
{
    stlcontainer::Vector<int> vec({3,5,6,7,1});
    std::vector<int> compareVec({3,5,6,7,1});

    for(auto index = 0; index < vec.size(); ++index)
    {
        ASSERT_EQ(vec[index], compareVec[index]);
    }

    stlcontainer::Vector<int> rval_vec({7,2,4,9,0,0,0,3});    
    std::vector<int> compareRvalVec({7,2,4,9,0,0,0,3});
    vec = rval_vec;
    compareVec = compareRvalVec;

    for(auto index = 0; index < vec.size(); ++index)
    {
        ASSERT_EQ(vec[index], compareVec[index]);
    }
}

TEST(VECTOR, MOVE_ASSIGNMENT)
{
    stlcontainer::Vector<int> vec({3,5,6,7,1});
    std::vector<int> compareVec({3,5,6,7,1});

    for(auto index = 0; index < vec.size(); ++index)
    {
        ASSERT_EQ(vec[index], compareVec[index]);
    }

    stlcontainer::Vector<int> lval_vec({7,2,4,9,0,0,0,3});    
    std::vector<int> compareLvalVec({7,2,4,9,0,0,0,3});
    vec = std::move(lval_vec);
    compareVec = std::move(compareLvalVec);

    for(auto index = 0; index < vec.size(); ++index)
    {
        ASSERT_EQ(vec[index], compareVec[index]);
    }
}

TEST(VECTOR, INIT_LIST_ASSIGNMENT)
{
    stlcontainer::Vector<int> vec({3,5,6,7,1});
    std::vector<int> compareVec({3,5,6,7,1});

    for(auto index = 0; index < vec.size(); ++index)
    {
        ASSERT_EQ(vec[index], compareVec[index]);
    }

    vec = {7,2,4,9,0,0,0,3};
    compareVec = {7,2,4,9,0,0,0,3};
    
    for(auto index = 0; index < vec.size(); ++index)
    {
        ASSERT_EQ(vec[index], compareVec[index]);
    }
}

// ------------------------------------------------------------------
// Element Access
// ------------------------------------------------------------------
TEST(VECTOR, AT)
{
    stlcontainer::Vector<int> vec({3,5,6,7,1});
    ASSERT_EQ(vec.at(0), 3);
    ASSERT_EQ(vec.at(4), 1);
    ASSERT_THROW(vec.at(99), std::out_of_range);
    ASSERT_THROW(vec.at(vec.size()), std::out_of_range);
}

TEST(VECTOR, FRONT_AND_BACK)
{
    stlcontainer::Vector<int> vec({3,5,6,7,1});
    ASSERT_EQ(vec.front(), 3);
    ASSERT_EQ(vec.back(), 1);
}

// ------------------------------------------------------------------
// Modifiers
// ------------------------------------------------------------------
/*int return_zero_elem(int* elems)
{
    return elems[0];
}

// Reference for catching seg fault: https://stackoverflow.com/questions/47583352/how-to-catch-segmentation-fault-with-google-test
TEST(VECTOR, CLEAR_AND_EMPTY)
{
    stlcontainer::Vector<int> vec({3,5,6,7,1});
    vec.clear();

    ASSERT_TRUE(vec.size() == 0);
    ASSERT_TRUE(vec.empty());
    
    // Should seg fault
    auto elems = vec.data();
    ASSERT_EXIT(return_zero_elem(elems), ::testing::KilledBySignal(SIGSEGV), ".*");
}*/

TEST(VECTOR, PUSH_BACK)
{
    stlcontainer::Vector<int> vec;
    std::cout << "cap = " << vec.capacity() << ", push back 3\n";
    vec.push_back(3);
    std::cout << "cap = " << vec.capacity() << ", push back 5\n";
    vec.push_back(5);
    std::cout << "cap = " << vec.capacity() << ", push back 6\n";
    vec.push_back(6);
    std::cout << "cap = " << vec.capacity() << ", push back 7\n";
    vec.push_back(7);
    std::cout << "cap = " << vec.capacity() << ", push back 1\n";
    vec.push_back(1);
    std::cout << "cap = " << vec.capacity() << "\n";

    std::vector<int> temp;
    std::cout << "cap = " << temp.capacity() << ", push back 3\n";
    temp.push_back(3);
    std::cout << "cap = " << temp.capacity() << ", push back 5\n";
    temp.push_back(5);
    std::cout << "cap = " << temp.capacity() << ", push back 6\n";
    temp.push_back(6);
    std::cout << "cap = " << temp.capacity() << ", push back 7\n";
    temp.push_back(7);
    std::cout << "cap = " << temp.capacity() << ", push back 1\n";
    temp.push_back(1);
    std::cout << "cap = " << temp.capacity() << "\n";

    std::vector<int> compareVec({3,5,6,7,1});

    for(auto index = 0; index < vec.size(); ++index)
    {
        ASSERT_EQ(vec[index], compareVec[index]);
    }

    ASSERT_TRUE(vec.size() == 5);
    ASSERT_TRUE(vec.capacity() > vec.size());
}

TEST(VECTOR, POP_BACK)
{
    stlcontainer::Vector<int> vec;
    vec.push_back(3);
    vec.push_back(5);
    vec.push_back(6);
    vec.push_back(7);
    vec.push_back(1);

    vec.pop_back();

    std::vector<int> compareVec({3,5,6,7});
    for(auto index = 0; index < vec.size(); ++index)
    {
        ASSERT_EQ(vec[index], compareVec[index]);
    }

    ASSERT_TRUE(vec.size() == 4);
}

TEST(VECTOR, RESIZE)
{
    stlcontainer::Vector<int> vec({3,5,6,7,1});
    auto initialCapacity = vec.capacity();

    vec.resize(7);
    ASSERT_TRUE(vec.capacity() > initialCapacity);
    ASSERT_TRUE(vec.size() == 7);

    vec.resize(4);
    ASSERT_TRUE(vec.size() == 4);
    ASSERT_TRUE(vec[0] == 3);
    ASSERT_TRUE(vec[1] == 5);
    ASSERT_TRUE(vec[2] == 6);
    ASSERT_TRUE(vec[3] == 7);

    vec.resize(10,10);
    std::vector<int> compareVec({3,5,6,7,10,10,10,10,10,10});
    for(auto index = 0; index < vec.size(); ++index)
    {
        ASSERT_EQ(vec[index], compareVec[index]);
    }
}

TEST(VECTOR, SWAP)
{
    stlcontainer::Vector<int> vec1({3,5,6,7,1});
    stlcontainer::Vector<int> vec2({0,5,4,2});

    std::vector<int> compareVecOne({3,5,6,7,1});
    std::vector<int> compareVecTwo({0,5,4,2});

    vec1.swap(vec2);
    
    ASSERT_TRUE(vec1.size() == compareVecTwo.size());
    for(auto index = 0; index < vec1.size(); ++index)
    {
        ASSERT_EQ(vec1[index], compareVecTwo[index]);
    }

    ASSERT_TRUE(vec2.size() == compareVecOne.size());
    for(auto index = 0; index < vec2.size(); ++index)
    {
        ASSERT_EQ(vec2[index], compareVecOne[index]);
    }
}

// ------------------------------------------------------------------
// Non-Member 
// ------------------------------------------------------------------
TEST(VECTOR, EQUALS)
{
    stlcontainer::Vector<int> vec1({3,6,7,4,1,0,0});
    stlcontainer::Vector<int> vec2({3,6,7,4,1,0,0});
    ASSERT_TRUE(vec1 == vec2);

    vec2 = {3,6,7,4,0,1,0};
    ASSERT_FALSE(vec1 == vec2);
}

TEST(VECTOR, RELATIONALOPS)
{
    // Test cases from http://www.cplusplus.com/reference/vector/vector/operators/
    stlcontainer::Vector<int> foo (3,100);
    stlcontainer::Vector<int> bar (2,200);
    std::vector<int> fooCompare (3,100);  
    std::vector<int> barCompare (2,200);   

    ASSERT_FALSE(foo == bar);
    ASSERT_TRUE(foo != bar);
    ASSERT_TRUE(foo < bar);
    ASSERT_FALSE(foo > bar);
    ASSERT_TRUE(foo <= bar);
    ASSERT_FALSE(foo >= bar);
    
    ASSERT_FALSE(fooCompare == barCompare);
    ASSERT_TRUE(fooCompare != barCompare);
    ASSERT_TRUE(fooCompare < barCompare);
    ASSERT_FALSE(fooCompare > barCompare);
    ASSERT_TRUE(fooCompare <= barCompare);
    ASSERT_FALSE(fooCompare >= barCompare);

    foo = stlcontainer::Vector<int> (4,200);
    bar = stlcontainer::Vector<int> (2,200);  
    fooCompare = std::vector<int>(4,200);
    barCompare = std::vector<int>(2,200);

    ASSERT_FALSE(foo == bar);
    ASSERT_TRUE(foo != bar);
    ASSERT_FALSE(foo < bar);
    ASSERT_TRUE(foo > bar);
    ASSERT_FALSE(foo <= bar);
    ASSERT_TRUE(foo >= bar);
    
    ASSERT_FALSE(fooCompare == barCompare);
    ASSERT_TRUE(fooCompare != barCompare);
    ASSERT_FALSE(fooCompare < barCompare);
    ASSERT_TRUE(fooCompare > barCompare);
    ASSERT_FALSE(fooCompare <= barCompare);
    ASSERT_TRUE(fooCompare >= barCompare);
}

// ------------------------------------------------------------------
// Misc
// ------------------------------------------------------------------
TEST(VECTOR, PUSH_BACK_LARGE)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 50000);

    stlcontainer::Vector<int> vec;
    size_t largeNum = 90000;
    vec.reserve(largeNum);
    for(auto index = 0; index < largeNum; ++index)
    {
        vec.push_back(dis(gen));
    }

    ASSERT_TRUE(vec.size() == largeNum);
}

TEST(VECTOR, DATA_TYPES)
{
    EXPECT_NO_THROW({
        stlcontainer::Vector<double> doubleVec({0.0, 6.789345, 45435.333, 5.55555555, 0});
        ASSERT_TRUE(doubleVec[1] == 6.789345);

        stlcontainer::Vector<char> charVec({'a', '0', 'g', '4'});
        ASSERT_TRUE(charVec[1] == '0');

        stlcontainer::Vector<std::string> strVec({"asdfjasdf", "asdf", "dfgdg", "sdfgsdfg", "sdgsfdgdf"});
        ASSERT_TRUE(strVec[2] == "dfgdg");
    });
    
}

TEST(VECTOR, STDSORT)
{
    stlcontainer::Vector<int> vec({3,6,7,4,1,0,0});
    std::vector<int> compareVec({3,6,7,4,1,0,0});
    std::sort(vec.begin(), vec.end());
    std::sort(compareVec.begin(), compareVec.end());

    for(auto index = 0; index < vec.size(); ++index)
    {
        ASSERT_EQ(vec[index], compareVec[index]);
    }
}