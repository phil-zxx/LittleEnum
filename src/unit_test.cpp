#include <little_enum.hpp>
#include <mini_testing_framework.hpp>

LITTLE_ENUM_CLASS(Animal, Cat = -2, Dog = 99999999, Horse = 5, Rabbit, Koala = -8888888, __NULL__)
LITTLE_ENUM_CLASS(TenorUnit, D, B, W, M, Y, C, I, I2)
LITTLE_ENUM_CLASS_WITH_TYPE(PutCallFlag, char, Call = 'C', Put = 'P')

int main()
{
    using namespace little_enum;

    try
    {
        static_assert(Enum::count<Animal>() == 6);

        CHECK(Enum::fromStr<Animal>("Cat")      == Animal::Cat);
        CHECK(Enum::fromStr<Animal>("Dog")      == Animal::Dog);
        CHECK(Enum::fromStr<Animal>("Horse")    == Animal::Horse);
        CHECK(Enum::fromStr<Animal>("Rabbit")   == Animal::Rabbit);
        CHECK(Enum::fromStr<Animal>("Koala")    == Animal::Koala);
        CHECK(Enum::fromStr<Animal>("__NULL__") == Animal::__NULL__);

        static_assert(Enum::fromSv<Animal>("Cat")      == Animal::Cat);
        static_assert(Enum::fromSv<Animal>("Dog")      == Animal::Dog);
        static_assert(Enum::fromSv<Animal>("Horse")    == Animal::Horse);
        static_assert(Enum::fromSv<Animal>("Rabbit")   == Animal::Rabbit);
        static_assert(Enum::fromSv<Animal>("Koala")    == Animal::Koala);
        static_assert(Enum::fromSv<Animal>("__NULL__") == Animal::__NULL__);

        CHECK(Enum::toStr(Animal::Cat)      == "Cat");
        CHECK(Enum::toStr(Animal::Dog)      == "Dog");
        CHECK(Enum::toStr(Animal::Horse)    == "Horse");
        CHECK(Enum::toStr(Animal::Rabbit)   == "Rabbit");
        CHECK(Enum::toStr(Animal::Koala)    == "Koala");
        CHECK(Enum::toStr(Animal::__NULL__) == "__NULL__");

        static_assert(Enum::toSv(Animal::Cat)      == "Cat");
        static_assert(Enum::toSv(Animal::Dog)      == "Dog");
        static_assert(Enum::toSv(Animal::Horse)    == "Horse");
        static_assert(Enum::toSv(Animal::Rabbit)   == "Rabbit");
        static_assert(Enum::toSv(Animal::Koala)    == "Koala");
        static_assert(Enum::toSv(Animal::__NULL__) == "__NULL__");

        static_assert(Enum::toValue(Animal::Cat)      == -2);
        static_assert(Enum::toValue(Animal::Dog)      == 99999999);
        static_assert(Enum::toValue(Animal::Horse)    == 5);
        static_assert(Enum::toValue(Animal::Rabbit)   == 6);
        static_assert(Enum::toValue(Animal::Koala)    == -8888888);
        static_assert(Enum::toValue(Animal::__NULL__) == -8888887);

        static_assert(std::is_same_v<int,  std::underlying_type_t<Animal>> == true);
        static_assert(std::is_same_v<char, std::underlying_type_t<Animal>> == false);

        size_t i = 0;
        for (const auto& [name, val] : Enum::getValuePairs<Animal>()) {
            if (i == 0)      CHECK(name == "Cat"      && val == Animal::Cat);
            else if (i == 1) CHECK(name == "Dog"      && val == Animal::Dog);
            else if (i == 2) CHECK(name == "Horse"    && val == Animal::Horse);
            else if (i == 3) CHECK(name == "Rabbit"   && val == Animal::Rabbit);
            else if (i == 4) CHECK(name == "Koala"    && val == Animal::Koala);
            else if (i == 5) CHECK(name == "__NULL__" && val == Animal::__NULL__);
            ++i;
        }


        static_assert(Enum::count<TenorUnit>() == 8);

        static_assert(Enum::fromChar<TenorUnit>('D') == TenorUnit::D);
        static_assert(Enum::fromChar<TenorUnit>('B') == TenorUnit::B);
        static_assert(Enum::fromChar<TenorUnit>('W') == TenorUnit::W);
        static_assert(Enum::fromChar<TenorUnit>('M') == TenorUnit::M);
        static_assert(Enum::fromChar<TenorUnit>('Y') == TenorUnit::Y);
        static_assert(Enum::fromChar<TenorUnit>('C') == TenorUnit::C);
        static_assert(Enum::fromChar<TenorUnit>('I') == TenorUnit::I);
        static_assert(Enum::fromChar<TenorUnit>('I') != TenorUnit::I2);

        CHECK(Enum::fromStr<TenorUnit>("D")  == TenorUnit::D);
        CHECK(Enum::fromStr<TenorUnit>("B")  == TenorUnit::B);
        CHECK(Enum::fromStr<TenorUnit>("W")  == TenorUnit::W);
        CHECK(Enum::fromStr<TenorUnit>("M")  == TenorUnit::M);
        CHECK(Enum::fromStr<TenorUnit>("Y")  == TenorUnit::Y);
        CHECK(Enum::fromStr<TenorUnit>("C")  == TenorUnit::C);
        CHECK(Enum::fromStr<TenorUnit>("I")  == TenorUnit::I);
        CHECK(Enum::fromStr<TenorUnit>("I2") == TenorUnit::I2);

        static_assert(Enum::fromSv<TenorUnit>("D")  == TenorUnit::D);
        static_assert(Enum::fromSv<TenorUnit>("B")  == TenorUnit::B);
        static_assert(Enum::fromSv<TenorUnit>("W")  == TenorUnit::W);
        static_assert(Enum::fromSv<TenorUnit>("M")  == TenorUnit::M);
        static_assert(Enum::fromSv<TenorUnit>("Y")  == TenorUnit::Y);
        static_assert(Enum::fromSv<TenorUnit>("C")  == TenorUnit::C);
        static_assert(Enum::fromSv<TenorUnit>("I")  == TenorUnit::I);
        static_assert(Enum::fromSv<TenorUnit>("I2") == TenorUnit::I2);

        CHECK(Enum::toStr(TenorUnit::D)  == "D");
        CHECK(Enum::toStr(TenorUnit::B)  == "B");
        CHECK(Enum::toStr(TenorUnit::W)  == "W");
        CHECK(Enum::toStr(TenorUnit::M)  == "M");
        CHECK(Enum::toStr(TenorUnit::Y)  == "Y");
        CHECK(Enum::toStr(TenorUnit::C)  == "C");
        CHECK(Enum::toStr(TenorUnit::I)  == "I");
        CHECK(Enum::toStr(TenorUnit::I2) == "I2");

        static_assert(Enum::toSv(TenorUnit::D)  == "D");
        static_assert(Enum::toSv(TenorUnit::B)  == "B");
        static_assert(Enum::toSv(TenorUnit::W)  == "W");
        static_assert(Enum::toSv(TenorUnit::M)  == "M");
        static_assert(Enum::toSv(TenorUnit::Y)  == "Y");
        static_assert(Enum::toSv(TenorUnit::C)  == "C");
        static_assert(Enum::toSv(TenorUnit::I)  == "I");
        static_assert(Enum::toSv(TenorUnit::I2) == "I2");

        static_assert(Enum::toValue(TenorUnit::D)  == 0);
        static_assert(Enum::toValue(TenorUnit::B)  == 1);
        static_assert(Enum::toValue(TenorUnit::W)  == 2);
        static_assert(Enum::toValue(TenorUnit::M)  == 3);
        static_assert(Enum::toValue(TenorUnit::Y)  == 4);
        static_assert(Enum::toValue(TenorUnit::C)  == 5);
        static_assert(Enum::toValue(TenorUnit::I)  == 6);
        static_assert(Enum::toValue(TenorUnit::I2) == 7);

        static_assert(std::is_same_v<int,  std::underlying_type_t<TenorUnit>> == true);
        static_assert(std::is_same_v<char, std::underlying_type_t<TenorUnit>> == false);


        static_assert(Enum::count<PutCallFlag>() == 2);

        static_assert(Enum::flip<PutCallFlag>(PutCallFlag::Call) == PutCallFlag::Put);
        static_assert(Enum::flip<PutCallFlag>(PutCallFlag::Put)  == PutCallFlag::Call);

        CHECK(Enum::fromStr<PutCallFlag>("Call") == PutCallFlag::Call);
        CHECK(Enum::fromStr<PutCallFlag>("Put")  == PutCallFlag::Put);

        static_assert(Enum::fromSv<PutCallFlag>("Call") == PutCallFlag::Call);
        static_assert(Enum::fromSv<PutCallFlag>("Put")  == PutCallFlag::Put);

        CHECK(Enum::toStr(PutCallFlag::Call) == "Call");
        CHECK(Enum::toStr(PutCallFlag::Put)  == "Put");

        static_assert(Enum::toSv(PutCallFlag::Call) == "Call");
        static_assert(Enum::toSv(PutCallFlag::Put)  == "Put");

        static_assert(Enum::toValue(PutCallFlag::Call) == 'C');
        static_assert(Enum::toValue(PutCallFlag::Put)  == 'P');

        static_assert(std::is_same_v<int,  std::underlying_type_t<PutCallFlag>> == false);
        static_assert(std::is_same_v<char, std::underlying_type_t<PutCallFlag>> == true);

        std::cout << "All good\n";
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << "\n";
        return -1;
    }
}
