//
// Created by jwats on 8/3/2021.
//

// The new operator
// By default, operator new will allocate memory on the free store to make space for your dynamic objects.
// The free store, or heap, is an implementation-defined storage location. On OS, the kernel usually manages the free
// store (HeapAlloc on Windows and malloc on Linux and macOS).

// You can overload the free store operations and take control over allocations by overloading the new operator.

// The <new> header contains the following four operators
/*
 * void* operator new(size_t)
 * void operator delete(void*)
 * void* operator new[](size_t)
 * void operator delete[](void*)
 */

// The return type of operator new is void*. The free store operators deal in raw, uninitialized memory.
// It is possible to provide your own versions of these four operators.

// To avoid memory fragmentation, you can chop allocated memory into so-called buckets of a fixed size.
// When you request memory, the environment allocates a whole bucket, even if you didn't request all of the memory.
// Windows provides two functions for allocating dynamic memory: VirtualAllocEx and HeapAlloc.
// VirtualAllocEx is low level, and provides you with many options, such as which process to allocate memory into, the
// preferred memory address, the requested size, and permissions, like whether the memory should be readable, writable,
// and executable.  This function will never allocate fewer than 4096 bytes (a page).

// HeapAlloc is a higher-level function that hands out less than a page of memory when it can; otherwise, it will invoke
// VirtualAllocEx on your behalf. With Visual Studio compiler, new will call HeapAlloc by default.
// This arrangement prevents memory fragmentation in exchange for some overhead assocated with rounding up allocations
// to bucket size. Modern OS, such as Windows, will have fairly complex schemes for allocating memory of different sizes.
// You don't see this complexity unless you want to take control.

// The following program implements a simple Bucket and Heap class.

#include <cstddef>
#include <new>
#include <cstdio>

// Bucket class is responsible for taking up space in memory. As an homage to the Windows heap manager, the bucket
// size is hardcoded to 4096. All of the management logic goes into the heap class.
struct Bucket
{
    const static size_t data_size{ 4096 };
    std::byte data[data_size];
};

struct Heap {

    // allocate first checks whether the number of bytes requested is greater than the bucket size. If it is, it throws
    // a std::bad_alloc exception. Then, Heap iterates through the buckets looking for one that isn't marked true in
    // bucket_used. If it finds one, it returns the data member pointer for the associated Bucket.
    void* allocate(size_t bytes)
    {
        if (bytes > Bucket::data_size) throw std::bad_alloc{};
        for (size_t i{}; i < n_heap_buckets; i++)
        {
            if (!bucket_used[i])
            {
                bucket_used[i] = true;
                return buckets[i].data;
            }
        }
        throw std::bad_alloc{};
    }

    void free(void* p)
    {
        for (size_t i{}; i < n_heap_buckets; i++)
        {
            if (buckets[i].data == p)
            {
                bucket_used[i] = false;
                return;
            }
        }
    }

    static const size_t n_heap_buckets{ 10 };
    // The buckets member houses all the Buckets, neatly packed into a contiguous string.
    Bucket buckets[n_heap_buckets]{};
    // bucket_used member is a relatively tiny array containing objects of type bool that keeps track of whether a
    // Bucket in buckets with the same index has been loaned out yet. Both members are initialized to zero.
    bool bucket_used[n_heap_buckets]{};
};

// One way to allocate a Heap is to declare it at namespace scope so it has static storage duration.  Because its lifetime
// begins when the program starts, you can use it inside the operator new and operator delete overrides.

Heap heap;
void* operator new(size_t n_bytes)
{
    return heap.allocate(n_bytes);
}

void operator delete(void* p)
{
    return heap.free(p);
}

int main()
{
    // print the memory address of the first buckets element of the heap.
    // This is the memory location loaned out to the first new invocation.
    printf("Buckets:    %p\n", heap.buckets);
    auto breakfast = new unsigned int { 0xC0FFEE };
    auto dinner = new unsigned int { 0xDEADBEEF };
    // double check that the memory address is the same as the first bucket in the heap
    printf("Breakfast: %p 0x%x\n", breakfast, *breakfast);
    // print out the next memory address, which coincides with the 4096 byte length of a Bucket.
    printf("Dinner:    %p 0x%x\n", dinner, *dinner);
    // delete both buckets
    delete breakfast;
    delete dinner;
    // then allocate char objects with reckless abandon until a std::bad_alloc is thrown in when heap runs out of memory
    // This is the exact same number of buckets allocated in Heap::n_heap_buckets.
    // For each char allocated, you've taken up 4096 bytes of memory.
    try
    {
        while (true)
        {
            new char;
            printf("Allocated a char.\n");
        }
    }
    catch (const std::bad_alloc&)
    {
        printf("std::bad_alloc caught.\n");
    }
}


