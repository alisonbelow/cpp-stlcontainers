## Iterators

### Iterator Base Class

Base class template:  

```cpp
template <class Category,              // iterator::iterator_category
          class T,                     // iterator::value_type
          class Distance = ptrdiff_t,  // iterator::difference_type
          class Pointer = T*,          // iterator::pointer
          class Reference = T&         // iterator::reference
          > class iterator;
```

Iterator traits:
Standard algorithms determine certain properties of the iterators passed to them and the range they represent by using the members of the corresponding iterator_traits instantiation. iterator_traits class template shall be defined, with at least the following member types defined:  
(1) `difference_type`:     type expressing result of subtractng one iterator from another  
(2) `value_type`: type of elem iterator points to  
(3) `pointer`: type of pointer to elem that iterator points to  
(4) `reference`: type of ref to elem that iterator points to  
(5) `iterator category`: see below   

### General

Iterators are classified into 5 categories depending on functionality:

Input/Ouput ⊂ Forward ⊆ Bidirectional ⊆ Random-Access 

Specifics:

* Input/output are most limited. Sequential single-pass input or output operations
* Forward ⊇ input. If *not* constant the functionality of output as well. Still limited to one direction. All standard containers support forward iterators
* Bidirectional iterators ⊇ forward iterators but also traverse backwards
* Random-access iterators ⊇ bidirectional iterators, have ability to access ranges non-sequentially. Can apply offset value to iterator which means you *do not* have to iterate through all elements in between. Similar to std ptrs

### Properties

All:  

- Copy-constructible  
    `X b(a);`  
- Copy-assignable   
    `b = a;`  
- Destructible  
    `~X();`  
- Can be incremented  
    `++a; a++`  
    The difference between *pre* (++a) and *post* (a++):   
    - Pre-increment increments the base iterator kept by the object (modified object-in-place)  
      Pre-increment also returns a ref to the object   
    - Post-increment creates copy of the object, increments using pre-fix notation, returns copy.  
      Post-increment returns a const object, semantically defined as previous value  

Input, Output, Forward, Bidirectional, Random Access:

- Supports equality/inequality comparisons    
    `a == b; a != b;`  
- Defreferenceable as an rvalue  
    `*a; a->m;`  

Output, Forward, Bidirectional, Random Access:  

- Dereferenceable as an lvalue  
    `*a = t; *a++=t;`  

Forward, Bidirectional, Random Access:

- Default-constructible  
    `X a; X();`  
- Multi-pass (dereferenceability not affected by dereferencing or incrementing)  
    `{ b=a; *a++; }`  

Bidirectional, Random Access:  

- Can be decremented  
    `--a; a--; *a--;`  
    The difference between *pre* (--a) and *post* (a--) (see above increment):   
    - Pre-decrement decrements the base iterator kept by the object  
    - Post-decrement creates copy of the object, decrements using pre-fix notation, returns copy.

Random Access:  

- Supports arithmetic operators: [+] and [-]  
    `a + b; a - b;`  
- Supports inequality comparisons: [<], [>], [<=], [>=]    
    `a < b; a > b; a <= b; a >= b;`  
- Supports compound assignement operations: [+=] and [-=]  
    `a += n; a -= n;`  
- Supports offset dereference operator: [[]]  
    `a[n]`   

### References

http://znc.es/Addison%20Wesley%20-%20The%20%20C++%20Standard%20Library.%20A%20Tutorial%20and%20Reference.pdf  
https://www.rapidtables.com/math/symbols/Set_Symbols.html  
https://en.cppreference.com/w/cpp/iterator  
https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator  
http://www.cplusplus.com/reference/iterator/  
https://stackoverflow.com/questions/1303899/performance-difference-between-iterator-and-iterator  
http://www.cplusplus.com/reference/iterator/reverse_iterator/operator++/  
https://accu.org/index.php/journals/479  
http://read.pudn.com/downloads70/ebook/250637/STL.Tutorial.and.Reference.Guide/Addison-Wesley%20-%20STL%20Tutorial%20and%20Reference%20Guide.pdf  

<br><br><br>*NOTE all documentation assuming C++ 17 standard*