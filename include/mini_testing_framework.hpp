#include <iostream>

#define CHECK(val) if ((val) == false) throw std::runtime_error("Expression " #val " is false")

constexpr bool operator==(std::string_view a, std::string_view b)
{
    // This function is purely here, because bool operator==(string_view, string_view) does
    // not work in MSVC 19.16 (VS 2017), if the underlying data pointers are different.

    if (a.size() != b.size())
        return false;

    for (size_t i = 0; i < a.size(); ++i)
        if (a[i] != b[i])
            return false;

    return true;
}
