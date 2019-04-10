#include <initializer_list>

#include "ForwardListIterator.h"

namespace stlcontainer
{

template<typename ListDataType>
class ForwardList
{
// Type definitions
private:
    using forward_list_node = typename stlcontainer::ForwardListNode<ListDataType>;
    using node_pointer = typename stlcontainer::ForwardListNode<ListDataType>*;

public:
    using value_type = ListDataType;
    using reference = value_type&;
    using const_reference = const reference;
    using iterator = typename stlcontainer::ForwardListIterator<ListDataType>;
    using const_iterator = const iterator;

public:
    // Member Functions: Constructors
    // Default constructor
    explicit ForwardList() : _head(make_node(value_type{}, nullptr)), _tail(_head) {};

    // Fill constructor
    ForwardList(size_t count, ListDataType value) : _head(make_node(value, nullptr)), _tail(_head)
    {
        auto prev_node = _head;
        size_t index = 0;
        while (++index < count)   // pre-increment of index means can use count, not (count - 1)
        {
            auto new_node = make_node(value, nullptr);
            prev_node->_next = new_node;
            prev_node = new_node;
        }
        _tail = make_node(value_type{}, nullptr);   // One past last node
        prev_node->_next = _tail;
    }

    // TODO range constructor

    // Copy constructor
    ForwardList(const ForwardList& other) : _head(make_node(other._head->_value, nullptr)), _tail(_head)
    {
        auto next_node = other._head->_next;
        auto prev_node = _head;
        while (next_node != other._tail)
        {
            auto new_node = make_node(next_node->_value, nullptr);
            prev_node->_next = new_node;  
            prev_node = new_node;
            next_node = next_node->_next;
        }
        _tail = make_node(value_type{}, nullptr);   // One past last node
        prev_node->_next = _tail;
    } 

    // Move constructor
    ForwardList(ForwardList&& other) : _head(std::move(other._head)), _tail(std::move(other._tail))
    {
        other._head = nullptr;
        other._tail = nullptr;
    }

    // Initializer list constructor
    ForwardList(std::initializer_list<ListDataType> initList): _head(make_node(*initList.begin(), nullptr)), _tail(_head)
    {
        auto prev_node = _head;
        auto initListIter = initList.begin();
        while (++initListIter != initList.end())
        {
            auto new_node = make_node(*initListIter, nullptr);
            prev_node->_next = new_node;
            prev_node = new_node;
        }
        _tail = make_node(value_type{}, nullptr);   // One past last node
        prev_node->_next = _tail;
    }

    // Member Functions: Destructor
    ~ForwardList() = default;

    // Member Functions: Assignment Operator and assign
    ForwardList& operator=(const ForwardList& other) 
    {
        _head = make_node(other._head->_value, nullptr);
        _tail = _head;

        auto next_node = other._head->_next;
        auto prev_node = _head;
        while (next_node != other._tail)
        {
            auto new_node = make_node(next_node->_value, nullptr);
            prev_node->_next = new_node;  
            prev_node = new_node;
            next_node = next_node->_next;
        }
        _tail = make_node(value_type{}, nullptr);   // One past last node
        prev_node->_next = _tail;
    }

    ForwardList& operator=(ForwardList&& other) noexcept 
    {
        _head = std::move(other._head);
        _tail = std::move(other._tail);
        other._head = nullptr;
        other._tail = nullptr;
    }

    ForwardList& operator=(std::initializer_list<ListDataType> initList) 
    {
        _head = make_node(*initList.begin(), nullptr);
        _tail = _head;

        auto prev_node = _head;
        auto initListIter = initList.begin();
        while (++initListIter != initList.end())
        {
            auto new_node = make_node(*initListIter, nullptr);
            prev_node->_next = new_node;
            prev_node = new_node;
        }
        _tail = make_node(value_type{}, nullptr);   // One past last node
        prev_node->_next = _tail;
    }

    void assign(size_t count, ListDataType value) 
    {
        _head = make_node(value, nullptr); 
        _tail = _head;

        auto prev_node = _head;
        size_t index = 0;
        while (++index < count)   // pre-increment of index means can use count, not (count - 1)
        {
            auto new_node = make_node(value, nullptr);
            prev_node->_next = new_node;
            prev_node = new_node;
        }
        _tail = make_node(value_type{}, nullptr);   // One past last node
        prev_node->_next = _tail;
    }
    
    // TODO void assign(iterator first, iterator last) {}
    
    void assign(std::initializer_list<ListDataType> initList) 
    {
        *this = initList;
    }

    // Member Functions: Element Access
    reference front() 
    {
        return _head->_value;
    }

    const_reference front() const
    {
        return _head->_value;
    }

    // Member Functions: Iterators
    iterator before_begin() noexcept
    {
        auto ret_node = make_node(value_type{}, _head);
        return iterator(ret_node);
    }

    iterator begin() noexcept
    {
        return iterator(_head);
    }

    const_iterator begin() const noexcept
    {
        return iterator(_head);
    }

    iterator end() noexcept
    {
        return iterator(_tail);
    }

    const_iterator end() const noexcept
    {
        return iterator(_tail);
    }

    // Member Functions: Capacity
    bool empty() const noexcept
    {
        return _head == _tail;
    }

    // TODO size_t max_size const noexcept {}

    // Member Functions: Modifiers
    void clear() noexcept
    {
        // auto node_to_delete = _head;
        while(_head != _tail)
        {
            auto node_to_delete = _head;
            _head = _head->_next;
            delete node_to_delete;
        }
    }

    iterator insert_after(const_iterator pos, const ListDataType& value)
    {
        auto node_before = pos._pointee;
        auto new_node = make_node(value, node_before->_next);
        node_before->_next = new_node;
        return iterator(new_node);
    }

    iterator insert_after(const_iterator pos, ListDataType&& value) 
    {
        auto node_before = pos._pointee;
        auto new_node = make_node(std::move(value), node_before->_next);
        node_before->_next = new_node;
        return iterator(new_node);   
    }
    
    iterator insert_after(const_iterator pos, size_t count, const ListDataType& value) 
    {
        auto node_before = pos._pointee;
        size_t num_inserted = 0;
        while(num_inserted < count)
        {
            auto new_node = make_node(value, node_before->_next);
            node_before->_next = new_node;
            ++num_inserted;
        }
        return iterator(node_before->_next);
    }
    
    iterator insert_after(const_iterator pos, iterator first, iterator last)
    {
        auto node_before = pos._pointee;
        auto node_after = pos._pointee->_next;
        while(first != last)
        {
            auto new_node = make_node(*first, node_after);
            node_before->_next = new_node;
            node_before = new_node;
            ++first;
        }
        return iterator(node_before->_next);
    }
    
    iterator insert_after(const_iterator pos, std::initializer_list<ListDataType> initList)
    {
        auto node_before = pos._pointee;
        auto node_after = pos._pointee->_next;
        for (auto elem : initList)
        {
            auto new_node = make_node(elem, node_after);
            node_before->_next = new_node;
            node_before = new_node;
        }
        return iterator(node_before->_next);
    }

    iterator erase_after(const_iterator pos) 
    {
        auto node_after = pos._pointee;
        auto node_to_point_to = node_after->_next;
        node_after->_next = node_to_point_to->_next;
        delete node_to_point_to;
        return iterator(node_after->_next);
    }

    iterator erase_after(const_iterator first, const_iterator last) 
    {
        auto node_after = first._pointee;
        auto node_to_point_to = node_after->_next;

        while(node_to_point_to != last._pointee)
        {
            node_after->_next = node_to_point_to->_next;
            delete node_to_point_to;
            node_to_point_to = node_after->_next;
        }
        return iterator(node_after->_next);     // Equivalent to returnng last
    }

    void push_front(const ListDataType& value)
    {
        auto new_node = make_node(value, _head);
        _head = new_node;        
    }

    void push_front(ListDataType&& value)
    {
        auto new_node = make_node(value, _head);
        _head = new_node;
    }

    void pop_front()
    {
        _head = _head->_next;
    }

    void resize(size_t count)
    {
        resize(count, ListDataType{});
    }

    void resize(size_t count, const ListDataType& val)
    {
        auto curr_size = 0;
        auto iter = begin();
        auto eraseIter = begin();
        while (iter != end())
        {
            ++iter;
            ++curr_size;

            if (curr_size < count)
            {
                ++eraseIter;
            }
        }
        if (curr_size == count) 
        {
            return;
        }

        if (curr_size > count)
        {
            erase_after(eraseIter, end());
        } 

        if (curr_size < count)
        {
            while (curr_size != count)
            {
                insert_after(iter, ListDataType{});
                ++iter;
                ++curr_size;
            }  
        }
    }

    void swap(ForwardList& other) noexcept
    {
        using std::swap;
        swap(_head, other._head);
        swap(_tail, other._tail);
    }

    // Member Functions: Operations
    
    void merge(ForwardList& other) 
    {
        auto iter = begin();
        auto otherIter = other.begin();
        auto traverse_node = make_node(ListDataType{}, nullptr);
        auto new_head = traverse_node;

        size_t count = 0;
        while (iter != end() && otherIter != other.end())
        {
            if (*iter <= *otherIter)
            {
                traverse_node->_next = iter._pointee;
                ++iter;
            } else {
                traverse_node->_next = otherIter._pointee;
                ++otherIter;
            }
            ++count;
            traverse_node = traverse_node->_next;
        }

        while (iter != end())
        {
            traverse_node->_next = iter._pointee;
            ++iter;
            traverse_node = traverse_node->_next;
        }

        while (otherIter != other.end())
        {
            traverse_node->_next = otherIter._pointee;
            ++otherIter;
            traverse_node = traverse_node->_next;
        }
        _head = new_head->_next;
    }

    // TODO void merge(ForwardList&& other) {}
    // TODO void splice_after(const_iterator pos, ForwardList& other) {}
    // TODO void splice_after(const_iterator pos, ForwardList&& other) {}
    // TODO void splice_after(const_iterator pos, ForwardList& other, const_iterator it) {}
    // TODO void splice_after(const_iterator pos, ForwardList&& other, const_iterator it) {}
    // TODO void splice_after(const_iterator pos, ForwardList& other, const_iterator first, const_iterator last) {}
    // TODO void splice_after(const_iterator pos, ForwardList&& other, const_iterator first, const_iterator last) {}
    
    void remove(const ListDataType& value) 
    {
        auto traverse_node = begin();
        while (traverse_node != end())
        {
            if (traverse_node._pointee->_next->_value == value)
            {
                erase_after(traverse_node);
            }
            ++traverse_node; 
        }
    }

    void reverse() noexcept 
    {
        auto prev_node = make_node(ListDataType{}, nullptr); 
        auto curr_node = _head; 
        auto next_node = make_node(ListDataType{}, nullptr);
        while (curr_node->_next != nullptr)
        {
            next_node = curr_node->_next;
            curr_node->_next = prev_node;
            prev_node = curr_node;
            curr_node = next_node;
        }
        _head = prev_node;
    }
    
    void unique()
    {
        auto curr_node = _head->_next;
        auto prev_node = _head;
        auto next_node = _head;

        while (prev_node != _tail)
        {
            next_node = curr_node->_next;
            if (prev_node->_value == curr_node->_value)
            {
                // Remove curr_node
                delete curr_node;
                prev_node->_next = next_node;    
            } else {
                prev_node = curr_node;
            }
            curr_node = next_node;
        }
    }

    // TODO void sort() {}

    // Non-Member Functions: Relational operators, swap declaration
    template<class myListDataType> 
    friend bool operator==(const ForwardList<myListDataType>& lhs, const ForwardList<myListDataType>& rhs);

    template<class myListDataType> 
    friend bool operator!=(const ForwardList<myListDataType>& lhs, const ForwardList<myListDataType>& rhs);

    template<class myListDataType> 
    friend bool operator<(const ForwardList<myListDataType>& lhs, const ForwardList<myListDataType>& rhs);

    template<class myListDataType> 
    friend bool operator>(const ForwardList<myListDataType>& lhs, const ForwardList<myListDataType>& rhs);

    template<class myListDataType> 
    friend bool operator<=(const ForwardList<myListDataType>& lhs, const ForwardList<myListDataType>& rhs);

    template<class myListDataType> 
    friend bool operator>=(const ForwardList<myListDataType>& lhs, const ForwardList<myListDataType>& rhs);

    template<class myListDataType> 
    friend void swap(ForwardList<myListDataType>& lhs, ForwardList<myListDataType>& rhs) noexcept;

private:
    node_pointer _head;
    node_pointer _tail;

    node_pointer make_node(value_type val, node_pointer node_ptr)
    {
        return new stlcontainer::ForwardListNode<ListDataType>(val, node_ptr);
    }
};

// Non-Member Functions

// TODO relational operators

template <class ListDataType>
void swap(ForwardList<ListDataType>& lhs, ForwardList<ListDataType>& rhs) noexcept
{
    lhs.swap(rhs);
}

} // namespace stlcontainer