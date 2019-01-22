#include <iterator>

namespace stlcontainer {

    // https://en.cppreference.com/w/cpp/iterator/iterator
    template<class VectorType>
    class VectorIterator : public std::iterator<
            std::random_access_iterator_tag,    // iterator_category
            VectorType,                         // value_type
            VectorType,                         // difference_type
            const VectorType*,                  // pointer
            const VectorType&>                  // reference
    {
        public:
            // Constructor
            explicit VectorIterator(VectorType* elem = nullptr, size_t index = 0) : _start_elem(elem), _index(index) {};

            // Destructor
            ~VectorIterator() = default;            

            // Dereferencing operators
            VectorType& operator*() const { return _start_elem[_index]; };
            VectorType* operator->() const { return &_start_elem[_index]; };

            // Increment
            // pre (++I) 
            VectorIterator& operator++() 
            {
                ++_index;
                return *this;
            };

            // post (I++)
            VectorIterator operator++(int) 
            {
                VectorIterator temp(*this);     // copy
                ++_index;
                return temp;                    // return copy
            };

            // Decrement
            // pre (--I)
            VectorIterator& operator--() 
            {
                --_index;
                return *this;
            };
            
            // post (I++)
            VectorIterator operator--(int) 
            {
                VectorIterator temp(*this);     // copy
                --_index;
                return temp;                    // return copy
            };

            // Comparison operators
            bool operator ==(const VectorIterator& rhs) const 
            {
                return (_start_elem == rhs._start_elem) && (_index == rhs._index);
            };

            bool operator !=(const VectorIterator& rhs) const 
            {
                return !(this == rhs);
            };

            // Arithmetic operators
            VectorIterator operator+(size_t step) 
            {
                return VectorIterator(_start_elem, _index + step);
            };

            VectorIterator operator-(size_t step) 
            {
                return VectorIterator(_start_elem, _index - step);
            };
    
            // Difference
            size_t operator-(const VectorIterator& other) 
            {
                return _index - other._index;
            };

            // Inequality comparisons
            bool operator<(const VectorIterator& other) 
            {
                return _index < other._index;
            };

            bool operator>(const VectorIterator& other) 
            {
                return other._index < _index;
            };

            bool operator<=(const VectorIterator& other) 
            {   
                return !(other._index < _index);    
            };

            bool operator>=(const VectorIterator& other) 
            {
                return !(_index < other._index);
            };

            // Compound assignment operators
            VectorIterator& operator +=(size_t step) 
            {
                this->_index += step;
                return *this;
            };

            VectorIterator& operator -=(size_t step) 
            {
                this->_index -= step;
                return *this;
            };    
    
        private:
            VectorType* _start_elem;
            size_t _index;
    };

}   // namespace stlcontainer
 
