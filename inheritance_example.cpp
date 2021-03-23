//
// Created by jmwat on 3/23/2021.
//

#include <cstdio>

// a pure virtual method. You can only derive from this base class.
struct BaseClass {
    virtual ~BaseClass() = default;
};

struct DerivedClass : BaseClass {
    DerivedClass() {
        printf("DerivedClass() invoked.\n");
    }
    ~DerivedClass() {
        printf("~DerivedClass() invoked.\n");
    }
};

int main()
{
    printf("Constructing DerivedClass x.\n");
    // allocate and initialize a DerivedClass with new and set result to a Baseclass pointer.
    BaseClass* x{new DerivedClass{}};
    printf("Deleting x as a BaseClass*.\n");
    // delete pointer, the DerivedClass destructor gets invoked. The BaseClass destructor does not get invoked.
    // important to have virtual to denote a pure virtual function.
    delete x;
}