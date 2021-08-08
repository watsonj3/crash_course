//
// Created by jwats on 8/5/2021.
//

// Lambda expressions construct unnamed function objects. The function object implies the function type, resulting in a
// quick way to declare a function object on the fly.  Lambdas don't provide any additional functionality other than
// declaring function types the old-fashioned way.  But they're extremely convenient when you need to initialize a function
// object in only a single context.

// five components of a lambda expression
/*
 * captures: The member variables of the function object (that is, the partially applied parameters)
 * parameters: The arguments required to invoke the function object
 * body: The function object's code
 * specifier: Elements like constexpr, mutable, noexcept, and [[noreturn]]
 * return type: The type returned by the function object
 * [captures] (parameters) modifiers -> return-type {body}
 */
// only the captures and the body are required.

#include <cstdio>
#include <cstdint>

// The transform template function accepts four arguments: a function object fn, an in array and an out array, and the
// corresponding length of those arrays. Within transform, you invoke fn on each element of in and assign the result to
// the corresponding element of out.
// transform is a template function, allowing one to reuse it with any function object.
template <typename Fn>
void transform(Fn fn, const int* in, int* out, size_t length)
{
    for (size_t i{}; i<length; i++)
    {
        out[i] = fn(in[i]);
    }
}

int main()
{
    const size_t len{ 3 };
    // declare base array 1, 2, 3 that will be used as the in array. Also declare three uninitialized arrays a, b, and c,
    // which will be used as the out arrays.
    int base[]{ 1, 2, 3 }, a[len], b[len], c[len];
    // first call to transform passes a lambda ([](int x) { return 1; }) that always returns 1, and the result is stored in a.
    // the lambda does not need a name.
    transform([](int x) {return 1; }, base, a, len);
    // this call to transform simply returns its argument, and the result is stored into b.
    transform([](int x) {return x; }, base, b, len);
    // this call multiplies the argument by 10 and adds 5. The result is stored in c.
    transform([](int x) {return 10*x+5; }, base, c, len);
    // print the output into a matrix where each column illustrates the transform that was applied to the different lambdas
    // in each case.
    for (size_t i{}; i < len; i++)
    {
        printf("Element %zu: %d %d %d\n", i, a[i], b[i], c[i]);
    }
}