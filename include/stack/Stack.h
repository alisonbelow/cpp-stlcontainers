#include "stddef.h"

#include <deque>

namespace stlcontainer 
{

template<typename StackDataType, typename Container = std::deque<StackDataType>> 
class Stack
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
    Stack() : _container(Container()) {};

    // Copy container constructor
    explicit Stack(const Container& cont): _container(cont) {};

    // Move container constructor
    explicit Stack(Container&& cont): _container(std::move(cont)) {};

    // Copy constructor
    Stack(const Stack& other): _container(other._container) {};

    // Move constructor
    Stack(Stack&& other): _container(std::move(other._container)) {};

    // Member Functions: Destructor
    ~Stack() = default;

    // Member Functions: Assignment Operator
    Stack& operator=(const Container& other)
    {
        if (this != &other) 
        {
            _container = other._container;
        }
        return *this;
    }

    Stack& operator=(Container&& other)
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
    reference top()
    {
        return _container.back();
    }

    const_reference top() const
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
        _container.pop_back();
    }

    void swap(Stack& other) noexcept
    {
        std::swap(_container, other._container);
    }

    // Declare relational operators as friends - need access to protected member _container
    // Need to introduce new template arguments
    // Alternatives discussed in cpp-templates/friends (https://github.com/alisonbelow/cpp-templates) 
    template<class myStackDataType, class myContainer> 
    friend bool operator==(const Stack<myStackDataType, myContainer>& lhs, const Stack<myStackDataType, myContainer>& rhs);

    template<class myStackDataType, class myContainer> 
    friend bool operator!=(const Stack<myStackDataType, myContainer>& lhs, const Stack<myStackDataType, myContainer>& rhs);

    template<class myStackDataType, class myContainer> 
    friend bool operator<(const Stack<myStackDataType, myContainer>& lhs, const Stack<myStackDataType, myContainer>& rhs);

    template<class myStackDataType, class myContainer> 
    friend bool operator>(const Stack<myStackDataType, myContainer>& lhs, const Stack<myStackDataType, myContainer>& rhs);

    template<class myStackDataType, class myContainer> 
    friend bool operator<=(const Stack<myStackDataType, myContainer>& lhs, const Stack<myStackDataType, myContainer>& rhs);

    template<class myStackDataType, class myContainer> 
    friend bool operator>=(const Stack<myStackDataType, myContainer>& lhs, const Stack<myStackDataType, myContainer>& rhs);

protected:
    Container _container;    
};

// Non-Member Functions: Relational Operators
template<class StackDataType, class Container> 
bool operator==(const Stack<StackDataType, Container>& lhs, const Stack<StackDataType, Container>& rhs)
{
    return lhs._container == rhs._container;
}

template<class StackDataType, class Container> 
bool operator!=(const Stack<StackDataType, Container>& lhs, const Stack<StackDataType, Container>& rhs)
{
    return lhs._container != rhs._container;
}

template<class StackDataType, class Container> 
bool operator<(const Stack<StackDataType, Container>& lhs, const Stack<StackDataType, Container>& rhs)
{
    return lhs._container < rhs._container;
}

template<class StackDataType, class Container> 
bool operator>(const Stack<StackDataType, Container>& lhs, const Stack<StackDataType, Container>& rhs)
{
    return lhs._container > rhs._container;
}

template<class StackDataType, class Container> 
bool operator<=(const Stack<StackDataType, Container>& lhs, const Stack<StackDataType, Container>& rhs)
{
    return lhs._container <= rhs._container;
}

template<class StackDataType, class Container> 
bool operator>=(const Stack<StackDataType, Container>& lhs, const Stack<StackDataType, Container>& rhs)
{
    return lhs._container >= rhs._container;
}

// Non-Member Functions: Swap
template<class StackDataType, class Container> 
void swap(Stack<StackDataType, Container>& lhs, Stack<StackDataType, Container>& rhs)
{
    return lhs.swap(rhs);
}

} // namespace stlcontainer