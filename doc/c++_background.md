
## C++ Background

### Terminology

**Shallow copy** only copies a pointer so that each pointer referes to the same object  
**Deep copy** copied what the original pointer points to so that the two pointers refer to two distinct objects.  
**Primitive types**  are data types are built-in or predefined data types and can be used directly by the user to declare variables. Example: int, char, float, bool, etc.

### const

There are five locations for const to appear:  
(1) after decl -> won't modify anything that belongs to class
`size_t size() const`  

(2) Before return in function - whatever we are returning cannot be modified  
`const T* front()`  

(3) Before param in function - function cannot modify  
`void print_me(const std::string s)`  

(4) Constant pointer to (constant) value  
(5) (Constant) pointer to constant value

### explicit

Will not allow any conversions or casting. This keyword specifies that a constructor or conversion function is explicit - it cannot be used for implicit conversions and copy-initialization.

### noexcept

Guarantees no exceptions will be thrown. Faster to compile.

### size_t

It is preferable to use `size_t` instead of an `unsigned int`. The extra bit that is used to declare sign in the `unsigned int` data structure can instead be used to double the size limit of the number itself (32 to 64 bit).

### Casting

Syntax: `*_cast<new_type>(obj)`

There are four types of casting supported by C++:  

1. **static_cast** - should be used for "well-behaved" or expected conversions. `static_cast` performs conversions between pointers to related classes, not only upcasts (from pointer-to-derived to pointer-to-base), but also downcasts (from pointer-to-base to pointer-to-derived). No checks are performed during runtime to guarantee that the object being converted is a full object of the destination type. It is therefore up to the programmer to ensure this conversion is valid.

    Casting also includes:  
    - Convert from void* to any pointer type. In this case, it guarantees that if the void* value was obtained by converting from that same pointer type, the resulting pointer value is the same.
    - Convert integers, floating-point values and enum types to enum types and reverse
    - Explicitly call a single-argument constructor or a conversion operator.
    - Convert to rvalue references.
    - Convert any type to void, evaluating and discarding the value.
2. **const_cast** - toggles the `const` of the object pointed to by a pointer. Note removing the constness of an object to write to it results in undefined behavior.  
3. **dynamic_cast** - used for upcasting and type-safe downcasting. (Downcasting is converting from base class to derived.) `dynamic_cast` can only be used with pointers and references to classes (or with void*).

    ```
    "The need for dynamic_cast generally arises because we want perform derived class operation on a derived class object, but we have only a pointer-or reference-to-base." 
    - Scott Meyers
    ```

    When a `dynamic_cast` of a pointer will fail (not a complete object of the destination class), the cast will return a null pointer. An incomplete `dynamic_cast` for a reference type will throw a *bad_Cast* exception. 

    Casting also includes:
    - casting null pointers between pointers types (even between unrelated classes)
    - casting any pointer of any type to a void* pointer.

4. **reinterpret_cast** - converts any pointer type to any other pointer type. Classes do not have to be related for conversion. All pointer conversions are allowed: neither the content pointed nor the pointer type itself is checked. It can also cast pointers to or from integer types. The format in which this integer value represents a pointer is platform-specific. The casting can be reversed (integer casted to valid pointer) if the integer type is large enough to fully contain the pointer.

### Pass-by-value vs Pass-by-reference

**Pass-By-Value:**  

- Create copy of parameter
- Send to function, local variables are copies of original arguments passed in
- Changes made in function do not affect originals

Should *not* pass-by-value if large data structure. Pass-by-value makes sense with primitive types.  

**Pass-By-Reference**

- Local parameters are references to storage locations of original arguments passed in
- Changes to these variables in the function will affect the orginals
- No copy is made, overhead of time and storage with pass-by-value is saved

Passing in a constant reference is often used as syntax for function arguments because there is no overhead in making a copy **and** the guarantee is made that the original data structure will not be affected.

### Copy vs Move Constructor

**Copy Constructor**  
Copy constructors of class T have the syntax: `T::T(const T& other)`. The argument is often const so that it is not modified.  

Copy constructors create a new object of the same class as the input arugment using the existing object. A copy of the existing object is created member to member.  

Copy constructors are called whenever an object is initialized from another object of the same type, including:  

1. Initialization like `T b; T a = b;` or `T a(b);` (when object is constructed based on another object of the same class)
2. Function argument passing such as `T a; f(a);`
3. When an object of class is returned by value such as `return a;`, and a has no move constructor

A copy constructor **must** be defined if a class has pointer class variables and/or dynamic memory allocations (e.g. using the word `new` to define a pointer data member). The compiler defined copy constructor does not handle these dynamic allocations, and cannot make deep copies.  

If a copy constructor is not user-defined (or if a user-defined copy constructor is not defaulted), the C++ compiler creates an implicitly-declared default copy constructor as a non-explicit inline public member of the class. Even if the user declared multiple copy constructors, the implicitly-declared copy constructor can be forced with the keyword `default`. The compiler declared copy constructor will be declared in the form `T::T(const T&)` if all each direct and virtual base of T have copy constructors with const params and each non-static data member M of class T have copy constructors with const params. Else, the implicitly-declared copy constructor is in form `T::T(T&)`.

An implicitly-declared copy constructor is undefined (until *C++11*) and defined as deleted (after *C++11*) if (any):

- T has non-static data members that cannot be copied
- T has direct/virtual base class that cannot be copied or that has a deleted/inaccessible destructor.  
Since *C++11*:
- T is union-like and has variant member with non-trivial copy constructor
- T has a data member with rvalue reference type
- T has a user defined move constructor/move assignment constructor operator (implicitly-declared copy constructor is deleted not defaulted in this case)

Trivial copy constructors occur when (all):

- Copy constructor is not user-provided (is defaulted or implicitly-defined)
- T has no virtual member functions and no base classes
- All direct base class copy constructors are trivial
- Copy constructor for every non-static class type member of T is trivial

In this scenario, the trivial copy constructor copies every scalar sub-object (recursively).

An implicitly defined copy constructor copies the object representation as if by std::memmove, if class is union type, and if not, performs a full member-wise copy (shallow copy) of the object's bases and non-static members using direct initialization. This implicit definition **does not** occur if T has a user-defined destructor or user-defined copy-assignment operator (since *C++11*).

**Move Constructor**  
Move constructors of class T have the syntax: `T::T(T&& other)`. Move constructors accept a rvalue reference as a parameter.  

Move constructors are called when an object is initialized from rvalue of the same type (xvalue *C++17*), including:  

1. Initialization `T b; T a = std::move(b);` OR `T a(std::move(b));`  
2. Function argument passing such as `f(std::move(a));`  
3. Function return, `return a;` where a is type T and T has a move constructor  

Move constructors "steal" the resources held by the argument (pointers, IO streams, running threads, etc.) instead of make copies of them. This leaves the argument in a valid yet indeterminate state. Move semantics in C++ are exactly this, the object is not *moved* from one place to another, but the source's internals are modified, made empty. Therefore, move constructor rvalue arguments should not be const, as the purpose is, in fact, to modify the other object.  

An implicitly-declared move constructor is created by a compiler is all the following is true, no user-declared copy constructors, copy assignment operators, move assignment operators, destructors and (since *C++11*) the implicitly-declared move constructor is not defined as deleted. The compiler creates the move constructor in the form non-explicit inline public member with syntax `T::T(T&&)`. Similarly to the implicitly-declared copy constructor, a class can have multiple move constructors, and can force the implicitly-declared move constructor with the keyword `default`.  

An implicitly-declared copy constructor is defined as deleted if (any):

- T has non-static data member OR direct/virtal base class that cannot be moved 
- T has a direct or virtual base class with a deleted/inaccessible destructor
- T is union-like and has variant member with non-trivial move constructor
- Deleted implicitly declared move constructor is ignored by overload resolution (since *C++14*)  

Trivial move constructors occur when (all):

- Move constructor is not user-provided (implicitly-defined or defaulted)
- No virtual member functions and base classes
- Move constructor selected for every direct base or non-static class type member of T is trivial
- T has no non-static data members of volatile type (since *C++14*)

Trivial move constructors performs the same action as a trivial copy constructor, meaning it makes a copy of the object representation as if by std::memmove.

An implicitly defined move constructor copies the object representation as if by std::memmove, if class is union type, else a full member-wise move of the object's bases and non-static members is done using direct initialization.

Move constructors that are user-defined **SHOULD NOT** throw exceptions.

**Both**  
If both copy and move constructors are provided and no other constructors are viable, overload resolution selects move constructor IF the argument is an rvalue of the same type, and selects copy constructor if the argument is an lvalue.  

If only the copy constructor is provided, all argument categories select it (as long as it takes a reference to const, since rvalues can bind to const references), which makes copying the fallback for moving, when moving is unavailable.  

### Copy vs Move Assignment Operator

**Copy Assignment**  
Syntax: `T& T::operator=(T& other)` or `T& T::operator=(const T& other)`

The copy assignment operator is often known just as the assignment operator, where both RHS and LHS of assignment have the same class type. A default version of this is enerated by the compiler if not declared, which does a memberwise copy of each member copied by its own copy assignment operator. The copy assignment operator must clean up the data members of the assignment's target (deal with old target internals), unlike the copy constructor where values are assigned to uninitialized data members.

When a user overloads the copy assignment operator, it is often to do deep copies of class objects.  

A copy assignment operator performs 3 logical steps:

1. Acquire new resources
2. Release old resources that this currently owns
3. Assign new resources' handles to the objects

**Move Assignment**  
Syntax: `T& T::operator=(T&& other)`

The move assignment operator differs from the move constructor in that the move assignment operator is called on an existing object.  

A move assignment operator performs 4 logical steps:

1. Release any resources that this currently owns (`delete ...`)
2. Pilfer other's resources
3. Set other to a default state
4. Return *this

**Both**    
Similar to copy/move constructor, copy assignment is the fallback for move assignment. If both assignment operators are provided overload resolution selects move assignment if the argument is an rvalue and selects copy assignment if the argument is an lvalue.

### Rule of Three and Rule of Five

Until C++11 Rule of Three:  
If a class defines 1+ of the following it should explicitly define all three: destructor, copy constructor, copy assignment operator. If Resource Acquisition Is Initialization (RAII), such as using smart pointers, the destructor may be left undefined.

After C++11 the Rule of Three becomes the Rule of Five, with the advent of move semantics. Now if 1+ of destructor, copy constructor, copy assignment operator, move constructor, move assignment operator are defined, the others should be explicitly defined as well. If only a destructor needs to be explicitly defined, the other 4 can be defaulted.  

### rvalue vs lvalue

If an object is constructed or an assignment is done where the argument is an lvalue, it is reasonable to copy the lvalue. The assumption is that it is not safe to alter the lvalue, because it may be used again later in the program.  

If an object is constructed or an assignment is done where the argument is an rvalue, then that rvalue is assumed to be just a temporary object of some kind. Instead of copying it (which can be expensive), its resources are simply transferred, or moved, (which is cheap) to the object that is being constructed or assigned.

In concept, rvalues correspond to temporary objects returned from functions, while lvalues correspond to objects you can refer to. A heuristic for this dilineation can be if you can take its address, typically it is an lvalue. An address itself, in C++ nomanclature, is an rvalue as you cannot modify or assign to an address.

Example:  
Right: `v.push_back(10);`  
Left: `a = 10; push_back(a);`  

Generally:  
rvalue = anything that can put on the RHS of an equals sign/assignment operator  
lvalue = anything that can put on the LHS of an equals sign/assignment operator  

In a function call, the distinction between parameters and arguments is that parameters are lvalues, but the arguments with which they are initialized may be  rvalues or lvalues. 

### References

https://en.cppreference.com/w/cpp/language/move_constructor  
https://en.cppreference.com/w/cpp/language/copy_constructor  
https://www.tutorialcup.com/cplusplus/copy-constructor.htm  
https://en.cppreference.com/w/cpp/language/copy_assignment  
https://en.cppreference.com/w/cpp/language/move_assignment  
https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)  
https://en.wikipedia.org/wiki/Move_assignment_operator  
https://en.wikipedia.org/wiki/Copy_assignment_operator  
https://smartbear.com/blog/develop/c11-tutorial-introducing-the-move-constructor-and/  
https://www.cs.fsu.edu/~myers/c++/notes/references.html  
http://www.cplusplus.com/doc/tutorial/typecasting/
https://www.bogotobogo.com/cplusplus/upcasting_downcasting.php