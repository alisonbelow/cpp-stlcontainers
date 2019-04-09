#include <iterator>
#include "ForwardListNode.h"

namespace stlcontainer
{

template<typename IterType>
class ForwardListIterator : public std::iterator<
    std::forward_iterator_tag,
    IterType, 
    IterType*, 
    IterType&>
{
// Friend declarations
friend class ForwardList<IterType>;

// Type definitions
public:
    using value_type =        IterType;
    using reference =         IterType&;
    using const_reference =   const reference;
    using iterator =          typename stlcontainer::ForwardListIterator<IterType>;
    using const_iterator =    const iterator;

public:

    // Deference
    reference operator* () const
    {
        return _pointee->_value;
    }

    // Increment/move
    iterator& operator++()
    {
        _pointee = _pointee->_next;
        return *this;
    }

    // Increment by value
    iterator operator++(int)
    {
        iterator returnval(_pointee);
        ++(*this);
        return returnval;
    }

    // Comparison operator, equality
    bool operator==(iterator other) const
    {
        return _pointee == other._pointee;
    }

    // Comparison operator, inequality
    bool operator!=(iterator other) const
    {
        return !(*this == other); 
    } 

private:
    stlcontainer::ForwardListNode<IterType>* _pointee;
    explicit ForwardListIterator(stlcontainer::ForwardListNode<IterType>* pointee): _pointee(pointee) {};
};

}