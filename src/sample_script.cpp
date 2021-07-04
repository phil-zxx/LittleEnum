#include <little_enum.hpp>
#include <iostream>

LITTLE_ENUM_CLASS(Animal, Cat, Dog, Horse, Rabbit)


int main()
{
    using namespace little_enum;

    const Animal val1 = Animal::Cat;
    std::cout << "1) This enum prints to '" << val1 << "'" << std::endl;

    const Animal val2 = Enum::fromStr<Animal>("Rabbit");
    std::cout << "2) This enum prints to '" << Enum::toStr(val2) << "'" << std::endl;

    const Animal val3 = Enum::fromStr<Animal>("SomeUnknownString");
    std::cout << "3) This enum prints to '" << Enum::toStr(val3) << "'" << std::endl;

    return 0;
}
