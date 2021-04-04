//
// Created by jwats on 4/3/2021.
//

// You can pass a function as a parameter to another function
// One way to do this is to pass a function pointer.

// Functions occupy memory, just like objects. You can refer to this memory address via usual pointer mechanisms.
// Unlike objects, you cannot modify the pointed-to function.
// You can take the address of functions and invoke them. Nothing else.

#include <cstdio>

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
    const float first{100};
    const int second{20};

    // Initialize a function pointer operation accepting a float and an int as arguments and returning a float.
    float (*operation)(float, int) {};
    // print the value of operation, which is nullptr, after initialization
    printf("operation initialized to 0x%p\n", operation);

    // assign the address of add to operation, using the address-of operator and print out it's new address.
    operation = &add;
    printf("&add = 0x%p\n", operation);
    printf("%g + %d = %g\n", first, second, operation(first, second));

    // reassign operation to subtract without using address of operator, print the new value of operation.
    operation = subtract;
    printf("&subtract = 0x%p\n", operation);
    printf("%g - %d = %g\n", first, second, operation(first, second));
}