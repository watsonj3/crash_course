//
// Created by jmwat on 3/23/2021.
//

// Template training and named conversion functions
// Named conversions are language features that explicitly convert one type into another type


#include <cstdio>
#include <stdexcept>
#include <cstddef>

// You can use X, Y, and Z as if they were any fully specified type, such as an int or user-defined class.
// with the exception of the first line, this class is completely similar to any other class.
// You can also build template functions the same way.
template <typename X, typename Y, typename Z>
struct MyTemplateClass {
    // foo method takes a Y reference and returns an X.
    X foo(Y&);
private:
    Z* member;
};


// const_cast
// shucks away the const modifier, allowing the modification of const values.
// example of using a const_cast function. The encased_solo parameter is const, so any attempt to modify it would
// result in a compile error.
void carbon_thaw(const int& encased_solo)
{
    //encased_solo++;       // compiler error since it's trying to modify a const
    // use const_cast to obtain a non-const reference hibernation_sick_solo.
    auto& hibernation_sick_solo = const_cast<int&>(encased_solo);
    // you are now free to modify the int pointed to by encased_solo via the new, non-const reference.
    hibernation_sick_solo++;
}

// static_cast
// reverses a well-defined implicit conversion, such as an integer type to another integer type.
// takes a void pointer argument and employs a static_cast to create a short pointer from this argument, increment
// the pointed-to short, and returns the result. The implicit conversion from short* to void* is well defined.
// attempting ill-defined conversions with static_cast will result in a compile error.
short increment_as_short(void* target)
{
    auto as_short = static_cast<short*>(target);
    *as_short = *as_short + 1;
    return *as_short;
}

// narrow_cast
// the following template performs a runtime check for narrowing. Narrowing is a loss in information. Think about
// converting from an int to a short. If the value of int fits into a short, then no narrowing will occur and the
// conversion is reversible. If the value of int is too big for the short, the result is narrowing and the result
// is not reversible.
// The following function checks for narrowing and throws a runtime error if it's detected
template <typename To, typename From>
To narrow_cast(From value)
{
    // first, you convert to the requested conversion
    const auto converted = static_cast<To>(value);
    // second, you reverse the conversion
    const auto backwards = static_cast<From>(converted);
    // if there is a narrowing, then throw runtime error. Otherwise, return converted.
    if (value != backwards) throw std::runtime_error("Narrowed!");
    return converted;
}

// mean: a template function example
// the following function will only work with doubles. If you want to change it to long, or int, then you would
// be required to change the return type, the argument type and result.
// In order to make this function work with any possible type, then you will need to use generic programming,
// a programming style where you program with yet-to-be-specified types. With C++, generic programming is using
// templates. Let's refactor mean into a template function.
/*double mean(const double* values, size_t length)
{
    double result{};
    for (size_t i{}; i<length; i++)
    {
        result += values[i];
    }
    return result / length;
}
*/
// mean refactored into template
// First we have a template prefix with a single template parameter, T.
// Next, update mean, replacing all double with T.
template<typename T>
T mean(const T* values, size_t length)
{
    T result{};
    for (size_t i{}; i<length; i++)
    {
        result += values[i];
    }
    return result / length;
}

// Simpleuniquepointer: a template class example
// A unique pointer is an RAII wrapper around a free-store allocated object. The unique pointer has a single owner
// at a time, so when a unique pointers lifetime ends, the pointed-to object gets destructed.

template <typename T>
struct SimpleUniquePointer
{
        // A default constructor, which will set the private member T* to nullptr
        SimpleUniquePointer() = default;
        // non-default constructor that takes a T* and sets the private member pointer
        SimpleUniquePointer(T* pointer) : pointer{pointer} {

        }
        // will delete if pointer is nullptr.
        ~SimpleUniquePointer() {
            if(pointer)
            {
                delete pointer;
            }
        }
        // you only want a single owner of the pointed-to object. This will delete the copy constructor and the
        // copy assignment operator. Prevents double-free issues that might arise.
        SimpleUniquePointer(const SimpleUniquePointer&) = delete;
        SimpleUniquePointer& operator=(const SimpleUniquePointer&) = delete;
        // The unique pointer is moveable with this move constructor. This steals the value of pointer from other
        // and sets the pointer of other to nullptr, handing responsibility of the pointed-to object to this.
        // Once the move constructor returns, the moved-from object is destroyed. Because the moved-from object's pointer
        // is set to nullptr, the destructor will not delete the pointed-to object.
        SimpleUniquePointer(SimpleUniquePointer&& other) noexcept : pointer{other.pointer}
        {
            other.pointer = nullptr;
        }
        // check explicitly for prior ownership. After check, perform operation of copy constructor. Set pointer to
        // the value of other.pointer, and then set other.pointer to nullptr. This ensures that the moved-from object
        // does not delete the pointed-to object.
        SimpleUniquePointer& operator=(SimpleUniquePointer&& other) noexcept
        {
            if(pointer)
            {
                delete pointer;
            }
            pointer = other.pointer;
            other.pointer = nullptr;
            return *this;
        }
        // get direct access to the underlying pointer
        T* get()
        {
            return pointer;
        }
private:
    T* pointer;
};

int main()
{
    short beast{665};
    auto mark_of_the_beast = increment_as_short(&beast);
    printf("%d is the mark_of_the_beast.", mark_of_the_beast);

    // this is ill-defined:
    //float on = 3.51666666666;
    //auto not_alright = static_cast<char*>(&on);

    // reinterpret_cast
    // sometimes in low-level programming, you must perform type conversions that are not well-defined. This is when
    // you need complete control over how to interpret memory. You must use caution with such control by ensuring the
    // correctness of these conversions.

    // suppose your embedded device keeps an unsigned long timer at memory address 0x1000. You could use reinterpret_cast
    // to read from the timer.
    // auto timer = reinterpret_cast<const unsigned long*>(0x1000);
    // printf("Timer is %lu.", *timer);
    // the above can be compiled, but expect a runtime crash unless 0x1000 is readable.
    // the compiler has no idea whether the memory at address 0x1000 is an unsigned long. You are taking responsibility
    // for this dangerous construction.

    int perfect{496};
    const auto perfect_short = narrow_cast<short>(perfect);
    printf("perfect_short: %d\n", perfect_short);
    try {
        int cyclic{142857};
        const auto cyclic_short = narrow_cast<short>(cyclic);
        printf("cyclic_short: %d\n", cyclic_short);
    } catch (const std::runtime_error& e) {
        printf("Exception: %s\n", e.what());
    }

    // examples of using the template mean function.
    const double nums_d[] = {1.0, 2.0, 3.0, 4.0};
    const auto result1 = mean<double>(nums_d, 4);
    printf("double: %f\n", result1);

    const float nums_f[] = {1.0f, 2.0f, 3.0f, 4.0f};
    const auto result2 = mean<float>(nums_f, 4);
    printf("float: %f\n", result2);

    const size_t nums_c[] = {1, 2, 3, 4};
    const auto result3 = mean<size_t>(nums_c, 4);
    printf("size_t: %zu\n", result3);

    // you can also omit the template parameters when invoking a template function. The process that the compiler
    // uses to determine the correct template parameters is called template type deduction.
    // Sometimes, the template arguments cannot be deduced, such as when the return type is a template argument.
    // It's best be careful when doing this.
    const int nums_i[] = {5, 6, 7, 8};
    const auto result4 = mean(nums_i, 4);
    printf("int: %d\n", result4);
}