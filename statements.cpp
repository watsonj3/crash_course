//
// Created by jwats on 4/1/2021.
//

// expression statement is an expression followed by a semi-colon (;)
#include <cstdio>

struct Tracer
{
    Tracer(const char* name) : name{name}
    {
        printf("%s constructed.\n", name);
    }
    ~Tracer()
    {
        printf("%s destructed.\n", name);
    }
private:
    const char* const name;
};

// function declaration, or function signature or prototype, specifies a function's inputs and outputs.
// function declaration defines the function's interface.
// function is defined after main block
void randomize(uint32_t&);

// replace randomize with a RandomNumberGenerator class, which replaces randomize function with next.
struct RandomNumberGenerator
{
    // seed value, which is used to initialize the number member variable
    explicit RandomNumberGenerator(uint32_t seed) : iterations{}, number{seed} {}
    uint32_t next();
    size_t get_iterations() const;
private:
    size_t iterations;
    uint32_t number;
};

int main()
{
    int x{};
    // this expression statement has a side effect (incrementing x)
    ++x;
    // This expression statement has no use. It is still valid.
    42;
    // This is also an expression statement
    printf("The %d True Morty\n", x);

    // Compound statements, or blocks, are a sequence of statements enclosed by braces.
    // Compound statements are useful if you want multiple statements to execute, rathern than one.
    // Each block declares a new scope, which is called a block scope. Objects declared within a block scope
    // have lifetimes bound by the block.
    // Variables declared within a block get destroyed in a well-defined order: the reverse of the order in which they
    // were declared.

    // initialize Tracer called main. Next, generate 2 compound statements.
    // This shows how the two tracer objects get destructed once execution passes through Block a.
    // a1 and a2 are destructed in reverse order from their initialization.
    // once execution passes through the second block, block b, the scope of main ends and Tracer main destructs.
    Tracer main{"main"};
    {
        printf("Block a\n");
        Tracer a1{"a1"};
        Tracer a2{"a2"};
    }
    {
        printf("Block b\n");
        Tracer b1{"b1"};
        Tracer b2{"b2"};
    }

    // Declaration statements
    // Declaration statements introduce identifiers, such as functions, templates, and namespaces.

    // initialize a counter to 0
    size_t iterations{};
    uint32_t number{0x4c4347};
    while (number != 0x474343)
    {
        // invoke randomize and increment iterations
        // once number equals the then print the number of iterations
        randomize(number);
        ++iterations;
    }
    // there will be about a billion iterations to randomly draw the target value
    printf("%zu", iterations);

    RandomNumberGenerator rng{0x4c4347};
    while (rng.next() != 0x474343)
    {
        // Do nothing...
    }
    printf("%zu", rng.get_iterations());

}

// Functions that aren't member functions are called non-member functions, or free functions. They are declared
// outside of main at namespace scope.
// A function definition includes the function declaration as well as the function's body. Defines implementation.
// This is a linear congruential generator, a primitive way to generate random numbers.
void randomize(uint32_t& x)
{
    x = 0x3FFFFFFF & (0x41C64E6D * x + 12345) % 0x80000000;
}

// Shares the same return type as the declaration. The RandomNumberGenerator:: construct specifies that
// you're defining a method
uint32_t RandomNumberGenerator::next()
{
    ++iterations;
    number = 0x3FFFFFFF & (0x41C64E6D * number + 12345) % 0x80000000;
    return number;
}

size_t RandomNumberGenerator::get_iterations() const
{
    return iterations;
}