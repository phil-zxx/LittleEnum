# LittleEnum [![Build Status](https://travis-ci.com/phil-zxx/LittleEnum.svg?branch=master)](https://travis-ci.com/phil-zxx/LittleEnum)
Header-Only Smart Enum Implementation for C++17.

---

### Compiler Support
Successfully tested on `GCC`, `Clang` and `MSVC`, for C++17 only.

---

### C++ Example
The following macro defines an `Animal` enum class:
```cpp
#include <little_enum.hpp>

LITTLE_ENUM_CLASS(Animal, Dog, Hamster = 99, Cat, Horse = -123);
```
Below is some sample usage via the provided interface functions:
```cpp
using namespace little_enum;

const Animal      a = Enum::fromStr<Animal>("Cat");  // Converts string "Cat" to the actual enum value Animal::Cat
const std::string b = Enum::toStr(Animal::Hamster);  // Converts enum value Animal::Hamster to string "Hamster"
const int         c = Enum::toValue(Animal::Horse);  // Converts enum value Animal::Horse to the underlying int value -123

const size_t      d = Enum::count<Animal>();         // Gives the number of available Animal enum values, which is 4 

std::cout << "Value: " << Animal::Dog;               // Gives "Value: Dog", via operator<<(std::ostream&, const Animal&)
```

---

### Available Functions
Below is a list of all functions provided by helper class `Enum`:
```cpp
// Returns a std::array of {name, value} pairs for the specified enum type
template <class E>
static constexpr std::array getValuePairs()

// Returns the number of available enum values
template <class E>
static constexpr size_t count()

// Converts enum value to std::string_view
template <class E>
static constexpr std::string_view toSv(const E inputEnum)

// Converts enum value to std::string
template <class E>
static std::string toStr(const E inputEnum)

// Converts enum value to underlying type value
template <class E>
static constexpr std::underlying_type_t<E> toValue(const E inputEnum)

// Converts std::string_view to enum value
template <class E>
static constexpr E fromSv(const std::string_view& inputSv)

// Converts std::string to enum value
template <class E>
static E fromStr(const std::string& inputStr)

// Converts char to enum value
template <class E>
static constexpr E fromChar(const char inputChar)

// Returns the opposite enum value (only works for enums with exactly 2 values)
template <class E>
static constexpr E flip(const E inputEnum)
```
Additionally, the following free function is provided for each enum type `E`:
```cpp
// Outputs the string value of the input enum to the stream
std::ostream& operator<<(std::ostream& os, const E& inputEnum)
```
