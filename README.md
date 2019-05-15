# LittleEnum

Header-Only Enum Implementation for C++17.
<br><br><br>

### Compiler Support
Successfully tested on `g++ 8.3.0` (CYGWIN 3.0.7) and `CL 19.20.27508.1` (MSVC 2019), on C++17 only.
<br><br><br>

### Basic C++ Example
The following macro defines an `Animal` enum class:
```cpp
#include <little_enum.hpp>

LITTLE_ENUM_CLASS(Animal, Cat, Dog, Horse);
```
In full, this macro is equivalent to / it expands to:
```cpp
#include <array>
#include <iostream>

enum class Animal { Cat, Dog, Horse }; 

constexpr const char* enumToStringImplementation(const Animal e) 
{
  switch (e) 
  {
  case Animal::Cat:   return "Cat"; 
  case Animal::Dog:   return "Dog"; 
  case Animal::Horse: return "Horse";
  } 
  return {}; 
} 

constexpr std::array<std::pair<Animal, const char*>, 3> stringEnumEnumerator(Animal) 
{
  return {{ { Animal::Cat, "Cat"}, { Animal::Dog, "Dog"}, { Animal::Horse, "Horse"} }}; 
} 

std::ostream& operator<<(std::ostream& os, const Animal& rhs)
{
  return os << LittleEnum::toStr(rhs); 
};
```
Functions `enumToStringImplementation` and `stringEnumEnumerator` can be used to convert between enums & strings.

A class is provides which wraps those functions into a convenient interface:
```cpp
struct LittleEnum
{
  template <class T> constexpr T fromStr(const char* inputString);
  template <class T> constexpr const char* toStr(const T inputEnum);
}
```
