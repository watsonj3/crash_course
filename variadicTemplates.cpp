//
// Created by jwats on 8/5/2021.
//

// Variadic templates allows you to create function templates that accept variadic, same-typed arguments.
// You add a special template parameter called a template parameter pack.

// The template parameter pack is part of the template parameter list.  When you use Args within the function template,
// it's called a function parameter pack. You can use sizeof...(args) to obtain the parameter pack's size.

// Unfortunately, it's not possible to index into a parameter pack directly.  You must invoke the function template
// within itself -- called compile-time recursion -- to recursively iterate over the elements in a parameter pack.
// Here is the same sum function used before in variadicFunctions.cpp, but with variadic templates.

#include <cstdio>

// This first function is the overload that handles the stopping condition; if the function has only a single argument,
// you simply return the argument x, because the sum of a single element is just the element.
template <typename T>
constexpr T sum(T x)
{
    return x;
}

// The variadic template follows a recursion pattern.  It peels a single argument x off the parameter pack args and then
// returns x plus the result of the recursive call to sum with the expanded parameter pack.
// Because all of this generic programming can be computed at compile time, you mark these functions constexpr.
// This is a major advantage over using variadic Functions, which has identical output but computes the result at runtime.
template <typename T, typename... Args>
constexpr T sum(T x, Args... args)
{
    return x + sum(args...);
}

// Fold expressions
// A fold expression computes the result of using a binary operator over all the arguments of a parameter pack.

template <typename... T>
constexpr auto foldSum(T...args)
{
    return (...+ args);
}

int main()
{
    printf("The answer is %d.\n", sum(2, 4, 6, 8, 10, 12));
    printf("The answer of the fold expression is %d.", foldSum(2, 4, 6, 8, 10, 12));
}
