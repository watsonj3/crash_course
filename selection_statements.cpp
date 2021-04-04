//
// Created by jwats on 4/2/2021.
//

// review of selection statements.

#include <cstdio>
#include <stdexcept>
#include <type_traits>

// this function template converts an else argument into Positive, Negative, or Zero
template <typename T>
constexpr const char* sign(const T& x)
{
    // sign takes a single argument and determines if it's equal to 0, greater than 0, or less than 0
    const char* result{};
    if (x == 0)
    {
        result = "zero";
    }
    else if (x > 0)
    {
        result = "positive";
    }
    else
    {
        result = "negative";
    }
    return result;
}

// constexpr if statements
// A constexpr if statement is evaluated at compile time. Code blocks that correspond to true
// conditions get emitted, and the rest is ignored.
// with templates and the <type_traits> header, constexpr if statements are extremely powerful.
// A major use for constexpr if is to provide custom behavior in a function template depending on some
// attributes of type parameters.
// value_of function template accepts a single argument x.
template <typename T>
auto value_of(T x)
{
    // determine whether the argument is a pointer type using std::is_pointer<T> type trait
    // At runtime, the constexpr if statement disappears.
    if constexpr (std::is_pointer<T>::value)
    {
        // throw an exception if argument is a nullptr, if it's a pointer type.
        if (!x) throw std::runtime_error{"Null pointer dereference."};
        // if it's not a nullptr, you dereference it and return the result.
        return *x;
    } else
    {
        // otherwise, x is not a pointer type, so you return it.
        return x;
    }
}

int main()
{
    printf("float 100 is %s\n", sign(100.0f));
    printf("int -200 is %s\n", sign(-200));
    printf("char 0 is %s\n", sign(char{}));

    unsigned long level{8998};
    auto level_ptr = &level;
    auto &level_ref = level;
    // instantiate value_of with  an unsigned long pointer, unsigned long reference, unsigned long, and nullptr.
    // each instantiation of value_of contains one branch of the selection statement or the other.
    printf("Power level = %lu\n", value_of(level_ptr));
    ++*level_ptr;
    printf("Power level = %lu\n", value_of(level_ref));
    ++level_ref;
    printf("It's over %lu\n", value_of(level++));
    try {
        level_ptr = nullptr;
        value_of(level_ptr);
    } catch (const std::exception& e) {
        printf("Exception: %s\n", e.what());
    }
}