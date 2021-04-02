//
// Created by jwats on 4/2/2021.
//

#include <cstdio>
#include <stdexcept>

// same functionality as the narrow_cast template class in template_training.cpp
template <typename To, typename From>
To NarrowCaster const {
    To cast (From value)
    {
        const auto converted = static_cast<To>(value);
        const auto backwards = static_cast<From>(converted);
        if (value != backwards) throw std::runtime_error{"Narrowed!"};
        return converted;
    }
};

// declare a type alias short_caster that partially applies short as the To type to NarrowCast.
template <typename From>
using short_caster = NarrowCaster<short, From>;

int main()
{
    try {
        // declare a caster object of type short_caster<int>
        // The single template parameter in the short_caster type alias gets applied to the remining
        // type parameter from the type alias -- From.
        const short_caster<int> caster;
        const auto cyclic_short = caster.cast(142857);
        printf("cyclic_short: %d\n", cyclic_short);
    } catch (const std::runtime_error& e) {
        printf("Exception: %s\n", e.what());
    }
}