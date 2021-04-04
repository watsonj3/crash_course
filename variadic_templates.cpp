//
// Created by jwats on 4/3/2021.
//

// way better version than the variadic function in variadic_function.cpp
#include <cstdio>

// These two template functions can be comp
// overload that handles the stopping condition. If the function has only a single argument, you simply return
template <typename T>
constexpr T sum(T x) {
    return x;
}

// use recursive call. It peels a single argument x off the parameter pack args and then returns x
// plus the result of the recursive call to sum with the expanded parameter pack.
template <typename T, typename...Args>
constexpr T sum(T x, Args... args) {
    return x + sum(args...);
}

int main() {
    printf("The answer is %d.", sum(2, 4, 6, 8, 10, 12));
}