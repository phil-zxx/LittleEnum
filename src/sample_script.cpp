#include <little_enum.hpp>

LITTLE_ENUM_CLASS(Animal, Cat, Dog, Horse, Rabbit);


int main()
{
    constexpr Animal val1 = Animal::Cat;
    std::cout << "1) This enum prints to '" << val1 << "'" << std::endl;

    constexpr Animal val2 = LittleEnum::fromStr<Animal>("Rabbit");
    std::cout << "2) This enum prints to '" << LittleEnum::toStr(val2) << "'" << std::endl;

    return 0;
}
