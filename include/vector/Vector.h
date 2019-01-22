#include <initializer_list>

#include "vector/VectorIterator.h"

namespace stlcontainer {

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
        
            // Constructors
            // Fill constructor
            explicit Vector(size_t count = 0, const VectorDataType& value = value_type{}): _count(0), _capacity(0) {}

            // Range constructor
            using VectorIterType = stlcontainer::VectorIterator<Vector<VectorDataType>>;
            Vector(VectorIterType firstIter, VectorIterType lastIter): _count(0), _capacity(0) {}

            // Copy constructor
            Vector(const Vector<VectorDataType> &other): _count(0), _capacity(0) {}

            // Move constructor
            Vector(Vector<VectorDataType> &&other) {}

            // Initializer list constructor
            Vector(std::initializer_list<VectorDataType> initList ): _count(0), _capacity(0) {}

            // Destructor
            ~Vector() {};       // TODO delete all _elements

            // Copy assignment
            Vector& operator=(const Vector<VectorDataType>& other) {}

            // Move assignment
            Vector& operator=(Vector<VectorDataType>&& other) noexcept {}

            // TODO Member functions

            // TODO Element access

            // TODO Iterators

            // TODO Capacity

            // TODO Modifiers

            // TODO Non-member functions

        private:
            value_type* elements;
            size_t _count;
            size_t _capacity;
    };          

} // namespace stlcontainer