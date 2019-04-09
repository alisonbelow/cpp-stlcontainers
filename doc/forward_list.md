## Forward List

The forward_list class is a container that supports fast insertion and removal of elements from anywhere in the container. However, fast random access is not supported. A forward list is essentially a singly linked list. Compared to `std::list`, the container allows more space-efficient storage when bi-direction iteration is not needed.

Adding, removing, and moving the elements in a list **does not** invalidate pointers/iterators referring to other list elems. The containers functions take care of this.

### Member Functions

#### Constructor

(1) Default: value-initializes the container

```cpp
std::forward_list::forward_list();
```

(2) Fill Constructor: constructs container with `count` elements. Complexity linear in count.

```cpp
std::forward_list::forward_list(size_t count);
std::forward_list::forward_list(size_t count, const value_type& val);
```

(3) Range Constructor: constructs container with elem in range [`first`, `last`). Complexity linear in distance between first and last.

```cpp
template class<InputIter>
std::forward_list::forward_list(InputIter first, InputIter last);
```

(4) Copy Constructor: constructs with copy of each of the elements in `other`. Complexity linear in size of other.

```cpp
std::forward_list::forward_list(const ForwardList& other);
```

(5) Move Constructor: move-constructs forward_list. Complexity constant.

```cpp
std::forward_list::forward_list(ForwardList&& other);
```

(6) Initializer List Constructor: constructs with copy of each element in initializer list. Complexity linear in size of init.

```cpp
std::forward_list::forward_list(std::initializer_list<value_type> initList);
```

#### Destructor

```cpp
std::forward_list~forward_list();
```

Destroys forward_list object. Destructors of elements called and storage deallocated. Complexity is linear in size of container.

#### std::forward_list::operator=  

Replaces contents of container adapater with `other`'s or initializer list contents.

(1) Copy assignment: replaces the contents with a copy of the contents of `other`.

```cpp
forward_list& std::forward_list::operator=(const forward_list& other);
```

(2) Move assignment: replaces the contents with those of `other` using move semantics.

```cpp
forward_list& std::forward_list::operator=(forward_list&& other);
```

(3) Initializer List assignment: replaces the contents with those identified by initializer list `initList`.

```cpp
forward_list& std::forward_list::operator(std::initializer_list<T> initList);
```

#### std::forward_list::assign

There are 3 variations of assign for `forward_list`. Replaces contents of container.

(1) Fill assign - new contents are `count` elements initialized to a copy of `val`. Complexity is linear in `count`.

```cpp
void std::forward_list::assign(size_t count, const T& val);
```

(2) Range assign - contents are elements constructed from each of the elements in range between `first` and `last`. Complexity is linear in distance between `first` and `last`.

```cpp
template<InputIter>
void std::forward_list::assign(InputIter first, InputIter last);
```

(3) Initializer list assign - new contents are copies of the values passed as initializer list, in the same order. Complexity is linear in `initList.size()`.

```cpp
void std::forward_list::assign(std::initializer_list<T> initList);
```

### Member Functions: Element Access

#### std::forward_list::front

Returns a reference to the first elem in the list. Complexity is constant.

```cpp
reference std::forward_list::front();
const_reference std::forward_list::front() const;
```

### Member Functions: Iterators

#### std::forward_list::before_begin

Returns an iterator to the element before beginning. Essentially placeholder, cannot access it. Used in `insert_after()`, `emplace_after()`, `erase_after()`, `splice_after()`, and increment operator. Constant complexity.

```cpp
iterator std::forward_list::iterator::before_begin() noexcept;
const_iterator std::forward_list::iterator::before_begin() const noexcept;
const_iterator std::forward_list::iterator::cbefore_begin() const noexcept;
```

#### std::forward_list::begin, cbegin

Returns iterator to first elem in container. If container empty, iterator will be equal to `end()`. Constant complexity.

```cpp
iterator std::forward_list::iterator::begin() noexcept;
const_iterator std::forward_list::iterator::begin() const noexcept;
const_iterator std::forward_list::iterator::cbegin() const noexcept;
```

#### std::forward_list::end, cend

Returns iterator to one position past the last elem in container. Essentially placeholder, cannot access it. Constant complexity.

```cpp
iterator std::forward_list::iterator::end() noexcept;
const_iterator std::forward_list::iterator::end() const noexcept;
const_iterator std::forward_list::iterator::cend() const noexcept;
```

### Member Functions: Capacity

#### std::forward_list::empty

Checks if list has no elements. Complexity is constant.

```cpp
bool std::forward_list::empty() const noexcept;
```

#### std::forward_list::max_size

Returns maximum number of elements the container is able to hold. Varies due to system/library implementation limitations. Complexity is constant.

```cpp
size_type std::forward_list::max_size() const noexcept;
```

### Member Functions: Modifiers

#### std::forward_list::clear

Erases all elements from the container. `size()` should return zero. Invalidates any references, pointers, or iterators referring to contained elems. Complexity is linear in size of container.

```cpp
void clear() noexcept {};
```

#### std::forward_list::insert_after

Insert elements after the specified position in the container. Can insert one or `count` elements. Returns iterator to last element inserted, or other if input is invalid for insertion. There are 5 variations of `insert_after`.

```cpp
// Copy insert - constant complexity
iterator std::forward_list::insert_after(const_iterator pos, const T& value);

// Move insert - constant complexity
iterator std::forward_list::insert_after(const_iterator pos, const T&& value);

// Fill insert - linear in count, return pos if count == 0
iterator std::forward_list::insert_after(const_iterator pos, size_t count, const T& value);

// Range insert - linear in distance between first and last, returns pos if first == last
template<typename InputIter>
iterator std::forward_list::insert_after(cosnt_iterator pos, InputIter first, InputIter last);

// Initializer list insert - complexity linear in initList.size(), returns pos if initList empty
iterator std::forward_list::insert_after(const_iterator pos, std::initializer_list<T> initList);
```

#### std::forward_list::emplace_after, not covered

#### std::forward_list::erase_after

Erases one to (first, last) elements. Constant complexity or linear in distance between `first` and `last`.

```cpp
iterator std::forward_list::erase_after(const_iterator pos)
iterator std::forward_list::erase_after(const_iterator first, const_iterator last)
```

#### std::forward_list::push_front

Add element to front of list. Constant complexity.

```cpp
void std::forward_list::push_front(const T& value)
void std::forward_list::push_front(T&& value)
```

#### std::forward_list::emplace_front, not covered

#### std::forward_list::pop_front

Removes first element from container. Constant complexity.

```cpp
void std::forward_list::pop_front();
```

#### std::forward_list::resize

Resizes container to `count` elements. If current size greater than count, container is reduced to first `count` elements. If current size is less than `count`, additional default or specified values are appended. Complexity is linear in distance between current size and `count`.

```cpp
void std::forward_list::resize(size_t count);
void std::forward_list::resize(size_t count, const T& value);
```

#### std::forward_list::swap

Exchanges contents between container and `other`. Does not move, copy or swap individual elements. Constant complexity.

```cpp
void std::forward_list::swap(forward_list other&);
```

### Member Functions: Operations
#### std::forward_list::merge
#### std::forward_list::splice_after
#### std::forward_list::remove, remove_if
#### std::forward_list::reverse
#### std::forward_list::unique
#### std::forward_list::sort

### Non-Member Functions: swap

#### std::swap

Specializes `std::swap` algorithm for `std::forward_list`. Swaps contents of `lhs` and `rhs`. Complexity is constant. No exceptions as of C++17.

```cpp
template<class T, class Container> void swap( forward_list<T, Container>& lhs, forward_list<T, Container>& rhs ) noexcept;
```

### Non-Member Functions: Relational Operators

#### std::forward_list::operator ==, !=, <, >, <=, >=

Compares the containers' contents. Returns true if comparison is true, else false.

```cpp
template<class T, class Container> bool operator==(const forward_list<T, Container>& lhs, const forward_list<T, Container>& rhs) const;

template<class T, class Container> bool operator!=(const forward_list<T, Container>& lhs, const forward_list<T, Container>& rhs) const;

template<class T, class Container> bool operator<(const forward_list<T, Container>& lhs, const forward_list<T, Container>& rhs) const;

template<class T, class Container> bool operator>(const forward_list<T, Container>& lhs, const forward_list<T, Container>& rhs) const;

template<class T, class Container> bool operator<=(const forward_list<T, Container>& lhs, const forward_list<T, Container>& rhs) const;

template<class T, class Container> bool operator>=(const forward_list<T, Container>& lhs, const forward_list<T, Container>& rhs) const;
```