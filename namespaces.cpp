//
// Created by jwats on 4/1/2021.
//
#include <cstdio>

// By default, all symbols you declare go into the global namespace.
// To place a symbol within a namespace other than the global namespace, you declare
// the symbol within a namespace block.

namespace BroopKidron13::Shaltanac
{
    // All symbols declared within this block
    // belong to the BroopKidron13::Shaltanac namespace
    enum class Color
    {
        Mauve,
        Pink,
        Russet
    };
}

// declare a type alias String that refers to a const char[260]
using String = const char[260];
// declare a ShaltanaColor type alias, which refers to BroopKidron13::Shaltanac::Color.
using ShaltanacColor = BroopKidron13::Shaltanac::Color;

int main()
{
    // You can use using directive within main to avoid having to type BroopKidron13::Shaltanac to use Color
    // a using directive imports a symbol into a block, or if you declar a using directive at namespace scope, into
    // the current namespace.
    using BroopKidron13::Shaltanac::Color;
    const auto shaltanac_grass = Color::Russet;
    if (shaltanac_grass == Color::Russet)
    {
        printf("The other Shaltanac's joopleberry shrub is always "
               "a more mauvey shade of pinky russet.");
    }

    const auto my_color{ShaltanacColor::Russet};
    String saying {
        "The other Shaltanac's joopleberry shrub is "
        "always a more mauvey shade of pinky russet."
    };
    if (my_color == ShaltanacColor::Russet)
    {
        printf("%s", saying);
    }
}