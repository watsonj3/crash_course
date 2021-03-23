#include <cstdio>
#include <cstddef>

int main()
{
    unsigned long maximum = 0;
    unsigned long values[] = {10, 50, 20, 40, 0};
    for (unsigned long value : values)
    {
        if (value > maximum)
        {
            maximum = value;
        }
    }
    printf("The maximum value is %lu", maximum);

    short array[] = {104, 105, 32, 98, 105, 108, 108, 0};
    size_t n_elements = sizeof(array) / sizeof(short);
}
