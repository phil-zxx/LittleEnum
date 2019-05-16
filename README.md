# LittleEnum

Header-Only Enum Implementation for C++17.
<br><br>

### Compiler Support
Successfully tested on `g++ 8.3.0` (CYGWIN 3.0.7) and `CL 19.20.27508.1` (MSVC 2019), on C++17 only.
<br><br>

### C++ Example
The following macro defines an `Animal` enum class:
```cpp
#include <little_enum.hpp>

LITTLE_ENUM_CLASS(Animal, Cat, Dog)
```
One can then use a convenient interface to convert between the enum & string values. For example:
```cpp
const char*  var1 = LittleEnum::toStr(Animal::Dog);        // Gives "Dog"
const Animal var2 = LittleEnum::fromStr<Animal>("Cat");    // Gives Animal::Cat
const Animal var3 = LittleEnum::fromStr<Animal>("Other");  // Gives Animal::_NULL_
```
<br>

### Macro Expansion
In full, the macro from the example above is equivalent to / expands to:
```cpp
#include <array>
#include <iostream>

enum class Animal { Cat, Dog }; 

constexpr const char* enumToStringMap(const Animal e) 
{
  switch (e) 
  {
  case Animal::_NULL_: return "_NULL_";
  case Animal::Cat:    return "Cat";
  case Animal::Dog:    return "Dog";
  } 
  return {}; 
} 

constexpr std::array<std::pair<const char*, Animal>, 3> stringToEnumMap(Animal) 
{
  return {{ {"_NULL_", Animal::_NULL_}, {"Cat", Animal::Cat}, {"Dog", Animal::Dog} }}; 
} 

std::ostream& operator<<(std::ostream& os, const Animal& rhs)
{
  return os << enumToStringMap(rhs); 
};
```
Function `enumToStringMap` is automatically incorporated into `LittleEnum::toStr` and function `stringToEnumMap` is automatically incorporated into `LittleEnum::fromStr`.
