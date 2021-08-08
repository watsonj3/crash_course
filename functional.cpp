//
// Created by jwats on 8/6/2021.
//

// The std::function class template from the <functional> header is a polymorphic wrapper around a callable object.
// Meaning, it's a generic function pointer.  You can store a static function, a function object, or a lambda into a std::function
// With functions, you can:
/*
 * Invoke without the caller knowing the function's implementation
 * assign, move, and copy
 * have an empty state, similar to a nullptr.
 */

// To declare a function, you much provide a single template parameter containing the function prototype of the callable object.
// std::function<return-type(arg-type-1, arg-type-2, etc.)>
// The std::function class template has a number of constructors. The default constructor constructs a std::function in empty mode,
// meaning it contains no callable object.

#include <cstdio>
#include <functional>


void static_func()
{
    printf("A static function.\n");
}

int main()
{
    // the template parameter void() denotes a function taking no arguments and returning void.
    // Because you didn't fill func with a callable object, it's in an empty state.
    std::function<void()> func;
    try
    {
        func();
    }
    catch(const std::bad_function_call& e)
    {
        // When you invoke func, it throws a std::bad_function_call, which is caught and printed.
        printf("Exception: %s", e.what());
    }

    // This template parameter indicates that a callable object contained by newFunc takes no arguments and returns void.
    // You initialize newFunc with a lambda that prints the message A lambda.
    std::function<void()> newFunc { [] {printf("A lambda.\n"); }};
    // invoke newFunc, which prints A lambda.
    newFunc();
    // next, assign static_func to newFunc, which replaces the lambda that was originally assigned upon construction.
    newFunc = static_func;
    newFunc();
}