//
// Created by jwats on 4/3/2021.
//

// Variadic functions take a variable number of arguments.
// printf is a canonical example: you provide a format specifier and an arbitrary number of parameters.

// YOu declare variadic functions by placing ... as the final parameter in teh function's argument list.
// similar to *args/**kwargs in Python

// You cannot extract elements from the variadic arguments directly. Instead, you access individual arguments
// using the utility functions in the <cstdarg> header

#include <cstdio>
#include <cstdint>
#include <cstdarg>

int sum(size_t n, ...)
{
    // all variadic functions must declare a va_list.
    va_list args;
    // A va_list requires initialization with va_start, which takes two arguments.
    // The first argument is a va_list, and the second is the size of the variadic arguments.
    va_start(args, n);
    int result{};
    // iterate over each element in the variadic arguments using the va_args function.
    while (n--)
    {
        // the first argument is the va_list argument, and the second is the argument type.
        auto next_element = va_arg(args, int);
        result += next_element;
    }
    // now call va_list with the va_list structure.
    va_end(args);
    return result;
}

// Variadic functions are unsafe and a common source of security vulnerabilities.
// Variadic arguments are not type-safe.

int main()
{
    // invoke sume with the seven arguments. The first is the number of variadic arguments (six) followed by six numbers.
    printf("The answer is %d.", sum(6, 2, 4, 6, 8, 10, 12));
}