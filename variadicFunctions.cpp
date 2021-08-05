//
// Created by jwats on 8/5/2021.
//

// Variadic functions

// Variadic functions take a variable number of arguments, meaning you can take any number of arguments.
// The variadic function printf is a canonical example: you provide a format specifier and an arbitrary number of parameters.
// Because printf is a variadic function, it accepts any number of parameters.
// Similar to Python's *args/**kwargs

// You declare variadic functions by placing ... as the final parameter in the function's argument list.
// When a variadic function is invoked, the compiler matches arguments against declared arguments.
// Any leftovers pack into the variadic arguments represented by the ... argument.
// You cannot extract elements from the variadic arguments directly.  Instead, you access individual arguments using the
// utility functions in the <cstdarg> header.

#include <cstdio>
#include <cstdint>
#include <cstdarg>

// sum is declared as a variadic function
int sum(size_t n, ...)
{
    // all variadic functions must declare a va_list.
    va_list args;
    // A va_list requires initialization with va_start, which takes two arguments.
    // The first argument is a va_list, and the second is the size of the variadic arguments.
    va_start(args, n);
    int result{};
    while (n--)
    {
        // You iterate over each element in the variadic arguments using the va_args function.
        // The first argument is the va_list argument, and the second is the argument type.
        auto next_element = va_arg(args, int);
        result += next_element;
    }
    // Once you've completed iterating, you call va_list with the va_list structure.
    va_end(args);
    return result;
}

int main()
{
    // You invoke sum with seven arguments: the first is the number of variadic arguments (6), followed
    // by six numbers.
    printf("The answer is %d.", sum(6, 2, 4, 6, 8, 10, 12));
}

// variadic functions are a holdover from C. Generally, variadic functions are unsafe and a common source of security
// vulnerabilities.
