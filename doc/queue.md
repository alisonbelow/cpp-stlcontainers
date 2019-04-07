## Queue

The queue class is a **container adapter** that provides a FIFO (First In, First Out) data structure to use. The queue is a wrapper around whatever container is underlying. Operations are limited for std::queue.  

The underlying container must be a *SequenceContainer*, and it must provide the following functions:
* back()
* front()
* push_back()
* pop_front()

Examples of containers that can be used are `std::deque`, and `std::list`. The default container is `std::deque`. Cannot use `std::vector` because of the needed `pop_front()` function

Complexity for most queue operators are constant (*O*(1)): push(), pop(), back(), size(), and empty() all have a constant complexity.

### Member Functions

#### Constructor

(1) Default: value-initializes the container

```cpp
std::queue::queue() : queue(Container());
```

(2) Copy Container Constructor: constructs underlying container with contents of `cont`

```cpp
explicit std::queue::queue(const Container& cont);
```

(3) Move Container Constructor: move-constructs the underlying container

```cpp
explicit std::queue::queue(Container&& cont);
```

(4) Copy Constructor: constructs with copy of `other`

```cpp
std::queue::queue(const Queue& other);
```

(5) Move Constructor: move-constructs queue

```cpp
std::queue::queue(Queue&& other);
```

(6) - (7) all are Allocator based constructors that will not be covered

#### Destructor

```cpp
std::queue~queue();
```

Destroys queue object. Destructors of elements called and storage destroyed. Complexity is linear in size of container adaptor.

#### std::queue::operator=  

Replaces contents of container adapater with `other`'s. Two variations exist: copy and move assignment

(1) Copy assignment: replaces the contents with a copy of the contents of `other`. Calls `_container = other._container`.

```cpp
queue& std::queue::operator=(const queue& other);
```

(2) Move assignment: replaces the contents with those of `other` using move semantics. Calls `_container = std::move(other._container)`.

```cpp
queue& std::queue::operator=(queue&& other);
```

### Member Functions: Element Access

#### std::queue::front

Returns reference to the first elem in the queue. This element will be removed during call to `pop()`. Constant complexity.

```cpp
reference std::queue::front();
const_reference std::queue::front() const;
```

#### std::queue::back

Returns reference to the last elem in the queue. This element is the most recently pushed element. Constant complexity.

```cpp
reference std::queue::back();
const_reference std::queue::back() const;
```

### Member Functions: Capacity

#### std::queue::empty

Checks if underlying container has no elements. Same as `_container.empty()`. Complexity is constant.

```cpp
bool std::queue::empty() const;
```

#### std::queue::size

Returns number of elements in underlying container. Same as `_container.size()`. Complexity is constant.

```cpp
size_type std::queue::size() const;
```

### Member Functions: Modifiers

#### std::queue::push

Pushes the given element to the end of the queue. There are two variations of `push`, one that copies the contents of `value` and one that moves `value` using move semantics. Complexity is equal to `container::push_back()`. 

```cpp
void std::queue::push(const value_type& value);
void std::queue::push(value_type&& value);
```

#### std::queue::emplace

Pushes a new element on end of queue, constructing the element in place without a copy or move operation. Will not be covered.

#### std::queue::pop

Removes element from front of the queue. Equivalent to calling `_container.pop_front()`. Complexity is equal to `container::pop_front()`.

```cpp
void std::queue::pop();
```

#### std::queue::swap

Exchanges contents of container adapter with those of `other`. Uses `std::swap`. Complexity is same as underlyng container, which is typically constant.

```cpp
void std::queue::swap(queue& other) noexcept;
```

### Non-Member Functions: swap

#### std::swap

Specializes `std::swap` algorithm for `std::queue`. Swaps contents of `lhs` and `rhs`. Complexity is same as underlying container. No exceptions as of C++17.

```cpp
template<class T, class Container> void swap( queue<T, Container>& lhs, queue<T, Container>& rhs ) noexcept;

```

### Non-Member Functions: Relational Operators

#### std::queue::operator ==, !=, <, >, <=, >=

Compares the underlying containers' contents of the two container adaptors. The container's operator is used to do the comparison. Complexity is linear in size of the container. Returns true if comparison is true, else false.

```cpp
template<class T, class Container> bool operator==(const queue<T, Container>& lhs, const queue<T, Container>& rhs) const;

template<class T, class Container> bool operator!=(const queue<T, Container>& lhs, const queue<T, Container>& rhs) const;

template<class T, class Container> bool operator<(const queue<T, Container>& lhs, const queue<T, Container>& rhs) const;

template<class T, class Container> bool operator>(const queue<T, Container>& lhs, const queue<T, Container>& rhs) const;

template<class T, class Container> bool operator<=(const queue<T, Container>& lhs, const queue<T, Container>& rhs) const;

template<class T, class Container> bool operator>=(const queue<T, Container>& lhs, const queue<T, Container>& rhs) const;
```