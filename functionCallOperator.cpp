//
// Created by jwats on 8/5/2021.
//

// It is possible to make user-defined types callable or invocable by overloading the function-call operator operator()().
// Such a type is called a function type, and instances of a function type are called function objects.
// The function-call operator permits any combination of argument types, return types, and modifiers.

// The function-call operator has the special operator() method name. You can declare an arbitrary number of arguments,
// and you can decide on the appropriate return type.
// When the compiler evaluates a function-call expression, it will invoke the function-call operator on the first operand,
// passing the remaining operands as arguments. The result of the function-call expression is the result of invoking the
// corresponding function-call operator.

#include <cstdio>
#include <cstdint>

struct CountIf
{
    // Initialize CountIf objects using a constructor taking a char. You can call the resulting function object
    // as if it were a function taking a null-terminated string argument.
    // The function call operator iterates through each character in the argument str using an index variable,
    // incrementing the result variable whenever the character matches the x field.
    // Because calling the function doesn't modify the state of a CountIf object, it is marked const.
    CountIf(char x) : x{ x } { }
    size_t operator()(const char* str) const
    {
        size_t index{}, result{};
        while (str[index])
        {
            if (str[index] == x) result++;
            index++;
        }
        return result;
    }
private:
    const char x;

};

int main()
{
    // s_counter is initialized, which counts the frequency of the letter s.
    // s_counter can be used as if it is a function
    CountIf s_counter{ 's' };
    auto sally = s_counter("Sally sells seashells by the seashore.");
    printf("Sally: %zu\n", sally);
    auto sailor = s_counter("Sailor went to sea to see what he could see.");
    printf("Sailor: %zu\n", sailor);
    // You can even initialize a CountIf object and use the function operator directly as an rvalue object.
    auto buffalo = CountIf{ 'f' }("Buffalo buffalo Buffalo buffalo "
                                   "buffalo buffalo Buffalo buffalo.");
    printf("Buffalo: %zu\n", buffalo);
}