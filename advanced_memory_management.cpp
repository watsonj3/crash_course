//
// Created by jwats on 3/24/2021.
//

// bucket and head classes to demonstrate allocating memory

#include <cstddef>
#include <new>
#include <cstdio>

// responsible for taking up space in memory
// it will allocate 4096 bytes, or a page in windows memory.
struct Bucket
{
    const static size_t data_size{4096};
    std::byte data[data_size];
};


struct Heap
{
    // first check whether the number of bytes requested is greater than the bucket size
    void* allocate(size_t bytes)
    {
        // first check whether the number of bytes is greater than the bucket size
        if (bytes > Bucket::data_size) throw std::bad_alloc{};
        // iterate through the buckets looking for 0one that isn't marked true in buckets used
        // if it finds an unused Bucket, then it returns data member pointer for the associated bucket.
        for (size_t i{}; i < n_heap_buckets; i++)
        {
            if (!bucket_used[i])
            {
                bucket_used[i] = true;
                return buckets[i].data;
            }
        }
        // throw an bad_alloc exception if it can't find an unused bucket.
        throw std::bad_alloc{};
    }
    // accepts a void* and iterates through all the buckets looking fora  matching data member pointer.
    // If it finds one, it sets bucket_used for the corresponding bucket to false and returns.
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

    static const size_t n_heap_buckets{10};
    // buckets member houses all the Buckets, packed into a contiguous string
    Bucket buckets[n_heap_buckets]{};
    // keeps track of whether a Bucket in buckets with the same index has been loaned out yet.
    bool bucket_used[n_heap_buckets];
};


Heap heap;

// Use n ew and delete for dynamic memory management. It will use heap instead of the default free store.
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
    // this location is loaned out the first new invocation.
    printf("Buckets:    %p\n", heap.buckets);
    auto breakfast = new unsigned int{0xC0FFEE};
    auto dinner = new unsigned int{0xDEADBEEF};
    // confirm the memory address of the first buckets element of the heap.
    printf("Breakfast: %p 0x%x\n", breakfast, *breakfast);
    // print the memory address of dinner. This is exactly 0x1000 greater than at breakfast, which is about the size
    // of a page.
    printf("Dinner:    %p 0x%x\n", dinner, *dinner);
    // delete breakfast and dinner to free up memory
    delete breakfast;
    delete dinner;
    // now allocate char's on the heap until the heap runs out of memory. Each char takes up about
    // 4096 bytes of memory!
    try {
        while (true)
        {
            new char;
            printf("Allocated a char.\n");
        }
    } catch (const std::bad_alloc&) {
        printf("std::bad_alloc caught.\n");
    }
}