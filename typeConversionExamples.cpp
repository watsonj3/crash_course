//
// Created by jwats on 8/3/2021.
//
#include <cstdint>
#include <cstdio>
#include <limits>

// implicitly convert a pointer to void*
void print_addr(void* x)
{
    printf("0x%p\n", x);
}

void trainwreck(const char* read_only)
{
    // Modern operating systems enforce memory access patterns.  This function attempts to write into the memory storing
    // the string literal Ezra.  This accidentally gets rid of the const qualifier on read_only.
    auto as_unsigned = (unsigned char*) read_only;
    *as_unsigned = 'b'; // Crashes on Windows 10 x64
}

void newTrainWreck(const char* read_only)
{
    // Trying this with reinterpret_cast, the compiler would generate an error. In this case, the IDE also generates an error.
    //auto as_unsigned = reinterpret_cast<unsigned char*>(read_only);
    //*as_unsigned = 'b';
}

// Sometimes, implicit conversions can cause surprising behavior. With user-defined types, you should always use explicit
// conversions with th explicit keyword. Explicit constructors instruct the comppiler not to consider the constructor as a
// means for implicit conversion.

struct ReadOnlyInt
{
    ReadOnlyInt(int val) : val{ val } {}
    explicit operator int() const {
        return val;
    }
private:
    const int val;
};

int main()
{
    //Implicit type conversions occur anywhere a particular type is called for but you provide a different type.

    //auto x = 2.718281828485943030339498L;
    //uint8_t y = x;  // silent truncation

    // integers can be converted into other integer types. If the destination type is signed, then all is well, as long
    // as the value can be represented.
    // If the destination type is unsigned, the result is as many bits as can fit into the type. The high-order bits are lost.

    // 0b11111111 = 511
    uint8_t x = 0b111111111; // 255
    int8_t y = 0b111111111; // implementation defined
    printf("x: %u\ny: %d", x, y);

    // the above implicitly casts an integer that is too big to fit in an 8-bit integer (511 or 9 bits of 1)
    // On a Windows 10 x64 machine, y equals -1.
    // The above can be avoided using the braced initialization syntax.
    double a = std::numeric_limits<float>::max();
    long double b = std::numeric_limits<double>::max();
    float c = std::numeric_limits<long double>::max();
    printf("a: %g\nb: %Lg\nc: %g", a, b, c);
    // this results in c being undefined behavior as you cannot fit a long double into a float

    // Pointers, integers, and floating-point numbers can all be implicitly converted to bool objects. If the value is
    // nonzero, the result of implicit conversion is true. Otherwise, the result is false.

    // Pointers can be implicitly converted to void*.
    int d{};
    print_addr(&d);
    print_addr((nullptr));

    // Explicit type conversions

    // These are called casts. Braced initialization {} is used for explicit type conversions. This is type safe
    // and non-narrowing. This ensures that at compile time, that only safe, well-behaved, non-narrowing conversions are
    // allowed.

    int32_t e = 100;
    int64_t f{ e };
    if (e == f) printf("Non-narrowing conversion!");

    // named conversion functions allow you to perform dangerous casts that braced initialization won't permit.
    // You can also perform C-style casts, but this is mainly to maintain some compatibility between the languages.
    // (desired-type)object-to-cast
    // For each C-style cast, there exists some incantation of static_casts, const_casts, and reinterpret_casts, that would
    // achieve the desired type conversion. C-style casts are far more dangerous than the named casts.

    // The syntax of C++ explicit casts is intentionally ugly and verbose. Rules are being bent and broken.
    // C-style casts don't do this.
    // When using finer instruments like the named casts, the compile can at least enforce some constraints.

    // See the ReadOnlyInt struct above.
    // Now you must explicitly cast a ReadOnlyInt to an int using static_cast:

    ReadOnlyInt the_answer{ 42 };
    auto ten_answers = static_cast<int>(the_answer) * 10;
}
