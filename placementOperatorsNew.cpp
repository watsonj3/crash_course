//
// Created by jwats on 8/3/2021.
//

// Sometimes, you don't want to override all free store allocations. Instead, you can use the placement operators, which
// perform the appropriate initialization on preallocated memory:
/*
 * void* operator new(size_t, void*)
 * void operator delete(size_t, void*)
 * void* operator new[](void*, void*)
 * void operator delete[](void*, void*)
 */

// You can manually construct objects in arbitrary memory.  This allows you to manually manipulate an object's lifetime.
// However, you cannot use delete to release the resulting dynamic objects.  You must call the object's destructor directly
// (and exactly once).

#include <cstdio>
#include <cstddef>
#include <new>

struct Point
{
    Point() : x{}, y{}, z{}
    {
        // The constructor prints a message indicating that a Point at a particular address was constructed.
        printf("Point at %p constructed.\n", this);
    }
    ~Point()
    {
        // The destructor prints a message indicating that the Point is getting destructed.
        printf("Point at %p destructed.\n", this);
    }
    double x, y, z;
};

int main()
{
    const auto point_size = sizeof(Point);
    std::byte data[3 * point_size];
    // print the address of data, which is the first address where placement new initializes a Point.
    printf("Data starts at %p.\n", data);
    // Each placement of new has allocated the Point within the memory occupied by the data array.
    auto point1 = new(&data[0 * point_size]) Point{};
    auto point2 = new(&data[1 * point_size]) Point{};
    auto point3 = new(&data[2 * point_size]) Point{};
    // You must then invoke each destructor individually.
    point1->~Point();
    point2->~Point();
    point3->~Point();
}

