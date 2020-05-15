#include <little_enum.hpp>

LITTLE_ENUM_CLASS(Animal, Cat, Dog, Horse, Rabbit)


int main()
{
    const Animal val1 = Animal::Cat;
    std::cout << "1) This enum prints to '" << val1 << "'" << std::endl;

    const Animal val2 = LittleEnum::fromStr<Animal>("Rabbit");
    std::cout << "2) This enum prints to '" << LittleEnum::toStr(val2) << "'" << std::endl;

    const Animal val3 = LittleEnum::fromStr<Animal>("SomeUnknownString");
    std::cout << "3) This enum prints to '" << LittleEnum::toStr(val3) << "'" << std::endl;

    return 0;
}
