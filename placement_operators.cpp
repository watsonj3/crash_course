//
// Created by jwats on 3/26/2021.
//

// Use placement operators to manually construct objects in arbitrary memory.
// This allows one to manually manipulate an object's lifetime.
// You cannot use delete to release dynamic objects though! You must call the objects destructor.

#include <cstdio>
#include <cstddef>
#include <new>

struct Point
{
    Point() : x{}, y{}, z{}
    {
        // print indicating that a Point at a particular memory address was constructed
        printf("Point at %p constructed.\n", this);
    }
    ~Point()
    {
        // print the Point is getting destructed, including the memory address
        printf("Point at %p destructed.\n", this);
    }
    double x, y, z;
};

int main()
{
    const auto point_size = sizeof(Point);
    std::byte data[3 * point_size];
    // print the address of data, which is the first address where placement new initializes a Point
    printf("Data starts at %p.\n", data);
    // each new has allocated the Point within the memory occupied by your data array
    auto point1 = new(&data[0 * point_size]) Point{};
    auto point2 = new(&data[1 * point_size]) Point{};
    auto point3 = new(&data[2 * point_size]) Point{};
    // each destructor is then invoked individually
    point1->~Point();
    point2->~Point();
    point3->~Point();
}