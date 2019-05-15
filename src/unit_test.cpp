#include <little_enum.hpp>

LITTLE_ENUM_CLASS(Animal, Cat, Dog, Horse, Rabbit);


int main()
{
    /* Since we evaluate to constexpr, all unit tests are performed at compile time */

    /* Test for the LittleEnum::toStr function (put enum type in, get const char* out) */
    {
        constexpr const char* val1 = LittleEnum::toStr(Animal::Cat);
        constexpr const char* val2 = LittleEnum::toStr(Animal::Dog);
        constexpr const char* val3 = LittleEnum::toStr(Animal::Horse);
        constexpr const char* val4 = LittleEnum::toStr(Animal::Rabbit);

        static_assert(val1 == "Cat");
        static_assert(val2 == "Dog");
        static_assert(val3 == "Horse");
        static_assert(val4 == "Rabbit");
    }

    /* Test for the LittleEnum::fromStr function (put const char* in, get enum type out) */
    {
        constexpr Animal val1 = LittleEnum::fromStr<Animal>("Cat");
        constexpr Animal val2 = LittleEnum::fromStr<Animal>("Dog");
        constexpr Animal val3 = LittleEnum::fromStr<Animal>("Horse");
        constexpr Animal val4 = LittleEnum::fromStr<Animal>("Rabbit");

        static_assert(val1 == Animal::Cat);
        static_assert(val2 == Animal::Dog);
        static_assert(val3 == Animal::Horse);
        static_assert(val4 == Animal::Rabbit);
    }

    /* Test for the LittleEnum::fromStr function (put string_view in, get enum type out) */
    {
        constexpr Animal val1 = LittleEnum::fromStr<Animal>(std::string_view("Cat"));
        constexpr Animal val2 = LittleEnum::fromStr<Animal>(std::string_view("Dog"));
        constexpr Animal val3 = LittleEnum::fromStr<Animal>(std::string_view("Horse"));
        constexpr Animal val4 = LittleEnum::fromStr<Animal>(std::string_view("Rabbit"));

        static_assert(val1 == Animal::Cat);
        static_assert(val2 == Animal::Dog);
        static_assert(val3 == Animal::Horse);
        static_assert(val4 == Animal::Rabbit);
    }

    return 0;
}
