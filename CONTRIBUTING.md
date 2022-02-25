# Contributing to DragonHeartOS

## Commits

Make sure your commit messages are _only_ written in American English and metric units. Time _must_ be represented in a DD-MM-YYYY format. Use proper spelling, grammar and punctuation.

Please follow the following format for your commit messages:
```
<Component>: <Message>

<Details>
```

Every commit message must have a maximum of 70 columns.

## Coding style

For spaces, parentheses, brace placement etc. all code should follow the format specified in the `.clang-format` file.

Stuff here will definetly change over time, so be aware of that. :^)

### Naming

This project uses a combination of CamelCase and snake_case. CamelCase is used for classes, namespaces, functions and structs. Use snake_case for variables.

###### Do:

```cpp
struct MyStruct;
int my_variable;
class MyClass;
namespace MyNamespace {}
```

###### Don't:

```cpp
struct my_struct;
int myVar;
class my_class;
namespace My_Namespace {}
```

Use full words, except in cases where it would be easier to understand or would just make more sense.

Data members in C++ classes should be private. Static data members should be prefixed using `s_`. Other data members, on the other hand, should be prefixed with `m_`.

Precede setters with the word `Set`. Use bare words for setters. Setter and getter names should match the names of the variables being set/gotten.

###### Do:

```cpp
void SetVariable(int); // Sets m_variable
int Variable() const;  // Returns m_variable
```

###### Don't:

```cpp
void set_var(int); // Sets m_variable
int variable() const;  // Returns m_variable
```

Precede getters with the word `Get` if the function returns a value through out arguments.

###### Do:

```cpp
int get_unix_time(String&) const;
```

###### Don't:

```cpp
int unix_time(String&) const;
```

Use descriptive function names:

###### Do:

```cpp
bool convert_to_boolean(int);
```

###### Don't:

```cpp
bool to_boolean(int);
```

Prefer enums to bools if callers are likely to be passing constants. This makes code much more readable.

###### Do:

```cpp
DoSomething(something, AllowFoo::Yes);
SetVisibility(false);
```

###### Don't:

```cpp
DoSomething(something, true);
SetVisibility(NotVisible);
```

Enum members should use InterCaps with an initial capital letter.

Prefer `const` to `#define`. Prefer inline functions to macros.

`#defined` constants should use all uppercase names with words separated by underscores.

Use `#pragma once` instead of `#define` and `#ifdef` for header guards.

###### Do:

```cpp
// MyClass.h
#pragma once
```

###### Don't:

```cpp
// MyClass.h
#ifndef MyClass_h
#define MyClass_h
```

In C++ implementation files, do not use `using` declarations of any kind to import names in the standard template library. Directly qualify the names at the point they're used instead.

###### Do:

```cpp
// File.cpp

std::swap(a, b);
c = std::numeric_limits<int>::max()
```

###### Don't:

```cpp
// File.cpp

using std::swap;
swap(a, b);
```

```cpp
// File.cpp

using namespace std;
swap(a, b);
```

Instead of writing `unsigned` or `unsigned int`, use something like `uint` instead. Never use `signed`

###### Do:

```cpp
uint i = 0;
```

###### Don't:

```cpp
unsigned i = 0;
unsigned int j = 0;
```

For types with methods, prefer classes over structs.

### Singleton pattern

Use a static member function named "the()" to access the instance of the singleton.

###### Do:

```cpp
class UniqueObject {
public:
    static UniqueObject& the();
    // ...
}
```

###### Don't:

```cpp
class UniqueObject {
public:
    static UniqueObject& shared();
    // ...
}
```

```cpp
class UniqueObject {
    // ...
};

UniqueObject& my_unique_object(); // Free function.
```

### Comments

Make comments look like sentences by starting with a capital letter. One exception may be end of line comments like this `if (x == y) // false for NaN`.

Use FIXME: (without attribution) to denote items that need to be addressed in the future.

###### Do:

```cpp
DrawJPG(); // FIXME: Make this code handle JPG in addition to the PNG support
```

###### Don't:

```cpp
DrawJPG(); // FIXME(joe): Make this code handle JPG in addition to the PNG support.
```

```cpp
DrawJPG(); // TODO: Make this code handle JPG in addition to the PNG support
```

Multiline comments must use `//`.

###### Do:

```cpp
// Line 1
// Line 2
// Line 3
```

###### Don't:

```cpp
/* Line 1
   Line 2
   Line 3 */
```

Explain _why_ the code does something. The code itself should already say what is happening.

### Overriding Virtual Methods

The declaration of a virtual method inside a class must be declared with the `virtual` keyword. All subclasses of that class must either specify the `override` keyword when overriding the virtual method or the `final` keyword when overriding the virtual method and requiring that no further subclasses can override it.

### Const placement

Use "east const" style where `const` is written on the right side of the type being qualified. See [this article](https://mariusbancila.ro/blog/2018/11/23/join-the-east-const-revolution/) for more information about east const.

###### Do:

```cpp
String const& m_name;
```

###### Don't:

```cpp
const String& m_name;
```
