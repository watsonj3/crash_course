//
// Created by jwats on 8/5/2021.
//
#include <cstdio>

// final and override modifiers

// The final modifier indicates that a method cannot be overridden by a child class. It's effectively the opposite of virtual.
struct BostonCorbett
{
    virtual void shoot() final
    {
        printf("What a God we have...God avenged Abraham Lincoln");
    }
};

// You can also apply the final keyword to an entire class, disallowing that class from becoming a parent entirely
struct newBostonCorbett final
{
    void shoot()
    {
        printf("What a God we have...God avenged Abraham Lincoln");
    }
};

// Causes a compile error when you attempt to inherit from the parent class
//struct newBostonCorbettJunior : newBostonCorbett {};


// You attempt to override the shoot method.  This will cause a compile error.

struct BostonCorbettJunior : BostonCorbett
{
    // void shoot() override {} // Doesn't work as shoot is final
};

// Whenever you're using interface inheritance, you should mark implementing classes final because the modifier
// can encourage the compiler to perform an optimization called devirtualization. When virtual calls are devirtualized,
// the compiler eliminates the runtime overhead associated with a virtual call.

// volatile
// A volatile object's value can change at any time, so the compiler must treat all accesses to volatile objects
// as visible side effects for optimization purposes.  The volatile keyword indicates that a method can be invoked
// on volatile objects.  This is analogous to how const methods can be appliled to const objects.

struct Distillate
{
    // declare the apply method on the Distillate class volatile.
    int apply() volatile
    {
        return ++ applications;
    }
private:
    int applications {};
};

int main()
{
    // create a volatile Distillate called ethanol.
    // Because the apply method is volatile, you can still invoke it.
    // Had you not marked apply volatile, the compiler would emit an error when you attempted to invoke it.
    // Just like how you cannot invoke a non-const method on a const object.
    volatile Distillate ethanol;
    printf("%d Tequila\n", ethanol.apply());
    printf("%d Tequila\n", ethanol.apply());
    printf("%d Tequila\n", ethanol.apply());
    printf("Floor!");
}
