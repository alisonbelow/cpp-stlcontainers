#include "stddef.h"

#include <deque>

namespace stlcontainer 
{

template<typename QueueDataType, typename Container = std::deque<QueueDataType>> 
class Queue
{
public:
    // Type definitions
    using container_type =  Container;
    using value_type =      typename Container::value_type;
    using size_type =       typename Container::size_type;
    using reference =       typename Container::reference;
    using const_reference = typename Container::const_reference;

public:
    // Member Functions: Constructors
    // Default constructor
    Queue() : _container(Container()) {};

    // Copy container constructor
    explicit Queue(const Container& cont): _container(cont) {};

    // Move container constructor
    explicit Queue(Container&& cont): _container(std::move(cont)) {};

    // Copy constructor
    Queue(const Queue& other): _container(other._container) {};

    // Move constructor
    Queue(Queue&& other): _container(std::move(other._container)) {};

    // Member Functions: Destructor
    ~Queue() = default;

    // Member Functions: Assignment Operator
    Queue& operator=(const Container& other)
    {
        if (this != &other) 
        {
            _container = other._container;
        }
        return *this;
    }

    Queue& operator=(Container&& other)
    {
        if (this != &other)
        {
            delete[] _container;
            _container = std::move(other._container);
            other._container = nullptr;
        }
        return *this;  
    }

    // Member Functions: Element Access
    reference front()
    {
        return _container.front();
    }

    const_reference front() const
    {
       return _container.front();
    }

    reference back()
    {
        return _container.back();
    }

    const_reference back() const
    {
       return _container.back();
    }

    // Member Functions: Capacity
    bool empty() const
    {
        return _container.empty();
    }

    size_type size() const
    {
        return _container.size();
    }

    // Member Functions: Modifiers
    void push(const value_type& value)
    {
        _container.push_back(value);
    }

    void push(value_type&& value)
    {
        _container.push_back(std::move(value));
    }

    void pop()
    {
        _container.pop_front();
    }

    void swap(Queue& other) noexcept
    {
        std::swap(_container, other._container);
    }

    // Declare relational operators as friends - need access to protected member _container
    // Need to introduce new template arguments
    // Alternatives discussed in cpp-templates/friends (https://github.com/alisonbelow/cpp-templates) 
    template<class myQueueDataType, class myContainer> 
    friend bool operator==(const Queue<myQueueDataType, myContainer>& lhs, const Queue<myQueueDataType, myContainer>& rhs);

    template<class myQueueDataType, class myContainer> 
    friend bool operator!=(const Queue<myQueueDataType, myContainer>& lhs, const Queue<myQueueDataType, myContainer>& rhs);

    template<class myQueueDataType, class myContainer> 
    friend bool operator<(const Queue<myQueueDataType, myContainer>& lhs, const Queue<myQueueDataType, myContainer>& rhs);

    template<class myQueueDataType, class myContainer> 
    friend bool operator>(const Queue<myQueueDataType, myContainer>& lhs, const Queue<myQueueDataType, myContainer>& rhs);

    template<class myQueueDataType, class myContainer> 
    friend bool operator<=(const Queue<myQueueDataType, myContainer>& lhs, const Queue<myQueueDataType, myContainer>& rhs);

    template<class myQueueDataType, class myContainer> 
    friend bool operator>=(const Queue<myQueueDataType, myContainer>& lhs, const Queue<myQueueDataType, myContainer>& rhs);

protected:
    Container _container;    
};

// Non-Member Functions: Relational Operators
template<class QueueDataType, class Container> 
bool operator==(const Queue<QueueDataType, Container>& lhs, const Queue<QueueDataType, Container>& rhs)
{
    return lhs._container == rhs._container;
}

template<class QueueDataType, class Container> 
bool operator!=(const Queue<QueueDataType, Container>& lhs, const Queue<QueueDataType, Container>& rhs)
{
    return lhs._container != rhs._container;
}

template<class QueueDataType, class Container> 
bool operator<(const Queue<QueueDataType, Container>& lhs, const Queue<QueueDataType, Container>& rhs)
{
    return lhs._container < rhs._container;
}

template<class QueueDataType, class Container> 
bool operator>(const Queue<QueueDataType, Container>& lhs, const Queue<QueueDataType, Container>& rhs)
{
    return lhs._container > rhs._container;
}

template<class QueueDataType, class Container> 
bool operator<=(const Queue<QueueDataType, Container>& lhs, const Queue<QueueDataType, Container>& rhs)
{
    return lhs._container <= rhs._container;
}

template<class QueueDataType, class Container> 
bool operator>=(const Queue<QueueDataType, Container>& lhs, const Queue<QueueDataType, Container>& rhs)
{
    return lhs._container >= rhs._container;
}

// Non-Member Functions: Swap
template<class QueueDataType, class Container> 
void swap(Queue<QueueDataType, Container>& lhs, Queue<QueueDataType, Container>& rhs)
{
    return lhs.swap(rhs);
}

} // namespace stlcontainer