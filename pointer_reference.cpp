//
// Created by jmwat on 3/22/2021.
//

#include <cstdio>

struct College
{
    char name[256];
};

void print_name(College* college_ptr)
{
    printf("%s College\n", college_ptr->name);
}

int main()
{
    int gettysburg{};
    printf("gettysburg: %d\n", gettysburg);
    int *gettysburg_address = &gettysburg;
    *gettysburg_address = 17325;
    printf("&gettysburg: %p\n", gettysburg_address);
    printf("value in gettysburg: %d\n", *gettysburg_address);
    printf("value in gettysburg: %d\n", gettysburg);

    College best_colleges[] = {"Magdalen", "Nuffield", "Kellogg"};
    print_name(best_colleges);

}
