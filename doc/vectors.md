## Vectors

Vectors are templated with
`template< class T, class Allocator = std::allocator<T>> class vector;`, meaning a vector can be declared as `std::vector<T> myVector`.  

 Type *T* elements types must be CopyAssignable (can be copy-assigned by an lvalue expression e.g. `t = v` returning T&) and CopyConstrutible (copy-constructed from an lvalue expression e.g. `T u = v` or `T(v)`).  

A non-default allocator can be an input into the vector declaration, given that the `value_type` of the allocator is the same as `T`.

Vectors provide a container encapsulating dynamic arrays, automatically handling storage (expansion and contraction). Memory is allocated on the heap. Vector elements are stored contiguously, meaning each element is next to one another in memory.  

### Time Complexity of std::vector

Random access: O(1)  
Insertion/Removal of elements at end: O(1)  
Insertion/Removal of elements, other: O(n)  
Access: O(1)  

### Constructors/Destructors

#### Constructors

(1) Default constructor: empty container. If no allocator supplied, use default-constructed instance. Complexity = const  

```cpp 
vector() noexcept(noexcept(Allocator()));
explicit vector( const Allocator& alloc ) noexcept;
```

(2) Fill constructor: container constructed with `count` copies of elements with value `value`. Complexity = linear in count  

```cpp 
explicit vector( size_type count, const T& value, const Allocator& alloc = Allocator() );
```

(3) Container constructed with `count` default inserted instances of T. NO COPIES MADE. Elements of non-class type (e.g. int) are zeroed. Complexity = linear in count. (since *C++11*, `alloc` added since *C++14*)  

```cpp 
explicit vector( size_type count, const Allocator& alloc = Allocator() );
```

(4) Range Constructor: container constructed with contents of range [`first`, `last`). `inputIter` must be type *LegacyInputIterator*. Each element emplace-constructed from its corresponding element in that range, in the same order. Complexity = linear in distance between `first` and `last`

```cpp 
template< class inputIter >
vector( inputIter first, inputIter last, const Allocator& alloc = Allocator() );
```

(5) Copy constructor. Complexity is linear in size of `other`

```cpp
vector( const vector& other, const Allocator& alloc );
```

(6) Move constructor (`noexcept` added since *C++17*). Does not invalidate pointers/refs/iterators (besides end iterator) to `other`, but all pointers/ref/iterators not refer to `*this`. Complexity is constant

```cpp
vector( vector&& other ) noexcept;
```

(7) Allocator-extended move constructor. If allocators are not the same between `other` and `alloc`, element-wise move takes place. `other` is not guaranteed to be empty in this case. Complexity = constant, linear if allocators are not same. (since *C++11*)

```cpp
vector( vector&& other, const Allocator& alloc );
```

(8) Container constructed with contents of initializer list `ilist`. Copies each of the elenments in `ilist` in same order. Complexity = linear in size of `ilist` (since *C++11*)  

```cpp
vector( std::initializer_list<T> ilist, const Allocator& alloc = Allocator() );
```

#### Destructor

Syntax:

```cpp 
~vector();
```  

Destructors of elements are called. Used storage is deallocated. If vector of pointers, pointer-to objects *are not* destroyed.

Complexity = linear in size of container

### Member Functions

#### std::vector::operator=  

Assigns values to the container. Has both copy assignment and move assignment operator, as well third operator that uses initializer list input.  

(1) Copy assignment operator  
Complexity: linear in size of `*this` and `other`  
After operation, `other`'s contents are preserved.  
Syntax:

```cpp 
vector& operator=(const vector& other);
```  

(2) Move assignment operator  
Complexity: linear in size of `*this` unless allocators dissimilar/do not propagate, then linear in size of `*this` and `other`  
After operation, `other` is in a valid but unspecified state. All elements in originally in `*this` are destroyed or replaced by element-wise move-assignment.  
Syntax:

```cpp 
vector& operator=(vector&& other) noexcept;
```  


(3) Initializer list operator    
Complexity: linear in size of `*this` and `ilist`  
Syntax:

```cpp 
vector& operator=(std::initializer_list<T> ilist);
```

#### std::vector::assign

Similar to constructors (2), (4), and (8). Replaces contents of container with input. Any original vector contents are destroyed, no assignments take place. The vector object itself is, in a sense, reused. This operation can cause an automatic reallocation of storage space IF the new vector size surpasses the current vector capacity.  

Variations:

(1) Fill:replaces contents with `count` copies of `value`  
Syntax:

```cpp 
void assign(size_type count, const T& value);
```  

(2) Range: replaces contents with copies of those in range [`first`, `last`). `InputIter` must satisfy *LegacyInputIterator* type. Does not include elemnt pointed to by `last`.  
Syntax:

```cpp
void assign(InputIter first, InputIter last);
```  

(3) Replaces contents with elements from initializer list `ilist`  
Syntax:

```cpp 
void assign(std::initializer_list<T> ilist);
```  

### Element Access

#### std::vector::at

Returns a reference to element at specified location `pos`. DOES do bound checking (if `pos` >= `size`), and if out of range a std::out_of_range exception is thrown.  
Complexity: constant  
Syntax:

```cpp 
reference std::vector::at(size_type pos);
const_reference std::vector::at(size_type pos) const;
```

#### std::vector::operator[]

Returns reference to element at specified location `pos`. No bounds checking performed.  
Complexity: constant  
Syntax:  

```cpp
reference std::vector::operator[](size_type pos);
const_reference std::vector::operator[](size_type pos) const;
```

#### std::vector::front

Returns reference or const reference to first element in container. Undefined if container is empty.  
Complexity: constant  
Syntax:  

```cpp
reference std::vector::front();
const_reference std::vector::front() const;
```

#### std::vector::back

Returns reference or const reference to last element in container. Undefined if container is empty.  
Complexity: constant  
Syntax:  

```cpp
reference std::vector::back();
const_reference std::vector::back() const;
```

#### std::vector::data

Returns direct pointer or const direct pointer to the first elemnt in memory in the array used to store vector's contents. If size is zero, a null pointer may/may not be returned.  
Complexity: constant  
Syntax:  

```cpp
T* std::vector::data() noexcept;
const T* std::vector::data() const noexcept;
```

### Iterators

Different types of iterators, std::vector uses *RandomAccessIterator*. This is necessary because it enables the O(1) access that many vector operations/functions require.  

**Why do we need reverse iterators?** Because if we reversed with forward iterator the end() points to one past and this would error!
`std::vector<int>::iterator it = v.begin()   // iterator to front of vector`  
`it = v.begin() + 3                          // iterator now points to 4th elem of v`

Reverse iterators provide an easy way to reuse code.  

**auto for loop with iterators:**    
`std::vector<int> numbers;`
`for (auto num:numbers)` -> equal to `(for auto iter - numbers.begin(); iter != numbers.end(); ++iter)`  
`auto` is good because it does incrementing and `!=end()` checking

**Can also do**:   
`for(auto & num:numbers)` -> for modification
`for(const auto& num: numbers)` -> for if you want to print

#### std::vector::begin and std::vector::rbegin

`begin()` returns an iterator to the first element in the container.  
Complexity: constant

```cpp
iterator std::vector::end() noexcept;
const_iterator std::vector::end() const noexcept;
const_iterator std::vector::cend() const noexcept;
```

Similarly, `rbegin()` returns a reverse iterator pointing to the last element in the vector, which is the reverse beginning. rbegin index is one greater than the one for `end()`.

```cpp
iterator std::vector::rbegin() noexcept;
const_iterator std::vector::rbegin() const noexcept;
const_iterator std::vector::crbegin() const noexcept;
```

#### std::vector::end and std::vector::rend

`end()` returns an iterator to the location one past the last element in the container. Iterator type = *RandomAccessIterator*  
Complexity: constant

```cpp
iterator std::vector::end() noexcept;
const_iterator std::vector::end() const noexcept;
const_iterator std::vector::cend() const noexcept;
```

Similarly, `rend()` returns a reverse iterator pointing to the element preceding the first element in the non-reversed vector, which is the reverse end.  

```cpp
iterator std::vector::rend() noexcept;
const_iterator std::vector::rend() const noexcept;
const_iterator std::vector::crend() const noexcept;
```

### Capacity

#### std::vector::empty

Checks if container has no elements. This means `begin() == end()`. Returns `true` if empty. Complexity is constant.  

```cpp
bool std::vector::empty() const noexcept;
```

#### std::vector::size

Returns number of elems in the vector. Return type = `size_t`. Complexity is constant. This value is the *populated* contents of the vector (number of actual objects in vector), converse to `capacity` which is the allocated memory for the entire vector/storage capacity.  

```cpp
size_type std::vector::size() const noexcept;
```

#### std::vector::capacity

Returns the number of elements that the container has currently allocated space for. `capacity` is not defaulted, and must be set using the `reserve()` function. Complexity is constant.

```cpp
size_type std::vector::capacity() const noexcept;
```

`capacity` can be affected by: `reserve`, `shrink_to_fit`, `insert`, `emplace`, `push_back`, `resize`, TODO

#### std::vector::max_size

Returns maximum number of elements the vector can hold. Return type = `size_t`. Complexity is constant. This value is meant to be the max *potential* size the container can hold (due to OS or library implementation limits), but container can still fail to allocate storage for all these elements or be limited due to amount of RAM available.  

```cpp
size_type std::vector::max_size() const noexcept;
```

#### std::vector::reserve

This function *allocates*, does not *initialize* memory. `reserve()` increases the `capacity` of the vector to a value that is greater than or equal to input param `new_capacity`. **The size of the vector is unaffected by this function call**. This function will only perform a capacity increase if `new_capacity` is greater than current `capacity`. Any other value of `new_capacity` does not cause a reallocation and the `capacity` is unaffected. If the vector is modified by this function, iterators, pointers, and references to the vector are invalidated.  
Complexity is *at most* linear in the `size` of the container.  

```cpp
void std::vector::reserve(size_type new_capacity);
```

An example snippet of the code:  
`std::vector<Car> cars;`  
`cars.reserve(100);     // Capacity now increased to 100`  
You can then use `push_back` to add elements to the vector.

#### std::vector::shrink_to_fit

`shrink_to_fit` requested the removal of unused capacity to reduce current `capacity` to `size`. This amount can be Complexity is at most linear in `size` of the container.

```cpp
void std::vector::shrink_to_fit();
```

### Modifiers

#### std::vector::clear

`clear()` is equivalent to called `erase(front(), back()`, which sets `size` to 0. You cannot guarantee that after clearing a vector that the data is or is not available/populated. `capacity` is guaranteed to be modified by `clear()`, nor is a reallocation guaranteed to take place. This function invalidates iterators, references, and pointers to the vector. Complexity is linear in `size` of the container.

```cpp
void std::vector::clear() noexcept;
```

#### std::vector::insert

Vector is extended by inserting new elements before element at specified `pos`, increasing the `size` of the vector. A reallocation will take place (increasing `capacity`) if the new vector size > current vector `capacity`. All elements after `position` index but be reallocated. Iterators are invalidataed if reallocation is caused.

Process:  
(1) Move iterator to position where insertion starts  
(2) Check if vector is full  
(3) If needed, makes space for `val`, `num` of `val`, range, or list contents  
(4) Copy elements as needed to back. If given two iterators (first and last), use std::dist to compute how much to move vector elem by. Elements must be moved from greatest index to least.  

There are five ways of insertion, seen below. Their complexities are commented in the code snippet:

```cpp
/*(1) Single Element: complexity = constant plus linear in distance between pos and end of container*/
iterator std::vector::insert(const_iterator pos, const T& val);

/*(2) Fill: complexity = linear in count plus linear in distance between pos and end of container*/
iterator std::vector::insert(const_iterator pos, size_type num, const T& val);

/*(3) Range: complexity = linear in std::distance between first and last plus linear in distance between pos and end of container*/
iterator std::vector::insert(const_iterator pos, InputIter first, InputIter last);

/*(4) Move: complexity = constant plus linear in distance between pos and end of container*/
iterator std::vector::insert(const_iterator pos, T&& value);

/*(5) Initializer list: complexity = linear in ilist.size() plus linear in distance between pos and end of container*/
iterator std::vector::insert(const_iterator pos, std::initializer_list<T> ilist);
```

#### std::vector::emplace

Inserts a new element in the vector directly before `pos`. The element **is not** moved or copied, it is constructed through *std::allocator_traits::construct* with `args` being forwarded. Size is increased by one. If new `size` is greater than `capacity`, then iterators, pointers, and references are invalidated. All elements displaced by this operation must be moved from greatest to least index. Complexity is linear in distance between `pos` and end of the container. An iterator pointing to the emplaced element is returned.

```cpp
template <class ... Args>
iterator std::vector::emplace(const_iterator pos, Args&& ... args);
```

#### std::vector::erase

Erases element at `pos` or elements in range `first` to `last`, not inclusive of `last`. Supplied parameters must be dereferenceable, meaning you cannot erase `end()` of vector. All vector elements after element(s) erased are moved to a new position after the erase operation. This move aspect of the function call necessitates all vector elements be *MoveAssignable*. Complexity is linear in the number of elements erased and number of element in the vector after erased element(s). This function call invalidates iterators, pointers, and references at or after the point of erase, including `end()`. An iterator pointing to new location of the element that followed the last element erased is returned.

```cpp
iterator std::vector::erase(const_iterator pos);
iterator std::vector::erase(const_iterator first, const_iterator last);
```

#### std::vector::push_back

Appends the given element to end of the container. There are two forms of `push_back`, (1) where the new element is initialized as a copy of input `value`, and (2) where input `value` is moved into the new element. Increases `size` by one. If new `size` is greater than capacity, then an automatic reallocation of vector storage occurs where `capacity` is doubled. The `end` iterator is always invalidated with this operation. If a reallocation happens then all iterators, pointers, and references are invalidated. Data races can also occur with a reallocation (all container elements modified). Complexity is constant, but if a reallocation occurs can be up to linear in `size` of the vector.

```cpp
void std::vector::push_back(const T& value);
void std::vector::push_back(T&& value);
```

It is good practice to reserve x locations in your vector and to then use push_back to add elements. You can also pair `shrink_to_fit` with `push_back` as, effectively, you know your push_back operation is safe as the vector has been shrunk to a manageable size that will not cause a reallocation.

A vector cannot be iterated through using `size()` and `push_back` as follows:

```cpp
for(int i = 0; i < myVector.size(); i++) {
    myVector.push_back(i);
}
```

Because size increases every time a new element is added, the example code will never terminate. Similarly, because of iterator invalidation, the following code should not be executed:

```cpp
for(int i : myVector) {
   myVector.push_back(i);
}
```

In this example, the iterator `end()` will become invalidated during a `push_back` operation.


#### std::vector::emplace_back

Appends a new element to the end of a vector. The element **is not** moved or copied, it is constructed through *std::allocator_traits::construct* with `args` being forwarded. Size is increased by one. If new `size` is greater than `capaciity`, then all iterators, pointers, and references are invalidated. Else, only the `end()` iterator is invalidated. A reference to the inserted element is returned. Complexity is constant, but if a reallocation occurs can be up to linear in `size` of the vector.

```cpp
template<class ... Args>
reference std::vector::emplace_back(Args&& ... args);
```

#### std::vector::pop_back

Removes last element of a container. Iterators `back()` and `end()` are invalidated. Complexity is constant. `size` is decreased by 1.

```cpp
void std::vector::pop_back();
```

#### std::vector::resize

(1) If the new size `count` is greater than `size` of the vector, all `count` elements in the vector will be preserved; the remaining elements will be initialized according to the second parameter. Either default-inserted elements are appended to the vector or copies of `value` are appended to the vector. The `capacity` will equal `size` after this call.  
(2) If the new size `count` is smaller than `size`, only `count` elements are preserved, as the container is reduced to its first `count` elements. The rest of the elements are discarded and shouldn't be used any more- consider these elements invalid.  
(3) If the new size `count` is larger than `capacity`, a reallocation will take place, increasing `capacity`.  

Even in situation (2), `resize` will never shrink `capacity`. This operation invalidates iterator `back()`, and can invalid all iterators, pointers, and references if a reallocation occurs. In situation (1) and (2), all pointers, iterators, and references to `count` elements remain valid. Complexity is linear in the number of elements inserted and erased. If a reallocation occurs complexity is linear for the vector's `size`.

```cpp
void std::vector::resize(size_type count);
void std::vector::resize(size_type count, const value_type& val);
```

#### std::vector::swap

The contents of the container are exchanged with `other`. No move, copy, or swap operations are performed on individual elements, pointers are just reassigned. Complexity is constant. Iterators, pointers, and references to container contents **are not** invalidated. However, `end()` iterators do not refer to elements and may be invalidated. 

```cpp
void std::vector::swap(vector& other) noexcept;
```

### Non-Member Functions

#### Relational Operators

##### std::vector::operator ==

```cpp
template <class T, class Alloc>
    bool std::vector::operator== (const std::vector<T, Alloc>& lhs, const std::vector<T, Alloc>&rhs);
```

Sizes are compared first. If they match, the elements are sequentially compared using the `==` operator, stopping at the first mismatch, if any. Complexity is constant if `rhs` and `lhs` `size` differs. Complexity is linear in size of equality comparison otherwise.

##### std::vector::operator <

```cpp
template <class T, class Alloc>
    bool std::vector::operator< (const std::vector<T, Alloc>& lhs, const std::vector<T, Alloc>&rhs);
```

Vector elements are compared lexiographically, checking that contents of `lhs` are less than the contents of `rhs`. Complexity is linear up to the smaller `size` between `lhs` and `rhs`.  


```cpp
template <class T, class Alloc>
    bool std::vector::operator!= (const std::vector<T, Alloc>& lhs, const std::vector<T, Alloc>&rhs);

template <class T, class Alloc>
    bool std::vector::operator> (const std::vector<T, Alloc>& lhs, const std::vector<T, Alloc>&rhs);

template <class T, class Alloc>
    bool std::vector::operator<= (const std::vector<T, Alloc>& lhs, const std::vector<T, Alloc>&rhs);

template <class T, class Alloc>
    bool std::vector::operator>= (const std::vector<T, Alloc>& lhs, const std::vector<T, Alloc>&rhs);
```

The operations `!=`, `>`, `<=`, `>=` are performed by making use of existing operators `==` and `<`.  

`a != b` corresponds to `!(a == b)`  
`a > b` corresponds to `b < a`  
`a <= b` corresponds to `!(b < a)`  
`a >= b` corresponds to `!(a < b)`  

Complexity for `!=` is constant if `rhs` and `lhs` `size` differs. Complexity is linear in size of equality comparison otherwise.  

Complexity for remaining operators is linear up to the smaller `size` between `lhs` and `rhs`.  

### References

https://en.cppreference.com/w/cpp/container/vector
https://en.cppreference.com/w/cpp/named_req/CopyAssignable
https://en.cppreference.com/w/cpp/named_req/CopyConstructible
http://john-ahlgren.blogspot.com/2013/10/stl-container-performance.html
https://www.bfilipek.com/2014/05/vector-of-objects-vs-vector-of-pointers.html-
http://www.cplusplus.com/reference/vector/vector/vector/
https://www.codeguru.com/cpp/cpp/cpp_mfc/stl/article.php/c4027/C-Tutorial-A-Beginners-Guide-to-stdvector-Part-1.htm

<br><br><br>*NOTE all documentation assuming C++ 17 standard*