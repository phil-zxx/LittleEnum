#pragma once

#include <array>
#include <iostream>


struct LittleEnum
{
private:
    static constexpr bool strEqual(const char* lhs, const char* rhs)
    {
        while (*lhs && (*lhs == *rhs))
            lhs++, rhs++;

        return !(*lhs < *rhs || *lhs > * rhs);
    }

    template <class T>
    struct StringToEnumMap
    {
        static constexpr auto range = stringToEnumMap(T{});
    };

public:
    template <class T>
    static constexpr const char* toStr(const T inputEnum)
    {
        return enumToStringMap(inputEnum);
    }

    template <class T>
    static constexpr T fromStr(const char* inputString)
    {
        for (const auto& [strValue, enumValue] : StringToEnumMap<T>::range)
        {
            if (LittleEnum::strEqual(strValue, inputString))
                return enumValue;
        }
        return T::_NULL_;
    }

    template <class T>
    static constexpr T fromStr(const std::string& inputString)
    {
        return LittleEnum::fromStr<T>(inputString.c_str());
    }

    template <class T>
    static constexpr T fromStr(const std::string_view& inputString)
    {
        return LittleEnum::fromStr<T>(inputString.data());
    }
};

#define LITTLE_ENUM_CLASS_EXPAND(x) x

#define LITTLE_ENUM_CLASS_DIVIDER_EMPTY() 
#define LITTLE_ENUM_CLASS_DIVIDER_COMMA() ,

#define LITTLE_ENUM_CLASS_STR_CONCAT(a, ...) LITTLE_ENUM_CLASS_STR_CONCAT_(a, __VA_ARGS__)
#define LITTLE_ENUM_CLASS_STR_CONCAT_(a, ...) a##__VA_ARGS__

#define LITTLE_ENUM_CLASS_ARG_COUNT_(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,_63,_64,VAL,...) VAL
#define LITTLE_ENUM_CLASS_ARG_COUNT(...) LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_ARG_COUNT_(__VA_ARGS__,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1))

#define LITTLE_ENUM_CLASS_CASE_RETURN(name, x) case name::x: return #x;
#define LITTLE_ENUM_CLASS_ARRAY_PAIR(name, x) { #x, name::x}

/* Python Script to create the below list of macros
for i in range(2,65):
    print(f'#define LITTLE_ENUM_CLASS_LOOP_{i}(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_{i-1}(f, n, d, __VA_ARGS__))')
*/

#define LITTLE_ENUM_CLASS_LOOP_1(f, n, d, x)       f(n,x)
#define LITTLE_ENUM_CLASS_LOOP_2(f, n, d, x, ...)  f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_1(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_3(f, n, d, x, ...)  f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_2(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_4(f, n, d, x, ...)  f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_3(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_5(f, n, d, x, ...)  f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_4(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_6(f, n, d, x, ...)  f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_5(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_7(f, n, d, x, ...)  f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_6(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_8(f, n, d, x, ...)  f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_7(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_9(f, n, d, x, ...)  f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_8(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_10(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_9(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_11(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_10(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_12(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_11(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_13(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_12(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_14(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_13(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_15(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_14(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_16(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_15(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_17(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_16(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_18(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_17(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_19(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_18(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_20(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_19(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_21(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_20(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_22(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_21(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_23(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_22(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_24(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_23(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_25(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_24(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_26(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_25(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_27(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_26(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_28(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_27(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_29(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_28(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_30(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_29(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_31(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_30(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_32(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_31(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_33(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_32(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_34(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_33(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_35(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_34(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_36(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_35(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_37(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_36(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_38(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_37(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_39(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_38(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_40(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_39(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_41(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_40(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_42(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_41(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_43(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_42(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_44(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_43(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_45(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_44(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_46(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_45(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_47(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_46(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_48(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_47(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_49(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_48(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_50(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_49(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_51(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_50(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_52(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_51(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_53(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_52(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_54(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_53(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_55(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_54(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_56(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_55(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_57(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_56(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_58(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_57(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_59(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_58(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_60(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_59(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_61(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_60(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_62(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_61(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_63(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_62(f, n, d, __VA_ARGS__))
#define LITTLE_ENUM_CLASS_LOOP_64(f, n, d, x, ...) f(n,x) d() LITTLE_ENUM_CLASS_EXPAND(LITTLE_ENUM_CLASS_LOOP_63(f, n, d, __VA_ARGS__))


#define LITTLE_ENUM_CLASS_IMPL(name, loop_func_name, ...)                                                                                \
    enum class name { __VA_ARGS__ };                                                                                                     \
    constexpr const char* enumToStringMap(const name e) {                                                                     \
        switch (e) {                                                                                                                     \
            LITTLE_ENUM_CLASS_EXPAND(loop_func_name(LITTLE_ENUM_CLASS_CASE_RETURN, name, LITTLE_ENUM_CLASS_DIVIDER_EMPTY, __VA_ARGS__))  \
        }                                                                                                                                \
        return {}; }                                                                                                                     \
    constexpr std::array<std::pair<const char*, name>, LITTLE_ENUM_CLASS_ARG_COUNT(__VA_ARGS__)> stringToEnumMap(name) {            \
        return {{                                                                                                                        \
            LITTLE_ENUM_CLASS_EXPAND(loop_func_name(LITTLE_ENUM_CLASS_ARRAY_PAIR, name, LITTLE_ENUM_CLASS_DIVIDER_COMMA, __VA_ARGS__))   \
        }}; }                                                                                                                            \
    std::ostream& operator<<(std::ostream& os, const name& rhs) { return os << enumToStringMap(rhs); }

#define LITTLE_ENUM_CLASS(name, ...)                                                                                                     \
    LITTLE_ENUM_CLASS_IMPL(name, LITTLE_ENUM_CLASS_STR_CONCAT(LITTLE_ENUM_CLASS_LOOP_, LITTLE_ENUM_CLASS_ARG_COUNT(_NULL_, __VA_ARGS__)), _NULL_, __VA_ARGS__)
