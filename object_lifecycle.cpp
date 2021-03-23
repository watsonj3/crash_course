//
// Created by jmwat on 3/22/2021.
//

#include <cstdio>

// static variable because it's declared at global scope.
// Can be accessed from any function in the translation unit
// a translation unit is what a preprocessor produces after acting on a single source file
//static int rat_things_power = 200;

void power_up_rat_thing(int nuclear_isotopes)
{
    // Because rat_things_power is a static variable, i.e. it's lifetime is the
    // program's lifetime, each time you call power_up_rat_thing, the value of rat_things_power
    // carries over into the next call
    static int rat_things_power = 200;
    rat_things_power = rat_things_power + nuclear_isotopes;
    printf("rat_things_power, %d\n", rat_things_power);
    // waste_heat storage duration begins when power_up_rat_thing is called and ends when
    // power_up_rat_thing returns, so its values aren't saved between function calls.
    const auto waste_heat = rat_things_power * 20;
    if (waste_heat > 10000)
    {
        printf("Warning! Hotdoggie!\n");
    }
}

int main()
{
    //printf("Rat-thing power: %d\n", rat_things_power);
    power_up_rat_thing(100);
    //printf("Rat-thing power: %d\n", rat_things_power);
    power_up_rat_thing(500);
    //printf("Rat-thing power: %d\n", rat_things_power);


    int* my_int_array_ptr = new int[100];

    delete[] my_int_array_ptr;
}
