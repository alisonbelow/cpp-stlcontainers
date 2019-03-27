#include "stddef.h"

#include <initializer_list>
#include <iterator>
#include <iostream>

namespace stlcontainer
{

size_t cstr_len(const char* s)
{
    size_t length = 0;
    while (*s++)
    {
        ++length;
    }
    return length;
}

class String
{
    static const int INITIAL_CAPACITY = 15;
    static const int MAX_STRING_SIZE = 65535;
    static const size_t npos = -1;
public:
    using value_type = char;
    using reference = char&;
    using pointer = char*;
    using const_reference = const reference;
    using const_pointer = const pointer;
    using iterator = std::iterator<std::random_access_iterator_tag, char, char, const char*, const char&>;

public:
    // Member Functions: Constructors -----------------------------------------
    // Default constructor
    explicit String() noexcept : _str(new char[0]), _len(0), _capacity(0) 
    {
        reserve(INITIAL_CAPACITY);
    };

    // Fill constructor
    String(size_t count, char ch) : _str(nullptr), _len(0), _capacity(0)
    {
        reserve(count > INITIAL_CAPACITY ? count : INITIAL_CAPACITY);
        for (auto index = 0; index < count; ++index)
        {
            _str[index] = ch;
        }
        _len = count;
    }

    // Copy constructor
    String(const String &other) : _str(nullptr), _len(0), _capacity(0)
    {
        reserve(other._capacity > INITIAL_CAPACITY ? other._capacity : INITIAL_CAPACITY);
        for (auto index = 0; index != other._capacity; ++index)
        {
            _str[index] = other._str[index];
        }
        _len = other._len;
    }

    // Move constructor
    String(String &&other) : _len(std::move(other._len)), _capacity(std::move(other._capacity)), _str(std::move(other._str))
    {
        other._str = nullptr;
        other._len = 0;
        other._capacity = 0;
    }

    // Initializer List constructor
    String(std::initializer_list<char> initList) : _str(nullptr), _len(0), _capacity(0)
    {
        reserve(initList.size() > INITIAL_CAPACITY ? initList.size() : INITIAL_CAPACITY);
        std::uninitialized_copy(initList.begin(), initList.end(), _str);
        _len = initList.size();
    }

    // C-str constructor
    String(const char *s) : _str(nullptr), _len(0), _capacity(0)
    {
        reserve(cstr_len(s) > INITIAL_CAPACITY ? cstr_len(s) : INITIAL_CAPACITY);
        auto index = 0;
        while (*s)
        {
            _str[index] = *s;
            ++index;
            ++s;
        }

        // Include null-terminated character
        _str[index] = *s;

        _len = index;
    }

    // Buffer constructor
    String(const char *s, size_t count) : _str(nullptr), _len(0), _capacity(0)
    {
        reserve(count > INITIAL_CAPACITY ? count : INITIAL_CAPACITY);
        auto index = 0;
        while(index < count)
        {
            _str[index] = *(s + index);
            ++index;
        }
        _len = index;      
    }

    // Substring constructor
    String(const String& other, size_t pos, size_t count = npos) : _str(nullptr), _len(0), _capacity(0)
    {
        if (count == stlcontainer::String::npos || (count - pos) >= other.size()) {
            count = other.size() - pos;
        }

        reserve(count > INITIAL_CAPACITY ? count : INITIAL_CAPACITY);
        auto s = other.data() + pos;
        size_t index = 0;
        while (index < count)
        {
            _str[index++] = *s;
            ++s;
        }
        _len = index;
    }

    // TODO Range constructor

    // Destructor
    ~String()
    {
        delete[] _str;
    }

    // Member Functions: Assignment Operator and assign -----------------------
    // Copy assignment
    String& operator= (const String& other)
    {
        if (this != &other)
        {
            reserve(other._capacity);
            for (auto index = 0; index != other.size(); ++index)
            {
                _str[index] = other._str[index];
            }
            _len = other._len;
        }
        return *this;
    }

    // Move assignment
    String& operator= (String&& other)
    {
        if (this != &other)
        {
            delete[] _str;
            _str = other._str;
            _len = other._len;
            _capacity = other._capacity;

            other._str = nullptr;
            other._len = 0;
            other._capacity = 0;
        }
        return *this;
    }

    // C-str assignment
    String& operator= (const char* s)
    {
        if (s != _str)
        {
            reserve(cstr_len(s));
            
            auto index = 0;
            while (*s)
            {
                _str[index] = *s;
                ++index;
                ++s;
            }
            // Include null-terminated character
            _str[index] = *s;

            _len = index;
        }
    }

    // Char assignment
    String& operator= (const char ch)
    {
        reserve(1);
        *_str = ch;
        _len = 1;
    }

    // Init list assignment
    String& operator= (std::initializer_list<char> initList)
    {
        reserve(initList.size());
        std::uninitialized_copy(initList.begin(), initList.end(), _str);
        _len = initList.size();
    }

    // String assign
    String& assign(const String& str) 
    {
        *this = str;
    }

    // Substring assign
    String& assign(const String& str, size_t pos, size_t count = stlcontainer::String::npos) 
    {
        if (count == stlcontainer::String::npos || (count - pos) >= str.size()) {
            count = str.size() - pos;
        }

        reserve(count);
        auto s = str.data() + pos;
        size_t index = 0;
        while (index < count)
        {
            _str[index++] = *s;
            ++s;
        }
        _len = index;
    }

    // C-str assign
    String& assign(const char* s) 
    {
        *this = s;
    }

    // Buffer assign
    String& assign(const char* s, size_t count) 
    {
        reserve(count);
        auto index = 0;
        while (index < count)
        {
            _str[index++] = *s;
            ++s;
        }
        _len = index;
    }
    
    // Fill assign
    String& assign(size_t count, char ch) 
    {
        reserve(count);
        auto index = 0;
        while (index < count)
        {
            _str[index++] = ch;
        }
        _len = index;
    }
    
    // Initializer list assign
    String& assign(std::initializer_list<char> initList) 
    {
        *this = initList;
    }

    // TODO Range assign
    // TODO string view assign

    // Member Functions: Element Access ---------------------------------------
    reference at(size_t pos)
    {
        if (pos >= size() || pos < 0)
        {
            throw std::out_of_range("Operator stlcontainer::String::at()");
        }
        return _str[pos];
    }

    const_reference at(size_t pos) const
    {
        if (pos >= size() || pos < 0)
        {
            throw std::out_of_range("Operator stlcontainer::String::at()");
        }
        return _str[pos];
    }

    reference operator[](size_t pos)
    {
        return _str[pos];
    }

    const_reference operator[](size_t pos) const
    {
        return _str[pos];
    }

    reference front()
    {
        return *_str;
    }

    const_reference front() const
    {
        return *_str;
    }

    reference back()
    {
        return *(_str + _len - 1);
    }

    const_reference back() const
    {
        return *(_str + _len - 1);
    }

    const_pointer data() const noexcept
    {
        return _str;
    }

    const_pointer c_str() const
    {
        return _str;
    }

    // Member Functions: Iterators --------------------------------------------
    // TODO

    // Member Functions: Capacity ---------------------------------------------
    bool empty() const
    {
        return (size() == 0);
    }

    size_t size() const noexcept
    {
        return _len;
    }

    size_t length() const noexcept
    {
        return _len;
    }

    size_t capacity() const noexcept
    {
        return _capacity;
    }

    void reserve(size_t new_cap = 0)
    {
        if (new_cap > MAX_STRING_SIZE)
        {
            throw std::length_error("Operation stlcontainer::Vector::reserve()");
        }

        if (new_cap <= capacity())
        {
            return;
        }

        char *new_elem = new char[new_cap];
        if (size())
        {
            for (size_t index = 0; index != size(); ++index)
            {
                new_elem[index] = _str[index];
            }
            delete[] _str;
        }

        _capacity = new_cap;
        _str = new_elem;
    }

    void shrink_to_fit()
    {
        if (size() == capacity())
        {
            return;
        }

        // Cannot use reserve because reserve checks if new capacity < current capacity, then no action
        _capacity = _len;     
    }

    // Member Functions: Operations
    void clear() noexcept 
    {
        delete[] _str;
        _str = nullptr;
        _len = 0;
    }

    // TODO Iterator insert
    // C-str insert
    String& insert(size_t index, const char* s) 
    {
        auto origSize = size();
        auto sLength = cstr_len(s);

        // Save remainder of string, if any
        String remainderStr;
        if (index < origSize) {
            remainderStr.assign(c_str() + sLength);
        }
        reserve(origSize + sLength);

        size_t position = 0;
        while (position < sLength)
        {
            _str[index + position] = *(s + position);
            ++position;
        }

        while ((position - sLength) < remainderStr.size())
            {
                _str[index + position] = remainderStr[position - sLength];
                ++position;
            }
        
        _len = origSize + sLength;
        return *this;
    }
    
    // Substring insert
    String& insert(size_t index, const String& str, size_t index_str, size_t count = stlcontainer::String::npos) {}
    // String insert
    String& insert(size_t index, const String& str) {}
    // Buffer insert
    String& insert(size_t index, const char* s, size_t count) {}
    // TODO Range insert
    // TODO Initializer list insert
    // TODO Single char insert

    // TODO npos
    String& erase(size_t index = 0, size_t count = stlcontainer::String::npos) {}
    // TODO erase other types

    void push_back(char ch) 
    {
        if (capacity() < _len + 1) 
        {
            reserve( _len == 0 ? 1 : capacity() * 2);
        }
        _str[_len++] = ch;
    }

    void pop_back() 
    {
        if (!empty())
        {
            --_len;
        }
        ~(_str[_len]);
    }

    // String append
    String& append(const String& str) 
    {
        reserve(capacity() + str.size());
        for (auto index = 0; index < str.size(); ++index)
        {
            _str[index + size()] = str[index];
        }
        _len += str.size();
        return *this;
    }

    // Substring append
    String& append(const String& str, size_t pos, size_t count = stlcontainer::String::npos) 
    {
        if (count == stlcontainer::String::npos || (count - pos) >= str.size()) {
            count = str.size() - pos;
        }

        reserve(count);

        for (auto index = 0; index < count; ++index)
        {
            _str[index + size()] = str[index + pos];
        }
        _len += count;
        return *this;
    }
    
    // C-str append
    String& append(const char* s) 
    {
        size_t count = cstr_len(s);
        reserve(size() + count);
        
        auto index = size();
        while (*s)
        {
            _str[index] = *s;
            ++index;
            ++s;
        }

        _len = index;
        return *this;
    }

    // Buffer append
    String& append(const char* s, size_t count) 
    {
        reserve(size() + count);

        auto index = 0;
        while(index < count)
        {
            _str[index + size()] = *(s + index);
            ++index;
        }
        _len += index;
        return *this;
    }

    // Fill append
    String& append(size_t count, char ch) 
    {
        reserve(size() + count);

        auto index = 0;
        while (index < count)
        {
            _str[index++ + size()] = ch;
        }
        _len += index;
        return *this;
    }

    // Initializer list append
    String& append(std::initializer_list<char> initList) 
    {
        reserve(size() + initList.size());
        auto index = 0;
        for (auto elem : initList)
        {
            _str[index++ + size()] = elem;
        }
        _len += index;
        return *this;
    }

    // TODO Range append
    // TODO Stringview append

    // Concatenation equals operator
    String& operator+= (const String& str) 
    {
        (*this).append(str);
        return *this;
    }
    
    // String replace
    String& replace(size_t pos, size_t count, const String& str) 
    {
        if (pos > size()) 
        {
            throw std::out_of_range("stlcontainer::String::replace(size_t pos, size_t count, const stlcontainer::String& str");   
        }

        auto origSize = size();
        auto strSize = str.size();

        // Save remainder of string, if any
        String remainderStr;
        if (pos + count < origSize) {
            remainderStr.assign(c_str() + pos + count);
        }
        
        reserve(origSize + (strSize - count));

        // Replace within string
        size_t index = 0;
        while (index < strSize)
        {
            _str[index + pos] = str[index];
            ++index;
        }

        // Append rest of remaining original string, if any
        if (pos + count < origSize) {
            while ((index - strSize) < remainderStr.size())
            {
                _str[index + pos] = remainderStr[index - strSize];
                ++index;
            }
        }

        _len = origSize - count + strSize;
        return *this;
    }

    // Substring replace
    String& replace(size_t pos, size_t count, const String& str, 
                    size_t pos2, size_t count2 = stlcontainer::String::npos) 
    {
        if (pos > size())
        {
            throw std::out_of_range("stlcontainer::String::replace(size_t pos, size_t count, const stlcontainer::String& str, size_t pos2, size_t count2)");
        }

        if ((pos2 + count2) > str.size() || count2 == stlcontainer::String::npos)
        {
            count2 = str.size();
        }

        auto origSize = size();

        // Save remainder of string, if any
        String remainderStr;
        if (pos + count < origSize) {
            remainderStr.assign(c_str() + pos + count);
        }

        reserve(origSize - count + count2);

        // Replacement
        size_t index = 0;
        _len = pos;
        while (index < count2)
        {
            _str[index + pos] = str[index + pos2];
            ++index;
            ++_len;
        }

        // Append rest of remaining original string, if any
        while ((index - count2) < remainderStr.size())
        {
            _str[index + pos] = remainderStr[index - count2];
            ++index;
            ++_len;
        }

        // _len = origSize - count + count2;
        return *this;       
    }
    
    // C-str replace
    String& replace(size_t pos, size_t count, const char* s) 
    {
        if (pos > size())
        {
            throw std::out_of_range("stlcontainer::String::replace(size_t pos, size_t count, const char* s)");
        }

        auto origSize = size();
        auto sLength = cstr_len(s);

        // Save remainder of string, if any
        String remainderStr;
        if (pos + count < origSize) {
            remainderStr.assign(c_str() + pos + count);
        }
        
        reserve(origSize - count + sLength);

        // Replace within string
        size_t index = 0;
        while (index < sLength)
        {
            _str[index + pos] = *(s + index);
            ++index;
        }

        // Append rest of remaining original string, if any
        if (pos + count < origSize) {
            while ((index - sLength) < remainderStr.size())
            {
                _str[index + pos] = remainderStr[index - sLength];
                ++index;
            }
        }

        _len = origSize - count + sLength;
        return *this;
    }
    
    // Buffer replace
    String& replace(size_t pos, size_t count, const char* s, size_t count2) 
    {
        if (pos > size())
        {
            throw std::out_of_range("stlcontainer::String::replace(size_t pos, size_t count, const char* s, size_t count2)");
        }
        
        auto origSize = size();
        auto sLength = cstr_len(s);
        
        if (count2 > sLength || count2 == stlcontainer::String::npos)
        {
            count2 = sLength;
        }

        // Save remainder of string, if any
        String remainderStr;
        if (pos + count < origSize) {
            remainderStr.assign(c_str() + pos + count);
        }
        reserve(origSize - count + count2);

        // Replacement
        size_t index = 0;
        while (index < count2)
        {
            _str[index + pos] = *(s + index);
            ++index;
        }

        // Append rest of remaining original string, if any
        if (pos + count < origSize) {
            while ((index - count2) < remainderStr.size())
            {
                _str[index + pos] = remainderStr[index - count2];
                ++index;
            }
        }

        _len = origSize - count + count2;
        return *this;    
    }
    
    // Fill replace
    String& replace(size_t pos, size_t count, size_t count2, char ch) 
    {
        if (pos > size())
        {
            throw std::out_of_range("stlcontainer::String::replace(size_t pos, size_t count, size_t count2, char ch");
        }

        auto origSize = size();

        // Save remainder of string, if any
        String remainderStr;
        if (pos + count < origSize) {
            remainderStr.assign(c_str() + pos + count);
        }

        reserve(origSize - count + count2);

        // Replacement
        size_t index = 0;
        while (index < count2)
        {
            _str[index + pos] = ch;
            ++index;
        }

        // Append rest of remaining original string, if any
        if (pos + count < origSize) {
            while ((index - count2) < remainderStr.size())
            {
                _str[index + pos] = remainderStr[index - count2];
                ++index;
            }
        }

        _len = origSize - count + count2;
        return *this;
    }
    
    // TODO Range replace
    // TODO Initializer list replace
    // TODO Stringview replace

    // Substring
    String substr(size_t pos = 0, size_t count = stlcontainer::String::npos) const 
    {
        if (count == stlcontainer::String::npos || (count - pos) >= size()) {
            count = size() - pos;
        } 
        return String(_str, count);
    }

    size_t copy(char* dest, size_t count, size_t pos = 0) const 
    {
        if (pos > size())
        {
            throw std::out_of_range("Operator stlcontainer::String::copy()");
        }
        
        if ((pos + count) > size() || count == stlcontainer::String::npos)
        {
            count = size() - pos;
        }        

        for (auto index = pos; index < count; ++index)
        {
            *dest++ = _str[index];
        }

        return count; 
    }

    void resize(size_t count)
    {
        resize(count, char());
    }

    void resize(size_t count, char ch) 
    {
        if (count == size()) return;

        // Reduce vector to first count elements
        if (count < size())
        {
            for (auto index = size() - 1; index >= count; --index)
            {
                ~(_str[index]);
                --_len;
            }
        }

        // Insert count - size() elements with val value
        if (count > size())
        {
            reserve(count);
            for (auto index = size(); index < count; ++index)
            {
                _str[index] = ch;
                ++_len;
            }
        }
    }

    // Swap
    void swap(String& other) noexcept 
    {
        std::swap(_len, other._len);
        std::swap(_capacity, other._capacity);
        std::swap(_str, other._str);
    }

    // Member Functions: Search
    // Substring find
    size_t find(const String& str, size_t pos = 0) const noexcept {}
    // Range find
    size_t find(const char* s, size_t pos, size_t count) const {}
    // C-str find
    size_t find(const char* s, size_t pos = 0) const {}
    // Char find
    size_t find(char ch, size_t pos = 0) const noexcept {}
    // TODO Stringview find

    // TODO rfind
    // TODO find_*_of variations

    // Non-Member Functions: Concatenation
    String operator+ (const String& rhs) {}
    String operator+ (const char* rhs) {}
    String operator+ (char rhs) {}

    // Non-Member Functions: Relational Operators
    bool operator== (const String& rhs) const
    {
        if (size() != rhs.size())
        {
            return false;
        }

        for(auto index = 0; index < size(); ++index)
        {
            if(_str[index] != rhs._str[index])
            {
                return false;
            }
        }
    }

    bool operator!= (const String& rhs) const
    {
        return !(*this == rhs);
    }

    bool operator<(const String& rhs) const 
    {
        bool matchingElems = true;
        for(auto index = 0; index < std::min(size(), rhs.size()); ++index)
        {
            if(_str[index] > rhs._str[index])
            {
                return false;
            }

            matchingElems &= (_str[index] == rhs._str[index]);
        }

        if (matchingElems) 
        {
            if (rhs.size() < size())
            {
                return false;
            }    
        }
        return true; 
    }

    bool operator> (const String& rhs) const
    {
        return rhs < *this;
    }

    bool operator<= (const String& rhs) const
    {
        return !(rhs < *this);
    }

    bool operator>= (const String& rhs) const
    {
        return !(*this < rhs);
    }

    // Non-Member Functions: Input/Output
    friend std::ostream& operator<<(std::ostream& os, const stlcontainer::String& str)
    {
        os << str.c_str();
        return os;
    }

private:
    char *_str;
    size_t _len;
    size_t _capacity;
};

} // namespace stlcontainer