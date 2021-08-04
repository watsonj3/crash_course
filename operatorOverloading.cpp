//
// Created by jwats on 8/3/2021.
//

#include <stdexcept>
#include <limits>
#include <cstdio>

/*
 * For user-defined types, you can specify custom behavior for operators by employing operator overloading.
 * Ensure that the return types and parameters match the types of the operands you want to deal with.
 */

// <limits> provides type support, which allows you to query various properties of arithmetic types.
// Within limits, the template class numeric_limits exposes a number of member constants that provide information about
// the template parameter. One such method is the max() method, which returns the highest finite value of a given type.
// You can use this method to test type behavior.

struct CheckedInteger
{
    // const public field.  This value is immutable -- after construction, it's not possible to modify the state of a
    // CheckedInteger.
    const unsigned int value;

    // Constructor used to initialize the public field value.
    CheckedInteger(unsigned int value) : value{ value } { }

    // operator+ here allows you to add an ordinary unsigned int to a CheckedInteger to produce a new CheckedInteger with
    // the correct value.
    CheckedInteger operator+(unsigned int other) const
    {
        // The return value of operator+ is constructed here.
        CheckedInteger result{ value + other};
        // Whenever addition results in the overflow of an unsigned int, the result will be less than the original values.
        // throw an exception if an overflow occurs.
        if (result.value < value) throw std::runtime_error{ "Overflow!" };
        return result;
    }
};

int main()
{
    // construct a CheckedInteger
    CheckedInteger a{ 100 };
    // add CheckedInteger to an unsigned int.
    auto b = a + 200;
    printf("a + 200 = %u\n", b.value);
    try
    {
        // add a CheckedInteger to a maximum value of an unsigned int via numeric_limits.
        auto c = a + std::numeric_limits<unsigned int>::max();
    }
    catch (const std::overflow_error& e)
    {
        // this causes an overflow, which is detected by the operator+ overload and results in a thrown overflow_error
        printf("(a + max) Exception: %s\n", e.what());
    }
}

