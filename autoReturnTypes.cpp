//
// Created by jwats on 8/5/2021.
//

// The primary use case for auto type deduction is with function templates, where a return type can depend on the
// template parameters.
// It's possible to extend the auto-return type deduction syntax to provide the return type as a suffix with the
// arrow operator ->. This way, you can append an expression that evaluates to the function's return type.
// This can be helpful in certain situations.  For example, this form of auto type deduction is commonly paired with a
// expressions decltype type expression.  A decltype type expression yields another expression's resultant type.
// The following decltype expressions yields int: decltype(100). Outside of generic programming with templates, decltype is rare.

// You can combine auto-return-type deduction and decltype to document the return types of function templates.

#include <cstdio>

// The add function employs auto type deduction with the decltype type expression.
// Each time you instantiate a template with two types x and y, the compiler evaluates decltype(x + y) and fixes
// the return type of add.
template <typename X, typename Y>
auto add(X x, Y y) -> decltype(x + y)
{
    return x + y;
}

int main()
{
    // provide 3 instantiations. First, add a double and an int. The compiler determines that the type is a double, which
    // fixes the return type of this add instantiation. This, in turn, sets the type of my_double to double.
    auto my_double = add(100., -10);
    printf("decltype(double + int) = double; %f\n", my_double);

    auto my_uint = add(100U, -20);
    printf("decltype(uint + int) = uint; %u\n", my_uint);

    auto my_ulonglong = add(char{100}, 54'999'900ull);
    printf("decltype(char + ulonglong) = ulonglong; %llu\n", my_ulonglong);
}