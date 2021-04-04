//
// Created by jwats on 4/2/2021.
//

#include <cstdio>
#include <cstdint>

// takes an 8 bit, unsigned integer by reference.
// This function doubles the argument and checks whether this causes an overflow.
// If it causes an overflow, returns true. Return false if no overflow occurs.
bool double_return_overflow(uint8_t& x)
{
    const auto original = x;
    x *= 2;
    return original > x;
}

// implements a FibonacciRange, which will generate an arbitrarily long sequence of Fibonacci
// numbers. This range must offer a begin and an end method that returns an iterator.
// This iterator, which is called FibonacciIterator in thsi example, must off operator!=, operator++, and operator*.

struct FibonacciIterator
{
    // operator != checks whether the argument is greater than or equal to current.
    // This operator is used within the range-based for loop in the conditional expression.
    // It should return true if elements remain in the range; otherwise, it returns false.
    bool operator!=(int x) const
    {
        return x >= current;
    }

    // operator ++ appears in the iteration expression and is responsible for setting up the iterator for
    // the next iteration.
    FibonacciIterator& operator++()
    {
        // You first save current value into the temporary var tmp.
        const auto tmp = current;
        // increment current by last, yielding next fibonacci number
        current += last;
        // set last equal to tmp
        last = tmp;
        // return a reference to this
        return *this;
    }
    // operator * returns current directly
    int operator*() const
    {
        return current;
    }

private:
    int current{1}, last{1};
};


struct FibonacciRange
{
    // constructor takes a max argument that defines an upper limit for the range.
    explicit FibonacciRange(int max) : max{max} {}
    // The begin method returns a fresh FibonacciIterator.
    FibonacciIterator begin() const
    {
        return FibonacciIterator{};
    }
    int end() const
    {
        return max;
    }

private:
    const int max;
};

int main()
{
    uint8_t x{1};
    printf("uint8_t:\n===\n");
    // this has a side effect of doubling x, because I've passed it by reference.
    while (!double_return_overflow(x))
    {
        printf("%u ", x);
    }

    // ranged-based for loop
    // The range-based for loop iterates over a range of values without needing an index variable.
    // A range (or range expression) is an object that the range-based for loop knows how to iterate over.
    // Many C++ objects are valid range expressions, including arrays. (All of the stdlib containers are included.)
    const int a[] {1, 1, 2, 3, 5, 8};
    // you declare the element variable to hold each element of the range.
    for (const auto element : a)
    {
        printf("%d ", element);
    }

    for (const auto i : FibonacciRange(5000))
    {
        printf("%d ", i);
    }
    // this does the same without using range-based for loop.
    FibonacciRange range{5000};
    const auto end = range.end();
    for (const auto b = range.begin(); b != end; ++b)
    {
        const auto i = *b;
        printf("%d ", i);
    }

}