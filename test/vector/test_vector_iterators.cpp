#include <vector>

#include <gtest/gtest.h>
#include "vector/VectorIterator.h"
#include "vector/Vector.h"

TEST(VECTOR_ITER, EMPTY_CREATION)
{
    stlcontainer::VectorIterator<std::vector<int>> vec_iter;
}

TEST(VECTOR_ITER, POPULATED_CREATION)
{
    stlcontainer::Vector<int> v = {1,2,5,4};
    stlcontainer::VectorIterator<stlcontainer::Vector<int>> vec_iter(v.data(), 0);

    ASSERT_EQ(*vec_iter, v[0]);
}

TEST(VECTOR_ITER, EQUALS_OPERATOR)
{
    std::vector<int> v = {1,2,5,4};
    stlcontainer::VectorIterator<stlcontainer::Vector<int>> vec_iter(v.data(), 0);

    ASSERT_TRUE(*vec_iter == v[0]);
}

TEST(VECTOR_ITER, DOES_NOT_EQUAL_OPERATOR)
{
    std::vector<int> v = {1,2,5,4};
    stlcontainer::VectorIterator<stlcontainer::Vector<int>> vec_iter(v.data(), 0);

    ASSERT_TRUE(*vec_iter != v[2]);
}

TEST(VECTOR_ITER, PREINCREMENT)
{
    std::vector<int> v = {1,2,5,4};
    stlcontainer::VectorIterator<stlcontainer::Vector<int>> vec_iter(v.data(), 0);

    ASSERT_EQ(*(++vec_iter), v[1]);
}

TEST(VECTOR_ITER, POSTINCREMENT)
{
    std::vector<int> v = {1,2,5,4};
    stlcontainer::VectorIterator<stlcontainer::Vector<int>> vec_iter(v.data(), 0);

    ASSERT_EQ(*(vec_iter++), v[0]);
    ASSERT_EQ(*(vec_iter++), v[1]);
}

TEST(VECTOR_ITER, DECREMENT)
{
    std::vector<int> v = {1,2,5,4};
    stlcontainer::VectorIterator<stlcontainer::Vector<int>> vec_iter(v.data(), 0);

    ++vec_iter;
    ASSERT_EQ(*(--vec_iter), v[0]);
}

TEST(VECTOR_ITER, ARITHMETIC_OPS)
{
    std::vector<int> v = {1,2,5,4};
    stlcontainer::VectorIterator<stlcontainer::Vector<int>> vec_iter(v.data(), 0);

    vec_iter = vec_iter + 2;
    ASSERT_EQ(*(vec_iter), v[2]);
    ASSERT_EQ(*(vec_iter - 1), v[1]);
}

TEST(VECTOR_ITER, COMPOUND_ASSIGNMENT_OPS)
{
    std::vector<int> v = {1,2,5,4,3};
    stlcontainer::VectorIterator<stlcontainer::Vector<int>> vec_iter(v.data(), 0);

    vec_iter += 4;
    ASSERT_EQ(*(vec_iter), v[4]);
}

TEST(VECTOR_ITER, RELATIONAL_OPERATORS)
{
    std::vector<int> v = {1,2,5,4};
    stlcontainer::VectorIterator<stlcontainer::Vector<int>> vec_iter(v.data(), 0);

    ASSERT_FALSE(*vec_iter >= v[2]);
    ASSERT_TRUE(*vec_iter >= v[0]);
    ASSERT_FALSE(*vec_iter > v[2]);
    ASSERT_TRUE(*vec_iter <= v[2]);
    ASSERT_TRUE(*vec_iter <= v[0]);
    ASSERT_TRUE(*vec_iter < v[2]);
}