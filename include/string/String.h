#include "stddef.h"

#include <initializer_list>
#include <iterator>

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
    static const int MAX_STRING_SIZE = 65535;

public:
    using value_type = char;
    using reference = char&;
    using pointer = char*;
    using const_reference = const reference;
    using const_pointer = const pointer;
    using iterator = std::iterator<std::random_access_iterator_tag, char, char, const char*, const char&>;

public:
    // Constructors
    // Default constructor
    explicit String() noexcept : _str(new char[0]), _len(0), _capacity(0) {};

    // Fill constructor
    String(size_t count, char ch) : _str(nullptr), _len(0), _capacity(0)
    {
        reserve(count + 1);
        for (auto index = 0; index < count; ++index)
        {
            _str[index] = ch;
        }
        _len = count;
    }

    // Copy constructor
    String(const String &other) : _str(nullptr), _len(0), _capacity(0)
    {
        reserve(other._capacity);
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
        reserve(initList.size() + 1);
        std::uninitialized_copy(initList.begin(), initList.end(), _str);
        _len = initList.size();
    }

    // C-str constructor
    String(const char *s) : _str(nullptr), _len(0), _capacity(0)
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

    // Buffer constructor
    String(const char *s, size_t count) : _str(nullptr), _len(0), _capacity(0)
    {
        reserve(count + 1);
        auto index = 0;

        while(index < count)
        {
            _str[index] = *(s + index);
            ++index;
        }
        _len = index;      
    }

    // TODO Substring constructor
    // String(const String& other, size_t pos, size_t count = npos): _len(0), _capacity(0) {}

    // TODO Range constructor
    // String(InputI)

    // Destructor
    ~String()
    {
        delete[] _str;
    }

    // Assignment operators
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
        reserve(initList.size() + 1);
        std::uninitialized_copy(initList.begin(), initList.end(), _str);
        _len = initList.size();
    }

    // Assign 
    // TODO ALL, same if not similar to assignment operator above

    // Member Functions: Element Access
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
        return *(_str + size() - 1);
    }

    const_reference back() const
    {
        return *(_str + size() - 1);
    }

    const_pointer data() const noexcept
    {
        return _str;
    }

    const_pointer c_str() const
    {
        return _str;
    }

    // Member Functions: Iterators
    // TODO

    // Member Functions: Capacity
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

    // Member Functions: Operations

    // Member Functions: Search

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

    // Non-Member Functions: Input/Output

private:
    char *_str;
    size_t _len;
    size_t _capacity;
};

} // namespace stlcontainer