//
// Created by jwats on 4/1/2021.
//

// implicit and explicit conversion types

#include <cstdint>
#include <cstdio>
#include <limits>

// implicitly converts to void*
void print_addr(void* x)
{
    printf("0x%p\n", x);
}

// user-defined type conversion function
// implicit conversions can cause surprising behavior. Use explicit conversions instead.
// You can achieve explicit conversions with the explicit keyword.
// explicit constructors instruct the compiler not to consider the constructor as a means for implicit conversion
struct ReadOnlyInt
{
    ReadOnlyInt(int val) : val{val} {}
    // operator int method defines the user-defined type conversion from a ReadOnlyInt to an int.
    // You can use ReadOnlyInt types just like regular int types thanks to implicit conversion
    explicit operator int() const
    {
        return val;
    }
private:
    const int val;
};

int main()
{
    // Here, we are implicitly casting an integer that is too big to fit in an 8-bit integer
    // This is 511, or 9 bits of ones, into signed and unsigned ints.
    // value of x is guaranteed to be 255, while value of y is implementation dependent.
    // On a Windows 10 x64 machine, y is -1. This can be avoided using braced initialization.
    uint8_t x = 0b111111111;  // 255
    int8_t y = 0b111111111;
    printf("x: %u\ny: %d\n", x, y);

    // floating point to floating point conversions.
    // this demonstrates undefined behavior

    // safe implicit conversion from float to double
    double a = std::numeric_limits<float>::max();
    // safe implicit conversion from double to long double
    long double b = std::numeric_limits<double>::max();
    // unsafe. assigning maximum value of a long double to a float. Undefined behavior.
    float c = std::numeric_limits<long double>::max();
    printf("a: %g\nb: %Lg\nc: %g\n", a, b, c);

    // conversion to bool
    // pointers, integers, and floating point number5s can all be implicitly converted to bool objects.
    // if the value is nonzero, the result of implicit conversion is true. Otherwise, the result is false.
    // The value of int{1} is true, and value of int{} is false

    int d{};
    // refers to the address of d
    print_addr(&d);
    // prints 0
    print_addr(nullptr);

    // Explicit type conversion are called casts. Using {} initialization is type safe and non-narrowing
    int32_t f = 100;
    // braced initialization to build int64 from int32. Guaranteed to not lose any information.
    int64_t g{f};
    // according to operator==, the origin equals the results
    if (f == g)
    {
        printf("Non-narrowing conversion!\n");
    }
    // This won't be allowed and compiler will generate an error
    //int32_t h{b};

    // C-Style casts
    // These are more dangerous than the named casts.

    ReadOnlyInt the_answer{42};
    // explicitly cast a ReadOnlyInt to an int using static_cast
    auto ten_answers = static_cast<int>(the_answer) * 10;   // int value 420


}