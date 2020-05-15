# LittleEnum [![Build Status](https://travis-ci.com/phil-zxx/LittleEnum.svg?branch=master)](https://travis-ci.com/phil-zxx/LittleEnum)
Header-Only Enum Implementation for C++17.

---

### Compiler Support
Successfully tested on `GCC`, `Clang` and `MSVC`, for C++17 only.

---

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

---

### Macro Expansion
In full, the macro from the example above is equivalent to / expands to:
```cpp
#include <array>
#include <iostream>

enum class Animal { Cat, Dog }; 

constexpr const char* _littleEnum_EnumToStrMap(const Animal e) 
{
    switch (e) 
    {
    case Animal::Cat:    return "Cat";
    case Animal::Dog:    return "Dog";
    case Animal::_NULL_: return "_NULL_";
    } 
    return {}; 
} 

constexpr std::array<std::pair<const char*, Animal>, 3> _littleEnum_StrToEnumMap(Animal) 
{
    return {{ {"Cat", Animal::Cat}, {"Dog", Animal::Dog}, {"_NULL_", Animal::_NULL_} }}; 
} 

std::ostream& operator<<(std::ostream& os, const Animal& rhs)
{
    return os << _littleEnum_EnumToStrMap(rhs); 
};
```
Functions `_littleEnum_EnumToStrMap` and `_littleEnum_StrToEnumMap` are automatically incorporated into `LittleEnum::toStr` and `LittleEnum::fromStr`, respectively.
