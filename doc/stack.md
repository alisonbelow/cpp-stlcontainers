## Stack

The stack class is a **container adapter** that provides a LIFO (Last In, First Out) data structure to use. The stack is a wrapper around whatever container is underlying. Operations are limited for std::stack.  

The underlying container must be a *SequenceContainer*, and it must provide the following functions:
* back()
* push_back()
* pop_back()

Examples of containers that can be used are `std::vector`, `std::deque`, and `std::list`. The default container is `std::deque`.

Stacks do not have iterators because the only element available to access is the top-most.

Complexity for most stack operators are constant (*O*(1)): push(), pop(), top(), size(), and empty() all have a constant complexity.

### Member Functions

#### Constructor

(1) Default: value-initializes the container

```cpp
std::stack::stack() : stack(Container());
```

(2) Copy Container Constructor: constructs underlying container with contents of `cont`

```cpp
explicit std::stack::stack(const Container& cont);
```

(3) Move Container Constructor: move-constructs the underlying container

```cpp
explicit std::stack::stack(Container&& cont);
```

(4) Copy Constructor: constructs with copy of `other`

```cpp
std::stack::stack(const Stack& other);
```

(5) Move Constructor: move-constructs stack

```cpp
std::stack::stack(stack&& other);
```

(6) - (7) all are Allocator based constructors that will not be covered

#### Destructor

```cpp
std::stack~stack();
```

Destroys stack object. Destructors of elements called and storage destroyed. Complexity is linear in size of container adaptor.

#### std::stack::operator=  

Replaces contents of container adapater with `other`'s. Two variations exist: copy and move assignment

(1) Copy assignment: replaces the contents with a copy of the contents of `other`. Calls `_container = other._container`.

```cpp
stack& std::stack::operator=(const stack& other);
```

(2) Move assignment: replaces the contents with those of `other` using move semantics. Calls `_container = std::move(other._container)`.

```cpp
stack& std::stack::operator=(stack&& other);
```

### Member Functions: Element Access

#### std::stack::top

Returns a reference to the top elem in stack, the most recently pushed element. Uses pop() to return. Same as `_container.back()`. Complexity is constant.

```cpp
reference std::stack::top();
const_reference std::stack::top() const;
```

### Member Functions: Capacity

#### std::stack::empty

Checks if underlying container has no elements. Same as `_container.empty()`. Complexity is constant.

```cpp
bool std::stack::empty() const;
```

#### std::stack::size

Checks number of elements in underlying container. Same as `_container.size()`. Complexity is constant.

```cpp
size_type std::stack::size() const;
```

### Member Functions: Modifiers

#### std::stack::push

Pushes the given element to the top of the stack. There are two variations of `push`, one that copies the contents of `value` and one that moves `value` using move semantics. Complexity is equal to `container::push_back()`. 

```cpp
void std::stack::push(const value_type& value);
void std::stack::push(value_type&& value);
```

#### std::stack::emplace

Pushes a new element on top of stack, constructing the element in place without a copy or mvoe operation. Will not be covered.

#### std::stack::pop

Removes the top element from the stack. Equivalent to calling `_container.pop_back()`. Complexity is equal to `container::pop_back()`.

```cpp
void std::stack::pop();
```

#### std::stack::swap

Exchanges contents of container adapter with those of `other`. Uses `std::swap`. Complexity is same as underlyng container, which is typically constant.

```cpp
void std::stack::swap(stack& other) noexcept;
```

### Non-Member Functions: swap

#### std::swap

Specializes `std::swap` algorithm for `std::stack`. Swaps contents of `lhs` and `rhs`. Complexity is same as underlying container. No exceptions as of C++17.

```cpp
template<class T, class Container> void swap( stack<T, Container>& lhs, stack<T, Container>& rhs ) noexcept;

```

### Non-Member Functions: Relational Operators

#### std::stack::operator ==, !=, <, >, <=, >=

Compares the underlying containers' contents of the two container adaptors. The container's operator is used to do the comparison. Complexity is linear in size of the container. Returns true if comparison is true, else false.

```cpp
template<class T, class Container> bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) const;

template<class T, class Container> bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) const;

template<class T, class Container> bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) const;

template<class T, class Container> bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) const;

template<class T, class Container> bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) const;

template<class T, class Container> bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) const;
```