//
// Created by jwats on 3/24/2021.
//
// limits has type support, similar to type_traits. This allows one to query various properties of arithmetic types.
// This program tries out the use of the overload operator method operator+.
// also will test limits of an unsigned int.
#include <limits>
#include <cstdio>
#include <stdexcept>

struct CheckedInteger
{
    // constructor takes single unsigned int. This is to member initialize the public field value.
    // CheckedInteger is immutable after construction.
    CheckedInteger(unsigned int value) : value{value} {}

    // allows add an ordinary unsigned int to a CheckedInteger to produce a new
    // CheckedInteger with the correct value.
    CheckedInteger operator+(unsigned int other) const
    {
        // return value constructed here.
        CheckedInteger result{value + other};
        // If addition results in overflow of an unsigned int, the result will be less
        // than the original values. Check here, and if overflow is detected, then throw
        // exception.
        if (result.value < value) throw std::runtime_error("Overflow!");
        // return value of operator+
        return result;
    }

    const unsigned int value;
};

int main()
{
    CheckedInteger a{100};
    // guaranteed to fit in a unsigned int.
    auto b = a + 200;
    printf("a + 200 = %u\n", b.value);
    try {
        // numeric_limits max method returns the highest finite value of a given type.
        // use this to check behavior of CheckInteger class.
        // guaranteed to cause a overflow error.
        auto c = a + std::numeric_limits<unsigned int>::max();
    } catch (const std::overflow_error& e) {
        printf("(a + max) Exception: %s\n", e.what());
    }
}

