//
// Created by jwats on 4/2/2021.
//

#include <cstdio>


// a volatile object's value can change at any time, so the compiler must treat all accesses to
// volatile objects as visible side effects for optimization purposes.
// The volatile keyword indicates that a method can be invoked on volatile objects.
// This is analogous to how const methods can be applied to const objects.
// Together, these two keywords define a method's const/volatile qualification.
struct Distillate
{
    int apply() volatile {
        return ++applications;
    }

private:
    int applications{};
};

int main() {
    volatile Distillate ethanol;
    printf("%d Tequila\n", ethanol.apply());
    printf("%d Tequila\n", ethanol.apply());
    printf("%d Tequila\n", ethanol.apply());
    printf("Floor!");
}