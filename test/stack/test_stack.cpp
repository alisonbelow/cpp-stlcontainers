#include <deque>
#include <list>
#include <stack>
#include <vector>

#include <gtest/gtest.h>
#include "stack/Stack.h"

TEST(STACK, EMPTY_CREATION_DEFAULT_CONSTRUCTOR)
{
    stlcontainer::Stack<int> stack;
    std::stack<int> stackCompare;
    std::deque<int> dequeCompare;

    ASSERT_EQ(stack.size(), stackCompare.size());
    ASSERT_EQ(stack.size(), dequeCompare.size());
    ASSERT_EQ(stack.empty(), stackCompare.empty());
    ASSERT_EQ(stack.empty(), dequeCompare.empty());
}

TEST(STACK, COPY_CONTAINER_CONSTRUCTOR)
{
    std::deque<int> d = {9,5,6};
    stlcontainer::Stack<int> stack(d);
    std::stack<int> stackCompare(d);
    ASSERT_EQ(stack.size(), stackCompare.size());
}

TEST(STACK, MOVE_CONTAINER_CONSTRUCTOR)
{
    std::deque<int> d = {9,5,6};
    stlcontainer::Stack<int> stack(std::move(d));
    std::stack<int> stackCompare(std::move(d));
    
    // stack already took all of d's resources, so size of stack should be 3 and size of stackCompare should be 0
    ASSERT_FALSE(stack.size() == stackCompare.size());

    std::deque<int> d2 = {9,5,6};
    std::stack<int> stackCompare2(std::move(d2));
    ASSERT_EQ(stack.size(), stackCompare2.size());
}

TEST(STACK, COPY_CONSTRUCTOR)
{
    stlcontainer::Stack<int> stack({9,5,6});
    stlcontainer::Stack<int> stackCopy(stack);

    std::stack<int> stackCompare({9,5,6});
    std::stack<int> stackCopyCompare(stackCompare);

    ASSERT_EQ(stackCopy.size(), stackCopyCompare.size());
}

TEST(STACK, MOVE_CONSTRUCTOR)
{
    stlcontainer::Stack<int> stack({9,5,6});
    stlcontainer::Stack<int> stackMove(std::move(stack));

    std::stack<int> stackCompare({9,5,6});
    std::stack<int> stackMoveCompare(std::move(stackCompare));

    ASSERT_EQ(stackMove.size(), stackMoveCompare.size());
}

TEST(STACK, ASSIGNMENT_OPERATORS)
{
    stlcontainer::Stack<int> stack({0,13,24,5});
    stlcontainer::Stack<int> stackAssign = stack;

    std::stack<int> stackCompare({0,13,24,5});
    std::stack<int> stackAssignCompare = stackCompare;

    ASSERT_EQ(stackAssign.size(), stackAssignCompare.size());
    ASSERT_EQ(stackAssign.top(), stackAssignCompare.top());
    
    stlcontainer::Stack<int> stackMoveAssign = std::move(stack);
    std::stack<int> stackMoveAssignCompare = std::move(stackCompare);

    ASSERT_EQ(stackMoveAssign.size(), stackMoveAssignCompare.size());
    ASSERT_EQ(stackMoveAssign.top(), stackMoveAssignCompare.top());
}

TEST(STACK, PUSH)
{
    stlcontainer::Stack<int> stack;
    std::stack<int> stackCompare;

    stack.push(5);
    stackCompare.push(5);

    ASSERT_TRUE(stack.size() == 1);
    ASSERT_FALSE(stack.empty());
    ASSERT_EQ(stack.size(), stackCompare.size());

    stack.push(6);
    stackCompare.push(6);
    stack.push(6);
    stackCompare.push(6);
    stack.push(6);
    stackCompare.push(6);
    stack.push(6);
    stackCompare.push(6);
    stack.push(6);
    stackCompare.push(6);
    stack.push(6);
    stackCompare.push(6);
    stack.push(6);
    stackCompare.push(6);
    ASSERT_EQ(stack.size(), stackCompare.size());
}

TEST(STACK, TOP)
{
    stlcontainer::Stack<int> stack;
    std::stack<int> stackCompare;

    stack.push(5);
    stackCompare.push(5);
    stack.push(4);
    stackCompare.push(4);
    stack.push(3);
    stackCompare.push(3);

    ASSERT_EQ(stack.top(), 3);
    ASSERT_EQ(stack.top(), stackCompare.top());
}

// size() and empty() tested in previous tests

TEST(STACK, POP)
{
    stlcontainer::Stack<int> stack;
    std::stack<int> stackCompare;

    stack.push(5);
    stackCompare.push(5);
    stack.push(5);
    stackCompare.push(5);
    stack.push(5);
    stackCompare.push(5);
    stack.push(77);
    stackCompare.push(77);
    stack.push(1);
    stackCompare.push(1);

    stack.pop();
    stackCompare.pop();

    ASSERT_EQ(stack.size(), stackCompare.size());   
    ASSERT_EQ(stack.top(), stackCompare.top());
    ASSERT_EQ(stack.top(), 77);
} 

TEST(STACK, SWAP)
{
    stlcontainer::Stack<int> stack({9,4,5,6,7});
    stlcontainer::Stack<int> stack2({1,1,1});
    std::stack<int> stackCompare({9,4,5,6,7});
    std::stack<int> stackCompare2({1,1,1});
    
    stack.swap(stack2);
    stackCompare.swap(stackCompare2);

    ASSERT_EQ(stack.size(), stackCompare.size());   
    ASSERT_EQ(stack.top(), stackCompare.top());
    ASSERT_EQ(stack2.size(), stackCompare2.size());   
    ASSERT_EQ(stack2.top(), stackCompare2.top());
}

TEST(STACK, RELATIONAL_OPERATORS)
{
    stlcontainer::Stack<int> stack({9,4,5,6,7});
    stlcontainer::Stack<int> stack2({1,1,1});
    std::stack<int> stackCompare({9,4,5,6,7});
    std::stack<int> stackCompare2({1,1,1});

    ASSERT_FALSE(stack2 == stack);
    ASSERT_TRUE(stack2 != stack);
    ASSERT_TRUE(stack2 < stack);  
    ASSERT_FALSE(stack2 > stack);
    ASSERT_TRUE(stack2 <= stack);  
    ASSERT_FALSE(stack2 >= stack); 

    ASSERT_FALSE(stackCompare2 == stackCompare);
    ASSERT_TRUE(stackCompare2 != stackCompare);
    ASSERT_TRUE(stackCompare2 < stackCompare);  
    ASSERT_FALSE(stackCompare2 > stackCompare);
    ASSERT_TRUE(stackCompare2 <= stackCompare);  
    ASSERT_FALSE(stackCompare2 >= stackCompare);
}

TEST(STACK, NONMEMBER_SWAP)
{
    stlcontainer::Stack<int> stack({9,4,5,6,7});
    stlcontainer::Stack<int> stack2({1,1,1});
    std::stack<int> stackCompare({9,4,5,6,7});
    std::stack<int> stackCompare2({1,1,1});
    
    stlcontainer::swap(stack, stack2);
    std::swap(stackCompare, stackCompare2);

    ASSERT_EQ(stack.size(), stackCompare.size());   
    ASSERT_EQ(stack.top(), stackCompare.top());
    ASSERT_EQ(stack2.size(), stackCompare2.size());   
    ASSERT_EQ(stack2.top(), stackCompare2.top());
}

TEST(STACK, CONTAINER_VARIATIONS)
{
    // Vector
    stlcontainer::Stack<int, std::vector<int>> stackVector({8,4,5,6});
    std::stack<int, std::vector<int>> stackVectorCompare({8,4,5,6});
    ASSERT_EQ(stackVector.size(), stackVectorCompare.size());   
    ASSERT_EQ(stackVector.top(), stackVectorCompare.top());

    // List
    stlcontainer::Stack<int, std::list<int>> stackList({8,4,5,6});
    std::stack<int, std::list<int>> stackListCompare({8,4,5,6});
    ASSERT_EQ(stackList.size(), stackListCompare.size());   
    ASSERT_EQ(stackList.top(), stackListCompare.top());

    // Deque, char
    stlcontainer::Stack<char, std::deque<char>> stackDeque({'8','4','5','6'});
    std::stack<char, std::deque<char>> stackDequeCompare({'8','4','5','6'});
    ASSERT_EQ(stackDeque.size(), stackDequeCompare.size());   
    ASSERT_EQ(stackDeque.top(), stackDequeCompare.top());
}