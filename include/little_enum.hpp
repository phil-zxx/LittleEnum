#pragma once

#include <string_view>
#include <string>
#include <array>
#include <ostream>


namespace little_enum {

    struct Enum {
    private:
        #if defined(__clang__) && __clang_major__ >= 5 || defined(__GNUC__) && __GNUC__ >= 9 || defined(_MSC_VER) && _MSC_VER >= 1910
        static constexpr bool is_supported = true;
        #else
        static constexpr bool is_supported = false;
        #endif
        static_assert(is_supported, "Smart Enum implemention is not supported by the current compiler");

        template <typename E, E V>
        static constexpr auto get_enum_string() noexcept {
            #if defined(__clang__) || defined(__GNUC__)
                std::string_view name = std::string_view(__PRETTY_FUNCTION__, sizeof(__PRETTY_FUNCTION__) - 2);
            #elif defined(_MSC_VER)
                std::string_view name = std::string_view(__FUNCSIG__, sizeof(__FUNCSIG__) - 17);
            #else
                // Compiler is not supported
                return string_view();
            #endif

            // Prettify name
            for (size_t i = name.size(); i > 0; --i) {
                if (!((name[i - 1] >= '0' && name[i - 1] <= '9') || (name[i - 1] >= 'a' && name[i - 1] <= 'z') || (name[i - 1] >= 'A' && name[i - 1] <= 'Z') || (name[i - 1] == '_'))) {
                    name.remove_prefix(i);
                    break;
                }
            }
            if (name.size() > 0 && ((name.front() >= 'a' && name.front() <= 'z') || (name.front() >= 'A' && name.front() <= 'Z') || (name.front() == '_')))
                return name;

            // Unable to parse function name, return nothing
            return std::string_view();
        }

        template <typename E, auto V>
        static constexpr bool is_valid() noexcept {
            return get_enum_string<E, static_cast<E>(V)>().size() != 0;
        }

        template <typename E, int Min>
        static constexpr E get_enum_value(size_t i) noexcept {
            return static_cast<E>(Min + static_cast<int>(i));
        }

        template <size_t N>
        static constexpr size_t get_valid_value_count(const bool(&valid)[N]) noexcept {
            size_t count = 0;
            for (size_t i = 0; i < N; ++i) {
                if (valid[i])
                    ++count;
            }

            return count;
        }

        template <typename E, int Min, size_t... I>
        static constexpr auto get_values(std::index_sequence<I...>) noexcept {
            constexpr bool arr_is_valid[sizeof...(I)] = { is_valid<E, get_enum_value<E, Min>(I)>()... };
            constexpr size_t count = get_valid_value_count(arr_is_valid);

            std::array<E, count> values = {};
            for (size_t i = 0, v = 0; v < count; ++i) {
                if (arr_is_valid[i])
                    values[v++] = get_enum_value<E, Min>(i);
            }
            return values;
        }

        template <typename E>
        static constexpr auto min_value_v = -128;

        template <typename E>
        static constexpr auto max_value_v = 128;

        template <typename E>
        static constexpr auto values_v = get_values<E, min_value_v<E>>(std::make_index_sequence<max_value_v<E> - min_value_v<E>>{});

        template <typename E, size_t... I>
        static constexpr auto get_names(std::index_sequence<I...>) noexcept {
            return std::array<std::string_view, sizeof...(I)>{ {get_enum_string<E, values_v<E>[I]>()...} };
        }

        template <typename E>
        static constexpr auto enum_count_v = values_v<E>.size();

        template <typename E>
        static constexpr auto names_v = get_names<E>(std::make_index_sequence<values_v<E>.size()>{});

    public:
        // Returns the number of available enum values
        template <typename E>
        static constexpr size_t count() {
            return enum_count_v<E>;
        }

        // Converts enum value to std::string_view
        template <typename E>
        static constexpr std::string_view toSv(const E inputEnum) {
            for (size_t i = 0; i < enum_count_v<E>; ++i) {
                if (Enum::values_v<E>[i] == inputEnum)
                    return Enum::names_v<E>[i];
            }

            throw std::runtime_error("Unable to convert enum value to string");
        }
        
        // Converts enum value to std::string
        template <typename E>
        static std::string toStr(const E inputEnum) {
            return std::string(Enum::toSv(inputEnum));
        }
        
        // Converts enum value to underlying type value
        template <typename E>
        static constexpr std::underlying_type_t<E> toValue(const E inputEnum) {
            return static_cast<std::underlying_type_t<E>>(inputEnum);
        }

        // Converts std::string_view to enum value
        template <class E>
        static constexpr E fromSv(const std::string_view& inputSv) {
            for (size_t i = 0; i < enum_count_v<E>; ++i) {
                if (Enum::names_v<E>[i] == inputSv)
                    return Enum::values_v<E>[i];
            }

            throw std::runtime_error("Unable to convert string_view '" + std::string(inputSv) + "' to an enum value");
        }

        // Converts std::string to enum value
        template <class E>
        static E fromStr(const std::string& inputStr) {
            return Enum::fromSv<E>(inputStr);
        }
        
        // Converts char array (const char*) to enum value
        template <class E>
        static constexpr E fromCharArr(const char* inputCharArr) {
            return Enum::fromSv<E>(inputCharArr);
        }
        
        // Converts char to enum value
        template <class E>
        static constexpr E fromChar(const char& inputChar) {
            for (size_t i = 0; i < enum_count_v<E>; ++i) {
                if (Enum::names_v<E>[i][0] == inputChar)
                    return Enum::values_v<E>[i];
            }

            throw std::runtime_error("Unable to convert char '" + std::string(1, inputChar) + "' to an enum value");
        }

        // Returns the opposite enum value (only works for enums with exactly 2 values)
        template <class E>
        static constexpr E flip(const E inputEnum) {
            static_assert(Enum::enum_count_v<E> == 2, "Only enums with 2 actual values can be flipped");

            if (inputEnum == Enum::values_v<E>[0])
                return Enum::values_v<E>[1];
            else if (inputEnum == Enum::values_v<E>[1])
                return Enum::values_v<E>[0];
            
            throw std::runtime_error("Unable to flip enum value '" + Enum::toStr(inputEnum) + "'");
        }
    };
}

#define LITTLE_ENUM_CLASS(name, ...) enum class name { __VA_ARGS__ }; \
    inline std::ostream& operator<<(std::ostream& os, const name& x) { return os << little_enum::Enum::toStr(x); }

#define LITTLE_ENUM_CLASS_WITH_TYPE(name, type, ...) enum class name : type { __VA_ARGS__ }; \
    inline std::ostream& operator<<(std::ostream& os, const name& x) { return os << little_enum::Enum::toStr(x); }
