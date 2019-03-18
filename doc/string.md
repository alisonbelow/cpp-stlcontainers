## String

The std::string is not actually a container. It is a member of the `<string>` or Strings library.  

`std::string` is actually a templated instantiation of `std::basic_string<char>`.  

### Member Functions

#### Constructor

(1) Default Constructor: empty, initializes with length 0

```cpp
explicit std::string( const Allocator& alloc ) noexcept;
```

(2) Copy Constructor: Constructs with copy of `str`

```cpp
std::string( const std::string& other );
```

(3) Move Constructor: Constructs by moving `other`

```cpp
std::string( std::string&& other ) noexcept;
```

(4) Substring Constructor: Copies portion of `other` that begins at character position `pos` and spans `len` characters (or until end of `other`)

```cpp
std::string( const std::string& other, size_t pos, size_t count = npos );
```

(5) Range Constructor: Copies sequence of characters in range [`first`, `last`)

```cpp
template class <InputIter> std::string(InputIter first, InputIter last );
```

(6) c-str Constructor: Copies the null-terminated character sequence pointed by `s`

```cpp
std::string( const char* s );
```

(7) Buffer Constructor: Copies the first `count` characters from the array of chars pointed by `s`

```cpp
std::string( const char* s, size_t count );
```

(8) Fill Constructor: Fills string with `count` consecutive copies of character `ch`

```cpp
std::string( size_t count, char ch );
```

(9) Initializer List Constructor: Copies each of the characters in initList, in the same order

```cpp
std::string( std::initializer_list<char> initList );
```

#### Destructor

```cpp
std::string~string() noexcept
```

Destroys string object, deallocated the storage capacity, invalidates pointers/references

#### std::string::operator=  

There are 5 types of assignment that a std::string handles. In all variations, a new value is assigned to the string, replacing its current contents. Complexity is generally linear in new string length.

```cpp
// (1) Copy assignment, complexity linear in size of str
std::string& operator=(const std::string& str)

// (2) Move assignment, complexity linear in size of this
std::string& operator=(std::string&& str) noexcept

// (3) c-str assignment, complexity linear in size of s
std::string& operator=(const char* s)

// (4) Character assignment, complexity constant
std::string& operator=(char ch)

// (5) Initializer list assignment, complexity linear in size of initList
std::string& operator=(std::initializer_list<char> initList)
```

#### std::vector::assign

There are 8 variations of the move function for std::string. In each, a new value is assigned to the string, replacing its current contents

```cpp
// (1) String/Copy assig, complexity linear in size of str
std::string& assign(const std::string& str)

// (2) Substring assign, complexity linear in size of str
// Replaces contents with substring [pos, pos+count]
// If substring lasts past end of string or if count == npos, substring = [pos, str.size()).
// If pos > str.size(), std::out_of_range exception thrown
std::string& assign(const std::string& str, size_t pos, size_t len = npos)

// (3) c-str assign, complexity linear in size of s
std::string& assign(const char* s)

// (4) Buffer assign, complexity linear in count, replaces contents with [s, s+count)
std::string& assign(const char* s, size_t count)

// (5) Fill assign, complexity linear in count, fills with count copies of ch
std::string& assign(size_t count, char ch)

// (6) Range assign, complexity linear in distance between first and last
template <class InputIter> std::string& assign(InputIter first, InputIter last)

// (7) Initializer list assign, complexity linear in size of initList
std::string& assign( std::initialize_list<char> initList)

// (8) Move assign, complexity constant
std::string& assign(std::string&& str) noexcept
```

### Member Functions: Element Access

#### std::string::at

Returns ref to character at position `pos`, bounds checking performed and std::out_of_range exception thrown on invald access. Constant complexity.

```cpp
std::string& at(size_t pos);
const std::string& at(size_t pos) const;
```

#### std::string::operator[]

Returns ref to character at position `pos`. No bounds checking performed. Undefined behaviors if `pos > size()`. Constant complexity.

```cpp
std::string& operator[](size_t pos);
const std::string& operator[](size_t pos) const;
```

#### std::string::front

Returns ref to first char in string. Behavior undefined if `empty() == true`. Constant complexity. Equivalent to `operator[](0)`.

```cpp
char& front();
const char& front() const;
```

#### std::string::back

Returns ref to last char in string. Behavior undefined if `empty() == true`. Constant complexity. Equivalent to `operator[](size() - 1)`.

```cpp
char& back();
const char& back() const;
```

#### std::string::data

Returns pointer to underlying array serving as character storage. `data()` and `c_str()` perofrms the same function and reuturn a null-terminated array. If `empty() == true`, a pointer to a null character is returned. Constant complexity.

```cpp
const char* data() const noexcept;
char* data();   // since C++17
```

#### std::string::c_str

Returns pointer to null-terminated character array with data equivalent to those stored in string. Constant complexity.

```cpp
const char* c_str() const;
```

### Member Functions: Iterators

#### std::string::begin, cbegin, rbegin, crbegin

Returns iterator to the first character of the string. `cbegin` and `crbegin` are always constant.  

`rbegin` and `crbegin` return a reverse iterator the first character of the reversed string, AKA last character of the non-reversed string.  

Complexity is constant.  

#### std::string::end, cend, rend, crend

Returns iterator to the character following the last character of the string. `cend` and `crend` are always constant.  

`rend` and `crend` return a reverse iterator to the character following the last character of the reversed string, AKA the character preceding the first character of the non-reversed string.  

Complexity is constant.  

### Member Functions: Capacity

#### std::string::empty

Checks if string has no characters, if `begin() == end()` or if length is 0. Complexity is constant

```cpp
bool empty() const;
```

#### std::string::size, length

Returns number of char elems in string. Constant complexity

```cpp
size_t size() const noexcept;
size_t length() const noexcept;
```

#### std::string::max_size

Returns max number of elems string can hold due to system/library implementations

```cpp
size_t max_size() const;
```

#### std::string::reserve

Modifies capacity according to rules:

1. If `new_cap > capacity()`, new storage allocated, `capacity()` set >= `new_cap`
2. Until C++20: If `new_cap < capacity()`, non-binding shrink request; if `new_cap < size()`, non-binding `shrink_to_fit()` request
    Since C++20: If `new_cap < capacity()`, no effect

All iterators and references invalidated. Throws std::length_error if `new_cap > max_size()`. Complexity at most linear in size() of string.

```cpp
void reserve(size_t new_cap = 0);   // default arg removed C++20
```

#### std::string::capacity

Returns number of chars that the string has allocated space for

```cpp
size_t capacity() const noexcept;
```

#### std::string::shrink_to_fit

Requests removal of unused capacity. Non-binding to reduce `capacity()` to `size()`. Complexity linear in size of string. Invalidates pointers, references, iterators.

```cpp
void shrink_to_fit();
```

### Member Functions: Operations

#### std::string::clear

Removes all chars from string. Equivalent to `erase(begin(), end()`. Complexity linear in size of string. Invalidates pointers, references, iterators.

```cpp
void clear() noexcept;
```

#### std::string::insert

There are 8 variations of the std::string insert function, similar to `assign` function except have single character type instead of move type. Complexity generally up to linear in new string length. Iterators, pointers, refs may be invalidated. std::out_of_range exception can be thrown if `index > size()` or if `index_str > str.size()`

```cpp
// (1) Fill insert, inserts count copies of ch at position pos
iterator insert(const_iterator pos, size_t count, char ch)

// (2) C-str insert, inserts copy of the string formed by null-terminated char sequence pointed by s at position index
std::string& insert(size_t index, const char* s)

// (3) Substring insert, inserts string (str.substr(index_str, count) at position index
std::string& insert(size_t index, const std::string& str, size_t index_str, size_t count = npos)

// (4) String insert, inserts str at index
std::string& insert(size_t index, const std::string& str)

// (5) Buffer insert, inserts copy of chars in range [s, s+count) at index.  
std::string& insert(size_t index, const char* s, size_t count)

// (6) Range insert, inserts copy of sequence of chars in range [first, last) before pos
template <class InputIter> std::string& insert(const_iterator pos, InputIter first, InputIter last)

// (7) Initializer list insert, inserts copy of each chars in il, in same order before pos
std::string& insert(const_iterator pos, std::initializer_list<char> initList)

// (8) Single char index, inserts character ch before character pointed to by pos
std::string& insert(const_iterator pos, char ch)
```

#### std::string::erase

Remove specified characters from string.

(1) `std::string& erase(size_t index = 0, size_t count = npos);`
Removed min(count, size() - index) characters starting at index. Returns `*this`. Throws std::out_of_range exception if `index > size()`.

(2) `iterator erase(const_iterator pos)`. Removes char at `pos`. Returns iterator pointing to character immediately following character erased, or `end()` if no char exists. No exception thrown.

(3) `iterator erase(const_iterator first, const_iterator last)`. Removes characters in range [first, last). Iterator pointing to character `last` pointed to before the erase, or `end()` if no such char exists. No exception thrown.

#### std::string::push_back

Appends `ch` to end of string. Constant complexity.

```cpp
void push_back(char ch);
```

#### std::string::pop_back

Removes last character from string. Equivalent to `erase(end() - 1)`. Undefined if string is empty. Constant complexity.

```cpp
void pop_back();
```

#### std::string::append

9 variations of append. Extends string by appending additional character(s) at the end of current string.

```cpp
// (1) String append
std::string& append(const std::string& str)

// (2) Substring append, appends substring [pos, pos+count). If requested substring lasts past end of string, or if count == npos, appends [pos, size()). If pos > str.size(), std::out_of_range thrown
std::string& append(const std::string& str, size_t pos, size_t count = npos)

// (3) c-str append, appends null-terminate char string pointed to by s
std::string& append(const char* s)

// (4) Buffer append, appends chars in range [s, s+count)
std::string& append(const char* s, size_t count)

// (5) Fill append, appends ocunt copies of character ch
std::string& append(size_t count, char ch)

// (6) Range append, appends char in range [first, last)
template <class InputIter> std::string& append(InputIter first, InputIter last)

// (7) Initializer list append, appends chars from initializer list initList
std::string& append(std::initializer_list<char> initList)

// (8) Converts t to string view, then appends chars from sv.
template <class T> std::string& append(const T& t);

// (9) .. see above
template <class T> std::string& append(const T& t, size_t pos, size_t count = npos);
```

#### std::string::operator +=

Similar to append. Append additional characters to the string.

```cpp
// (1) Appends string str, complexity linear in size of str
std::string& operator+=(const std::string& str)

// (2) Appends c-str pointed to by s, complexity linear in size of s
std::string& operator+=(const char* s)

// (3) Appends char ch, constant complexity
std::string& operator+=(char ch)

// (4) Appends initializer list initList, complexity linear of size of initList
std::string& operator+=(std::initializer_list<char> initList)

// (5) Converts t to string view sv, then appends character in the string sv as if by append(sv)
template <class T> std::string& operator +=(const T& t)
```

#### std::string::replace

9 variations of std::string::replace in which part of the string indicated (either [pos, pos + count) or [first, last)) is replaced with new string.  

```cpp
// (1) String replace with str
std::string& replace(size_t pos, size_t count, const std::string& str)
std::string& replace(const_iterator first, const_iterator last, const std::string& str);

// (2) Substring replace, replaces with substring [pos2, pos2+count2). If requested substring lasts past end of string, or if count2 == npos, replaces [pos2, size()). If pos > str.size()/length(), std::out_of_range thrown
std::string& replace(size_t pos, size_t count, const std::string& str, size_t pos2, size_t count2 = npos)

// (3) c-str replace, replaces with null-terminate char string pointed to by s
std::string& replace(size_t pos, size_t count, const char* s)

// (4) Buffer replace, replaces with null-terminate char string pointed to by s in range [s, s+count2]
std::string& replace(size_t pos, size_t count, const char* s, size_t count2)
std::string& replace(const_iterator first, const_iterator last, const char* s, size_t count2)

// (5) Fill replace, replaces with count2 copies of character ch
std::string& replace(size_t pos, size_t count, size_t count2, char ch)
std::string& replace(const_iterator first, const_iterator last, size_t count2, char ch)

// (6) Range replace, replaces with char in range [first2, last2)
template <class InputIter> std::string& replace(const_iterator first, const_iterator last, InputIter first2, InputIter last2)

// (7) Initializer list replace, replaces with chars from initializer list initList
std::string& replace(const_iterator first, const_iterator last, std::initializer_list<char> initList)

// (8) Converts t to string view, then replaces chars from sv.
template <class T> std::string& replace(size_t pos, size_t count, const T& t);
template <class T> std::string& replace(const_iterator first, const_iterator last, const T& t);

// (9) ... see above ... replaces with [pos2, pos2+count2) or [pos2, sv.size()) if count2 == npos or if extends past sv.size()
template <class T> std::string& replace(size_t pos, size_t count, const T& t, size_t pos2, size_t count2 = npos);
```  

#### std::string::substr
  
Returns a substring [pos, pos+count). If requested substring extends past end of string, or if count == npos, returned substring is [pos, size()). Complexity is linear in count. Throws std::out_of_range if `pos > size()`.

```cpp
std::string substr(size_t pos = 0, size_t count = npos) const;
```

#### std::string::copy

Copies a substrig, [pos, pos+count) to character string s pointed to by dest. If requested substring extends past end of string, or if count == npos, copied substring is [pos, size()). If `pos > size()`, std::out_of_range exception thrown. Complexity is linear in count. Returns number of characters copied

```cpp
size_t copy(char* dest, size_t count, size_t pos = 0) const
```

#### std::string::resize

Resizes string to contain count characters. If current size < count, additional characters appended. If current size > count, string is reduced to first count elems. Complexity linear in size of string. If count > max_size(), std::length_error thrown.

```cpp
void resize(size_t count);    // new chars initialized to char{}()
void resize(size_t count, char ch);   // new chars initialized to ch
```

#### std::string::swap

Exchanges contents of string with those of `other`. All iterators/refs may be invalidated. Constant complexity.

```cpp
void swap(std::string& other) noexcept;
```

### Member Functions: Search

#### std::string::find

Finds first substring equal to given character sequence. Search begins as pos. Position of first character of the found substring, or npos if no such substring is found, is returned.

```cpp
// (1) First first substring equal to str
size_t find(const std::string& str, size_t pos = 0) const noexcept;

// (2) Finds first substring equal to range [s, s+count)
size_t find(const char* s, size_t pos, size_count) const;

// (3) Finds first substring equal to char string pointed to by s
size_t find(const char* s, size_t pos = 0) const;

// (4) Finds first character ch
size_t find(char ch, size_t pos = 0) const noexcept;

// (5) Converts t to stringview sv, finds first substring equal to sv
template <class T> size_t find(const T& t, size_t pos = 0) const noexcept;
```

Some rules:

- A substring can only be found if `pos < size() - str-.size()`
- An empty substring is found as pos only if `pos <= size()`
- For a non-empty substring, if `pos >= size()`, function always returns npos

#### std::string::rfind

See same variations above for `rfind`, similar to `find`. Finds the last substring equal to the given character sequence. Search begins at pos. Returns position of the first character of the found substring or npos if no such substring found

```cpp
// See find above for syntax/variations
size_t rfind(const std::string& str, size_t pos = npos) const noexcept;
size_t rfind(const char* s, size_t pos, size_t count) const;
size_t rfind(const char* s, size_t pos = npos) const;
size_t rfind(char ch, size_t pos = npos) const noexcept;
template <class T> size_t rfind(const T& t, size_t pos = npos) const noexcept;
```

#### std::string::find_first_of, find_first_not_of, find_last_of, find_last_not_of

Same 5 variations of these function as of `find`.

1. `find_first_of`- finds the first char equal to one of the characters in the given character sequence. Search only considers interval [pos, size()). If character not present, npos is returned. Otherwise, position of found character is returned.

2. `first_first_not_of` - finds first character equal to none of the characters in given char sequence. Search only considers interval [pos, size()).

3. `find_last_of` - finds last character equal to one of characters in given char sequence. Search only considers interval [0, pos].

4. `find_last_not_of` - finds last character equal to none of the characters in given character sequence. Search only considers interval [0, pos].

```cpp
size_t find_*_of(const std::string& str, size_t pos = 0) const noexcept;
size_t find_*_of(const char* s, size_t pos, size_t count) const;
size_t find_*_of(const char* s, size_t pos = 0) const;
size_t find_*_of(char ch, size_t pos = 0) const noexcept;
template<class T> find_*_of(const T& t, size_t pos = 0) const noexcept;
```

### Non-Member Functions

#### std::string::operator +

Concatenation operator. Returns newly constructed string object with its value equal to concatenation of characters in lhs followed by those in rhs.

```cpp
// (1) String concatenation
std::string operator+(const std::string& lhs, const std::string& rhs);

// (1) C-str concatenation
std::string operator+(const std::string& lhs, const char* rhs);
std::string operator+(const char* lhs, const std::string& rhs);

// (3) Character concatenation
std::string operator+(const std::string& lhs, char rhs);
std::string operator+(char lhs, const std::string& rhs);
```

#### std::string::swap NM

Specialized std::swap alg for std::string. Swaps contents of lhs and rhs. Equivalent to `lhs.swap(rhs)`. Constant complexity.

```cpp
void swap(std::string& lhs, std::string& rhs);
```

#### std::string::erase NM

C++ 20, will not cover - TODO?

### Non-Member Functions: Relational Operators

#### std::string::operator ==, !=, <, >, <=, >=

Compares contents of string with another string or null-terminated character array.  Returns true if comparison true, false otherwise. Complexity is linear in size of strings.

### Non-Member Functions: Input/Output

#### std::string::operator <<

Inserts sequence of characters that conforms value of `str` into `os`. Overloads operator `<<`. Complexity linear in length of `str`. 

```cpp
std::ostream& operator<<(std::ostream& os, const std::string& str)
```

#### std::string::operator >>

Extracts string from input stream `is`, storing the sequence in `str`, which is overwritten. Each extracted character is appended to string as if `push_back` used. Overloads operator `>>`. Complexity linear in length of `str`. 

```cpp
std::ostream& operator<<(std::ostream& os, const std::string& str)
```