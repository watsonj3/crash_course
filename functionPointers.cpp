//
// Created by jwats on 8/5/2021.
//

// One of the major concepts in functional programming is to pass a function as a parameter to another function.
// One way to achieve this is to pass a function pointer.  Functions occupy memory, just like objects. You can refer
// to this memory address via usual pointer mechanisms.
// However, unlike objects, you cannot modify the pointed-to function. In this respect, functions are
// conceptually similar to const objects. You can take the address of functions and invoke them.

#include <cstdio>

// Here we have two functions with identical function signatures, add and subtract. Because the function signatures
// match, pointer types to these functions will also match.
float add(float a, int b)
{
    return a + b;
}

float subtract(float a, int b)
{
    return a - b;
}

int main()
{
    const float first{ 100 };
    const int second { 20 };

    // initialize a function pointer operation accepting a float and an int as arguments and returning a float.
    float(*operation)(float, int) {};
    // print the value of operation, which is nullptr, after initialization.
    printf("operation initialized to 0x%p\n", operation);

    // next, assign the address of add to operation using the address-of operator
    operation = &add;
    // print the address of add.
    printf("&add = 0x%p\n", operation);
    // invoke operation and then print the results
    printf("%g + %d = %g\n", first, second, operation(first, second));

    // reassign operation to subtract without using the address of operator.
    operation = subtract;
    printf("&subtract = 0x%p\n", operation);
    printf("%g - %d = %g\n", first, second, operation(first, second));
}