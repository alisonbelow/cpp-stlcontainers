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

    // Member Functions: Destructor

    // Member Functions: Assignment Operator

    // Member Functions: Element Access

    // Member Functions: Capacity

    // Member Functions: Modifiers

    // Non-Member Functions: Relational Operators

    // Non-Member Functions: Swap

protected:
  Container _container;    

};

} // namespace stlcontainer