//
// Created by jwats on 4/2/2021.
//

// Attributes
// Attributes apply implementation-defined features to an expression statement.
// You introduce attributes using double brackets [[]], containing a list of one or more
// comma-separated attribute elements
// situations where one would use attributes are rare, but they convey useful information to the compiler nonetheless.

// demonstrates use of [[no return]] attribute

#include <cstdio>
#include <stdexcept>

// just throws an exception. Because you always throw an exception, pitcher never returns.
// the noreturn attribute is not necessary, i.e. it works without it.
// Giving this information to the compiler allows it to reason more completely on your code, and
// optimize your program.
[[noreturn]] void pitcher()
{
    throw std::runtime_error{"Knuckleball."};
}

int main()
{
    try
    {
        //invoke pitcher and handle the caught exception.
        pitcher();
    } catch(const std::exception& e)
    {
        printf("exception: %s\n", e.what());
    }
}