#include <little_enum.hpp>

LITTLE_ENUM_CLASS(Animal, Cat, Dog, Horse, Rabbit)


int main()
{
    /* Since we evaluate to constexpr, all unit tests are performed at compile time */

    /* Test for LittleEnum::toStr (put enum type in, get const char* out) */
    {
        constexpr const char* val1 = LittleEnum::toStr(Animal::Cat);
        constexpr const char* val2 = LittleEnum::toStr(Animal::Dog);
        constexpr const char* val3 = LittleEnum::toStr(Animal::Horse);
        constexpr const char* val4 = LittleEnum::toStr(Animal::Rabbit);

        static_assert(std::string_view(val1) == "Cat");
        static_assert(std::string_view(val2) == "Dog");
        static_assert(std::string_view(val3) == "Horse");
        static_assert(std::string_view(val4) == "Rabbit");
    }

    /* Test for LittleEnum::fromStr(const char*) (put const char* in, get enum type out) */
    {
        constexpr auto val1 = LittleEnum::fromStr<Animal>("Cat");
        constexpr auto val2 = LittleEnum::fromStr<Animal>("Dog");
        constexpr auto val3 = LittleEnum::fromStr<Animal>("Horse");
        constexpr auto val4 = LittleEnum::fromStr<Animal>("Rabbit");
        constexpr auto val5 = LittleEnum::fromStr<Animal>("SomeUnknownString");

        static_assert(val1 == Animal::Cat);
        static_assert(val2 == Animal::Dog);
        static_assert(val3 == Animal::Horse);
        static_assert(val4 == Animal::Rabbit);
        static_assert(val5 == Animal::_NULL_);
    }

    /* Test for LittleEnum::fromStr(const std::string_view&) (put string_view in, get enum type out) */
    {
        constexpr auto val1 = LittleEnum::fromStr<Animal>(std::string_view("Cat"));
        constexpr auto val2 = LittleEnum::fromStr<Animal>(std::string_view("Dog"));
        constexpr auto val3 = LittleEnum::fromStr<Animal>(std::string_view("Horse"));
        constexpr auto val4 = LittleEnum::fromStr<Animal>(std::string_view("Rabbit"));
        constexpr auto val5 = LittleEnum::fromStr<Animal>(std::string_view("SomeUnknownString"));

        static_assert(val1 == Animal::Cat);
        static_assert(val2 == Animal::Dog);
        static_assert(val3 == Animal::Horse);
        static_assert(val4 == Animal::Rabbit);
        static_assert(val5 == Animal::_NULL_);
    }

    return 0;
}
