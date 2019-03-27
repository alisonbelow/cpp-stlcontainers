#include <initializer_list>

#include "vector/VectorIterator.h"

namespace stlcontainer {

    template<typename VectorType> class VectorIterator;     // Forward declare

    template<class VectorDataType>
    class Vector 
    {
    public:
        // Type definitions
        using value_type = VectorDataType;
        using reference = value_type&;
        using pointer = value_type*;
        using const_reference = const value_type&;
        using const_pointer = const value_type*;
        using difference_type = value_type;
        using iterator = stlcontainer::VectorIterator<Vector<VectorDataType>>;
        using const_iterator = const stlcontainer::VectorIterator<Vector<VectorDataType>>;
        using VectorIterType = stlcontainer::VectorIterator<Vector<VectorDataType>>;
    
    public:
        // Constructors
        // Fill constructor
        explicit Vector(size_t count = 0, const VectorDataType& value = value_type{}): _count(0), _capacity(0) 
        {
            reserve( count == 0 ? 1 : count);
            for (auto index = 0; index < count; ++index )
            {
                _elements[index] = value;
            }
            _count = count;
        }

        // TODO Range constructor

        // Copy constructor
        Vector(const Vector<VectorDataType> &other): _count(0), _capacity(0)
        {
            reserve(other._capacity);  
            for (auto index = 0; index != other._capacity; ++index)
            {
                _elements[index] = other._elements[index];
            }
            _count = other._count;
        }

        // Move constructor
        Vector(Vector<VectorDataType> &&other): _count{std::move(other._count)}, _capacity{std::move(other._capacity)}, _elements{std::move(other._elements)}
        {
            other._elements = nullptr;
            other._count = 0;
            other._capacity = 0;
        }

        // Initializer list constructor
        Vector(std::initializer_list<VectorDataType> initList ): _count(0), _capacity(0) 
        {
            reserve(initList.size());
            std::uninitialized_copy(initList.begin(), initList.end(), _elements);
            _count = initList.size();
        }

        // Destructor
        ~Vector() {
            delete[] _elements;
        }

        // Copy assignment
        Vector& operator=(const Vector<VectorDataType>& other) 
        {
            if (this != &other) 
            {
                reserve(other._capacity);
                for (auto index = 0; index != other.size(); ++index)
                {
                    _elements[index] = other._elements[index];
                }
                _count = other._count;
            }
            return *this;
        }

        // Move assignment
        Vector& operator=(Vector<VectorDataType>&& other) noexcept 
        {
            if (this != &other)
            {
                delete[] _elements;
                _elements = other._elements;
                _count = other._count;
                _capacity = other._capacity;

                other._elements = nullptr;
                other._count = 0;
                other._capacity = 0;
            }
            return *this;
        }

        // Member functions
        Vector& operator=(std::initializer_list<VectorDataType> initList) 
        {
            reserve(initList.size());

            // Reassign data to initList
            std::uninitialized_copy(initList.begin(), initList.end(), _elements);
            _count = initList.size();
        }

        void assign(size_t count, const VectorDataType& value) 
        {
            clear();

            reserve(count);
            for (auto index = 0; index < count; ++index )
            {
                _elements[index] = value;
            }
            _count = count;
        }

        // TODO range assignment: void assign(VectorIterType firstIter, VectorIterType lastIter) 

        void assign(std::initializer_list<VectorDataType> initList) 
        {
            clear(); 
            reserve(initList.size());
            std::uninitialized_copy(initList.begin(), initList.end(), _elements);
            _count = initList.size();
        }

        // Element access
        reference at(size_t pos) 
        {
            if (pos >= size() || pos < 0) {
                throw std::out_of_range("Operator stlcontainer::Vector::at()");
            }
            return _elements[pos];
        } 

        const_reference at(size_t pos) const 
        {
            if (pos >= size() || pos < 0) {
                throw std::out_of_range("Operator stlcontainer::Vector::at()");
            }
            return _elements[pos];
        }

        reference operator[](size_t pos) 
        {
            return _elements[pos];
        } 

        const_reference operator[](size_t pos) const 
        {
            return _elements[pos];
        }

        reference front() 
        {
            return *_elements;
        }

        const_reference front() const 
        {
            return *_elements;
        }

        reference back() 
        {
            return *(_elements + size() - 1);
        }

        const_reference back() const 
        {
            return *(_elements + size() - 1);
        }

        VectorDataType* data() noexcept 
        { 
            return _elements;
        }

        // Iterators
        iterator create_iterator(value_type* start_elem, size_t pos) noexcept 
        {
            return iterator(start_elem, pos);
        }

        const_iterator create_iterator(const value_type* start_elem, const size_t pos) const noexcept 
        {
            return const_iterator(start_elem, pos);
        }

        iterator begin() noexcept 
        {
            create_iterator(_elements, 0);
        }

        const_iterator cbegin() noexcept 
        {
            create_iterator(_elements, 0);
        }

        iterator end() noexcept 
        {
            create_iterator(_elements, _count);
        }

        const_iterator cend() noexcept 
        {
            create_iterator(_elements, _count);
        }

        // Capacity
        size_t size() const noexcept 
        {   
            return _count;
        }

        size_t capacity() const noexcept 
        {
            return _capacity;
        }

        bool empty() const noexcept 
        {
            return (size() == 0);
        }

        void reserve(size_t new_capacity) 
        {
            // If new capacity less than or equal to current, return
            if (new_capacity <= capacity()) 
            {
                return;
            }

            // Else, increase capacity, copy elem to new data
            VectorDataType *new_elem = new VectorDataType[new_capacity];

            // Copy elements to new vector, _count stays the same 
            if (size())
            {
                for (size_t index = 0; index != size(); ++index)
                {
                    new_elem[index] = _elements[index];
                }
                delete[] _elements;
            }    

            _capacity = new_capacity;
            _elements = new_elem;
        }

        // Modifiers
        void clear() noexcept 
        {
            delete[] _elements;
            _elements = nullptr;
            _count = 0;
        }

        // TODO iterator erase(const_iterator pos) {}
        // TODO iterator insert(const_iterator pos, const VectorDataType& val) {}
        // TODO other variations of insert              

        void push_back(const VectorDataType& val) 
        {
            if (capacity() < size() + 1) 
            {
                reserve( size() == 0 ? 1 : capacity() * 2);
            }
            _elements[_count++] = val;
        }

        void push_back(VectorDataType&& val) 
        {
            if (capacity() < size() + 1) 
            {
                reserve( size() == 0 ? 1 : capacity() * 2);
            }
            _elements[_count++] = val;
        }

        void pop_back() 
        {
            if (!empty())
            {
                --_count;
            }
            _elements[_count].~VectorDataType();
        }

        void resize(size_t count) 
        {
            if (count == size()) return;

            // Reduce vector to first count elements
            if (count < size())
            {
                for (auto index = size() - 1; index >= count; --index)
                {
                    _elements[index].~VectorDataType();
                    --_count;
                }
            }

            // Default insert count - size() elements
            if (count > size())
            {
                reserve(count + 1);
                for (auto index = size(); index < count; ++index)
                {
                    _elements[index] = VectorDataType();     // Default initialization
                    ++_count;
                }
            }
        }

        void resize(size_t count, const VectorDataType& val) 
        {
            if (count == size()) return;

            // Reduce vector to first count elements
            if (count < size())
            {
                for (auto index = size() - 1; index >= count; --index)
                {
                    _elements[index].~VectorDataType();
                    --_count;
                }
            }

            // Insert count - size() elements with val value
            if (count > size())
            {
                reserve(count + 1);
                for (auto index = size(); index < count; ++index)
                {
                    _elements[index] = val;
                    ++_count;
                }
            }
        }

        void swap(Vector& other) noexcept 
        {
            using std::swap;
            swap(_count, other._count);
            swap(_capacity, other._capacity);
            swap(_elements, other._elements);
        }

        // Non-member functions
        bool operator== (const Vector& lhs) const
        {
            if (size() != lhs.size())
            {
                return false;
            }

            for(auto index = 0; index < size(); ++index)
            {
                if(_elements[index] != lhs._elements[index])
                {
                    return false;
                }
            }
            return true;      
        }

        bool operator!= (const Vector& lhs) const
        {
            return !(*this == lhs);
        }

        bool operator< (const Vector& lhs) const
        {
            bool matchingElems = true;
            for(auto index = 0; index < std::min(size(), lhs.size()); ++index)
            {
                if(_elements[index] > lhs._elements[index])
                {
                    return false;
                }

                matchingElems &= (_elements[index] == lhs._elements[index]);
            }

            if (matchingElems) 
            {
                if (lhs.size() < size())
                {
                    return false;
                }    
            }
            return true;      
        }

        bool operator> (const Vector& lhs) const
        {
            return lhs < *this;
        }

        bool operator<= (const Vector& lhs) const
        {
            return !(lhs < *this);
        }

        bool operator>= (const Vector& lhs) const
        {
            return !(*this < lhs);
        }
        
    private:
        value_type* _elements;
        size_t _count;
        size_t _capacity;
    };          

} // namespace stlcontainer