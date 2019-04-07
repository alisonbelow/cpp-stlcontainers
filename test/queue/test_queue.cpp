#include <deque>
#include <list>
#include <queue>
#include <vector>

#include <gtest/gtest.h>
#include "queue/Queue.h"

TEST(STACK, EMPTY_CREATION_DEFAULT_CONSTRUCTOR)
{
    stlcontainer::Queue<int> queue;
    std::queue<int> queueCompare;
    std::deque<int> dequeCompare;

    ASSERT_EQ(queue.size(), queueCompare.size());
    ASSERT_EQ(queue.size(), dequeCompare.size());
    ASSERT_EQ(queue.empty(), queueCompare.empty());
    ASSERT_EQ(queue.empty(), dequeCompare.empty());
}

TEST(STACK, COPY_CONTAINER_CONSTRUCTOR)
{
    std::deque<int> d = {9,5,6};
    stlcontainer::Queue<int> queue(d);
    std::queue<int> queueCompare(d);
    ASSERT_EQ(queue.size(), queueCompare.size());
}

TEST(STACK, MOVE_CONTAINER_CONSTRUCTOR)
{
    std::deque<int> d = {9,5,6};
    stlcontainer::Queue<int> queue(std::move(d));
    std::queue<int> queueCompare(std::move(d));
    
    // queue already took all of d's resources, so size of queue should be 3 and size of queueCompare should be 0
    ASSERT_FALSE(queue.size() == queueCompare.size());

    std::deque<int> d2 = {9,5,6};
    std::queue<int> queueCompare2(std::move(d2));
    ASSERT_EQ(queue.size(), queueCompare2.size());
}

TEST(STACK, COPY_CONSTRUCTOR)
{
    stlcontainer::Queue<int> queue({9,5,6});
    stlcontainer::Queue<int> queueCopy(queue);

    std::queue<int> queueCompare({9,5,6});
    std::queue<int> queueCopyCompare(queueCompare);

    ASSERT_EQ(queueCopy.size(), queueCopyCompare.size());
}

TEST(STACK, MOVE_CONSTRUCTOR)
{
    stlcontainer::Queue<int> queue({9,5,6});
    stlcontainer::Queue<int> queueMove(std::move(queue));

    std::queue<int> queueCompare({9,5,6});
    std::queue<int> queueMoveCompare(std::move(queueCompare));

    ASSERT_EQ(queueMove.size(), queueMoveCompare.size());
}

TEST(STACK, ASSIGNMENT_OPERATORS)
{
    stlcontainer::Queue<int> queue({0,13,24,5});
    stlcontainer::Queue<int> queueAssign = queue;

    std::queue<int> queueCompare({0,13,24,5});
    std::queue<int> queueAssignCompare = queueCompare;

    ASSERT_EQ(queueAssign.size(), queueAssignCompare.size());
    ASSERT_EQ(queueAssign.front(), queueAssignCompare.front());
    ASSERT_EQ(queueAssign.back(), queueAssignCompare.back());
    
    stlcontainer::Queue<int> queueMoveAssign = std::move(queue);
    std::queue<int> queueMoveAssignCompare = std::move(queueCompare);

    ASSERT_EQ(queueMoveAssign.size(), queueMoveAssignCompare.size());
    ASSERT_EQ(queueMoveAssign.front(), queueMoveAssignCompare.front());
    ASSERT_EQ(queueMoveAssign.back(), queueMoveAssignCompare.back());
}

TEST(STACK, PUSH)
{
    stlcontainer::Queue<int> queue;
    std::queue<int> queueCompare;

    queue.push(5);
    queueCompare.push(5);

    ASSERT_TRUE(queue.size() == 1);
    ASSERT_FALSE(queue.empty());
    ASSERT_EQ(queue.size(), queueCompare.size());

    queue.push(6);
    queueCompare.push(6);
    queue.push(6);
    queueCompare.push(6);
    queue.push(6);
    queueCompare.push(6);
    queue.push(6);
    queueCompare.push(6);
    queue.push(6);
    queueCompare.push(6);
    queue.push(6);
    queueCompare.push(6);
    queue.push(6);
    queueCompare.push(6);
    ASSERT_EQ(queue.size(), queueCompare.size());
}

TEST(STACK, FRONT)
{
    stlcontainer::Queue<int> queue;
    std::queue<int> queueCompare;

    queue.push(5);
    queueCompare.push(5);
    queue.push(4);
    queueCompare.push(4);
    queue.push(3);
    queueCompare.push(3);

    ASSERT_EQ(queue.front(), 5);
    ASSERT_EQ(queue.front(), queueCompare.front());
}

TEST(STACK, BACK)
{
    stlcontainer::Queue<int> queue;
    std::queue<int> queueCompare;

    queue.push(5);
    queueCompare.push(5);
    queue.push(4);
    queueCompare.push(4);
    queue.push(3);
    queueCompare.push(3);

    ASSERT_EQ(queue.back(), 3);
    ASSERT_EQ(queue.back(), queueCompare.back());
}

// size() and empty() tested in previous tests

TEST(STACK, POP)
{
    stlcontainer::Queue<int> queue;
    std::queue<int> queueCompare;

    queue.push(2);
    queueCompare.push(2);
    queue.push(5);
    queueCompare.push(5);
    queue.push(6);
    queueCompare.push(6);
    queue.push(77);
    queueCompare.push(77);
    queue.push(1);
    queueCompare.push(1);

    queue.pop();
    queueCompare.pop();

    ASSERT_EQ(queue.size(), queueCompare.size());   
    ASSERT_EQ(queue.front(), queueCompare.front());
    ASSERT_EQ(queue.front(), 5);
    ASSERT_EQ(queue.back(), queueCompare.back());
    ASSERT_EQ(queue.back(), 1);
} 

TEST(STACK, SWAP)
{
    stlcontainer::Queue<int> queue({9,4,5,6,7});
    stlcontainer::Queue<int> queue2({1,1,1});
    std::queue<int> queueCompare({9,4,5,6,7});
    std::queue<int> queueCompare2({1,1,1});
    
    queue.swap(queue2);
    queueCompare.swap(queueCompare2);

    ASSERT_EQ(queue.size(), queueCompare.size());   
    ASSERT_EQ(queue.front(), queueCompare.front());
    ASSERT_EQ(queue.back(), queueCompare.back());
    ASSERT_EQ(queue2.size(), queueCompare2.size());   
    ASSERT_EQ(queue2.front(), queueCompare2.front());
    ASSERT_EQ(queue2.back(), queueCompare2.back());
}

TEST(STACK, RELATIONAL_OPERATORS)
{
    stlcontainer::Queue<int> queue({9,4,5,6,7});
    stlcontainer::Queue<int> queue2({1,1,1});
    std::queue<int> queueCompare({9,4,5,6,7});
    std::queue<int> queueCompare2({1,1,1});

    ASSERT_FALSE(queue2 == queue);
    ASSERT_TRUE(queue2 != queue);
    ASSERT_TRUE(queue2 < queue);  
    ASSERT_FALSE(queue2 > queue);
    ASSERT_TRUE(queue2 <= queue);  
    ASSERT_FALSE(queue2 >= queue); 

    ASSERT_FALSE(queueCompare2 == queueCompare);
    ASSERT_TRUE(queueCompare2 != queueCompare);
    ASSERT_TRUE(queueCompare2 < queueCompare);  
    ASSERT_FALSE(queueCompare2 > queueCompare);
    ASSERT_TRUE(queueCompare2 <= queueCompare);  
    ASSERT_FALSE(queueCompare2 >= queueCompare);
}

TEST(STACK, NONMEMBER_SWAP)
{
    stlcontainer::Queue<int> queue({9,4,5,6,7});
    stlcontainer::Queue<int> queue2({1,1,1});
    std::queue<int> queueCompare({9,4,5,6,7});
    std::queue<int> queueCompare2({1,1,1});
    
    stlcontainer::swap(queue, queue2);
    std::swap(queueCompare, queueCompare2);

    ASSERT_EQ(queue.size(), queueCompare.size());   
    ASSERT_EQ(queue.front(), queueCompare.front());
    ASSERT_EQ(queue.back(), queueCompare.back());
    ASSERT_EQ(queue2.size(), queueCompare2.size());   
    ASSERT_EQ(queue2.front(), queueCompare2.front());
    ASSERT_EQ(queue2.back(), queueCompare2.back());
}

TEST(STACK, CONTAINER_VARIATIONS)
{
    // List
    stlcontainer::Queue<int, std::list<int>> queueList({8,4,5,6});
    std::queue<int, std::list<int>> queueListCompare({8,4,5,6});
    ASSERT_EQ(queueList.size(), queueListCompare.size());   
    ASSERT_EQ(queueList.front(), queueListCompare.front());
    ASSERT_EQ(queueList.back(), queueListCompare.back());

    // Deque, char
    stlcontainer::Queue<char, std::deque<char>> queueDeque({'8','4','5','6'});
    std::queue<char, std::deque<char>> queueDequeCompare({'8','4','5','6'});
    ASSERT_EQ(queueDeque.size(), queueDequeCompare.size());   
    ASSERT_EQ(queueDeque.front(), queueDequeCompare.front());
    ASSERT_EQ(queueDeque.back(), queueDequeCompare.back());
}