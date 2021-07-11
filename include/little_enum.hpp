#pragma once

#include <array>
#include <string_view>
#include <string>
#include <iostream>


namespace little_enum {

    namespace detail {

        // Allows you to obtain (Enum::val) from (Enum::val = num_val) by taking advantage of C-cast precedence
        // Idea from better_enum
        template <class E>
        struct remove_assign {
            constexpr explicit remove_assign(E value) : m_value(value) { }

            template <class T>
            constexpr const remove_assign& operator=(T) const { return *this; }

            constexpr operator E() const { return m_value; }

        private:
            E m_value;
        };

        constexpr std::string_view shorten_name(const char* value)
        {
            std::string_view name = value;

            for (size_t i = 0, size = name.size(); i < size; ++i)
            {
                if (!(('0' <= name[i] && name[i] <= '9') || ('a' <= name[i] && name[i] <= 'z') || ('A' <= name[i] && name[i] <= 'Z') || (name[i] == '_')))
                {
                    name.remove_suffix(size - i);
                    break;
                }
            }

            return name;
        }
    }

    struct Enum {
    private:
        template <class E>
        static constexpr auto enum_array();

        template <class E>
        static constexpr auto enum_array_v = Enum::enum_array<E>();
        
        template <class E>
        static constexpr size_t count_v = Enum::enum_array_v<E>.size();

        template <class E>
        struct Pair {
            std::string_view name;
            E value;
        };

    public:
        // Returns a std::array of {name, value} pairs for the specified enum type
        template <class E>
        static constexpr auto getValuePairs() {
            return Enum::enum_array_v<E>;
        }

        // Returns the number of available enum values
        template <class E>
        static constexpr size_t count() {
            return Enum::enum_array_v<E>.size();
        }

        // Converts enum value to std::string_view
        template <class E>
        static constexpr std::string_view toSv(const E inputEnum) {
            for (const auto& p : Enum::enum_array_v<E>) {
                if (p.value == inputEnum)
                    return p.name;
            }
            throw std::runtime_error("Unable to convert enum value to string");
        }

        // Converts enum value to std::string
        template <class E>
        static std::string toStr(const E inputEnum) {
            return std::string(Enum::toSv(inputEnum));
        }

        // Converts enum value to underlying type value
        template <class E>
        static constexpr std::underlying_type_t<E> toValue(const E inputEnum) {
            return static_cast<std::underlying_type_t<E>>(inputEnum);
        }

        // Converts std::string_view to enum value
        template <class E>
        static constexpr E fromSv(const std::string_view& inputSv) {
            for (const auto& p : Enum::enum_array_v<E>) {
                if (p.name == inputSv)
                    return p.value;
            }
            throw std::runtime_error("Unable to convert string '" + std::string(inputSv) + "' to an enum value");
        }

        // Converts std::string to enum value
        template <class E>
        static E fromStr(const std::string& inputStr) {
            return Enum::fromSv<E>(inputStr);
        }

        // Converts char to enum value
        template <class E>
        static constexpr E fromChar(const char& inputChar) {
            for (const auto& p : Enum::enum_array_v<E>) {
                if (p.name.size() == 1 && p.name.front() == inputChar)
                    return p.value;
            }
            throw std::runtime_error("Unable to convert char '" + std::string(1, inputChar) + "' to an enum value");
        }

        // Returns the opposite enum value (only works for enums with exactly 2 values)
        template <class E>
        static constexpr E flip(const E inputEnum) {
            static_assert(Enum::count_v<E> == 2, "Only enums with 2 actual values can be flipped");

            if (inputEnum == Enum::enum_array_v<E>[0].value)
                return Enum::enum_array_v<E>[1].value;
            else if (inputEnum == Enum::enum_array_v<E>[1].value)
                return Enum::enum_array_v<E>[0].value;
            else
                throw std::runtime_error("Unable to flip enum value '" + Enum::toStr(inputEnum) + "'");
        }
    };
}

#define LITTLE_ENUM_EXPAND(x) x
#define LITTLE_ENUM_COMMA() ,
#define LITTLE_ENUM_ARRAY_PAIR(name, x) { little_enum::detail::shorten_name(#x), (little_enum::detail::remove_assign<name>)name::x }

#define LITTLE_ENUM_STR_CONCAT_(a, ...) a##__VA_ARGS__
#define LITTLE_ENUM_STR_CONCAT(a, ...) LITTLE_ENUM_STR_CONCAT_(a, __VA_ARGS__)

#define LITTLE_ENUM_ARG_COUNT_(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,_63,_64,VAL,...) VAL
#define LITTLE_ENUM_ARG_COUNT(...) LITTLE_ENUM_EXPAND(LITTLE_ENUM_ARG_COUNT_(__VA_ARGS__,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1))

/* Python Script to create the below list of macros
for i in range(2, 65) :
    print(f'#define LITTLE_ENUM_LOOP_{i}(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_{i-1}(f, n, d, __VA_ARGS__))')
*/

// Loop idea from better_enum & wise_enum
#define LITTLE_ENUM_LOOP_1(f, n, d, x)       f(n,x)
#define LITTLE_ENUM_LOOP_2(f, n, d, x, ...)  f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_1(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_3(f, n, d, x, ...)  f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_2(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_4(f, n, d, x, ...)  f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_3(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_5(f, n, d, x, ...)  f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_4(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_6(f, n, d, x, ...)  f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_5(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_7(f, n, d, x, ...)  f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_6(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_8(f, n, d, x, ...)  f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_7(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_9(f, n, d, x, ...)  f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_8(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_10(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_9(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_11(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_10(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_12(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_11(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_13(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_12(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_14(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_13(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_15(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_14(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_16(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_15(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_17(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_16(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_18(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_17(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_19(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_18(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_20(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_19(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_21(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_20(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_22(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_21(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_23(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_22(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_24(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_23(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_25(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_24(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_26(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_25(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_27(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_26(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_28(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_27(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_29(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_28(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_30(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_29(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_31(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_30(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_32(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_31(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_33(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_32(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_34(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_33(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_35(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_34(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_36(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_35(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_37(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_36(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_38(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_37(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_39(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_38(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_40(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_39(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_41(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_40(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_42(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_41(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_43(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_42(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_44(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_43(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_45(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_44(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_46(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_45(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_47(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_46(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_48(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_47(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_49(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_48(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_50(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_49(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_51(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_50(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_52(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_51(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_53(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_52(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_54(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_53(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_55(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_54(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_56(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_55(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_57(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_56(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_58(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_57(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_59(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_58(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_60(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_59(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_61(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_60(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_62(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_61(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_63(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_62(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_LOOP_64(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_EXPAND(LITTLE_ENUM_LOOP_63(f, n, d, __VA_ARGS__))

#define LITTLE_ENUM_IMPL(name, loop_func_name, ...)                                                                         \
    template<> constexpr auto little_enum::Enum::enum_array<name>() {                                                       \
        return std::array<little_enum::Enum::Pair<name>, LITTLE_ENUM_ARG_COUNT(__VA_ARGS__)>{little_enum::Enum::Pair<name>  \
            LITTLE_ENUM_EXPAND(loop_func_name(LITTLE_ENUM_ARRAY_PAIR, name, LITTLE_ENUM_COMMA, __VA_ARGS__)) }; }           \
    inline std::ostream& operator<<(std::ostream& os, const name& x) { return os << little_enum::Enum::toSv(x); }

#define LITTLE_ENUM_CLASS(name, ...) enum class name { __VA_ARGS__ };  \
    LITTLE_ENUM_IMPL(name, LITTLE_ENUM_STR_CONCAT(LITTLE_ENUM_LOOP_, LITTLE_ENUM_ARG_COUNT(__VA_ARGS__)), __VA_ARGS__)

#define LITTLE_ENUM_CLASS_WITH_TYPE(name, type, ...) enum class name : type { __VA_ARGS__ };  \
    LITTLE_ENUM_IMPL(name, LITTLE_ENUM_STR_CONCAT(LITTLE_ENUM_LOOP_, LITTLE_ENUM_ARG_COUNT(__VA_ARGS__)), __VA_ARGS__)
