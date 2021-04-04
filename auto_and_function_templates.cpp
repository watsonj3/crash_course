//
// Created by jwats on 4/2/2021.
//

// You can have the compiler deduce the correct return type by using auto.
// As with auto type deduction, the compiler deduces the return type, fixing the runtime type.

// The primary use case for auto type deduction is with function templates, where a return type can depend
// on the template parameters.

// It's possible to extend the auto-return type deduction syntax to provide the return type as a suffix with
// the arrow operator -> . This way, you can append an expression that evaluates to the function's return type.
// This is commonly paired with decltype type expressions. A decltype type expression yields another expression's
// resultant type.

// The following expression yields int, because the integer literal 100 has that type.
// decltype(100);
// decltype is rare outside of programming with templates.

// You can combine auto-return deduction and decltype to document the return types of function templates.

#include <cstdio>

// the add function employs auto type deduction with the decltype type expression.
// Each time you instantiate a template with two types x and y, the compiler evaluates decltype(X + Y)
// and fixes the return type of add.
template <typename X, typename Y>
auto add(X x, Y y) -> decltype(x + y) {
    return x + y;
}

int main()
{
    // add a double and an int. Compiler determines that decltype(double{100.} + int{-10} is a double
    // which fixes the return type of this add instantiation.
    auto my_double = add(100., -10);
    printf("decltype(double + int) = double; %f\n", my_double);

    auto my_uint = add(100U, -20);
    printf("decltype(uint + int) = uint; %u\n", my_uint);

    auto my_ulonglong = add(char{100}, 54'999'900ull);
    printf("decltype(char + ulonglong) = ulonglong; %llu\n", my_ulonglong);
}