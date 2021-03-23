//
// Created by jmwat on 3/23/2021.
//

#include <cstdio>
#include <utility>

// function takes a lvalue reference
void ref_type(int &x)
{
    printf("lvalue reference %d\n", x);
}

// function takes a rvalue reference
void ref_type(int &&x)
{
    printf("rvalue reference %d\n", x);
}

int main()
{
    auto x = 1;
    // invoke lvalue reference function. x is a lvalue since it has a name.
    ref_type(x);
    // invoke rvalue reference function. 2 is an integer literal without a name.
    ref_type(2);
    // invoke rvalue reference function. x + 2 is not bound by a name.
    ref_type(x + 2);

    // move a lvalue reference to a rvalue reference using std::move from utility header.
    ref_type(std::move(x));
}