//
// Created by jwats on 4/1/2021.
//

// Constant expressions can be evaluated at compile time.
// This should be preferred over runtime, for performance and safety reasons.

// constexpr extends the reach of the compiler.
// Both const and constexpr are related. Whereas constexpr enforces than an expression is compile time evaluable,
// const enforces that a variable cannot change within some scope (at runtime).
// All constexpr expressions are const because they're always fixed at runtime.

#include <cstdint>

// Example program where some library you're using for your project uses Color objects that are encoded using
// the hue-saturation-value (HSV) representation

struct Color
{
    float H, S, V;
};

// You want to instantiate Color objects using red-green-blue (RGB) representations.
// You can use constexpr to eliminate magic values.

// each of these functions must be evaluable at compile time.
// use ternary operator to return value of the argument that is greatest
constexpr uint8_t max(uint8_t a, uint8_t b)
{
    return a > b ? a : b;
}
// use transitive property of comparison; by evaluating the two-argument max for the pairs a, b, and a, c,
// you can find the max of this intermediate result to find the overall max.
constexpr uint8_t max(uint8_t a, uint8_t b, uint8_t c)
{
    return max(max(a, b), max(a, c));
}

// same as above but the comparison is flipped.
constexpr uint8_t min(uint8_t a, uint8_t b)
{
    return a < b ? a : b;
}

constexpr uint8_t min(uint8_t a, uint8_t b, uint8_t c)
{
    return min(min(a, b), min(a, c));
}

// quick and dirty constexpr version of the C function fmod, which computes the floating-point remainder of dividing
// the first argument (dividend) by the second argument (divisor).
// fmod is not constexpr, so you have to build your own.
constexpr float modulo(float dividend, float divisor)
{
    const auto quotient = dividend / divisor;
    // subtract the integral part of quotient using a static_cast and a substraction
    // then multiply the decimal portion of the quotient by divisor.
    return divisor * (quotient - static_cast<uint8_t>(quotient));
}

constexpr Color rgb_to_hsv(uint8_t r, uint8_t g, uint8_t b)
{
    // declare and initialize Color c, which will get returned by rgb_to_hsv.
    Color c{};
    const auto c_max = max(r, g, b);
    // value of the Color, V, is computed here by scaling the maximum value of r, g, and b.
    c.V = c_max / 255.0f;

    const auto c_min = min(r, g, b);
    const auto delta = c.V - c_min / 255.0f;
    // the saturation s is calculated by computing the distance between the minimum and maximum RGB values
    // and scaling by v.
    c.S = c_max == 0 ? 0 : delta /c.V;

    if (c_max == c_min)
    {
        c.H = 0;
        return c;
    }

    if (c_max == r)
    {
        c.H = (g / 255.0f - b / 255.0f) / delta;
    }
    else if (c_max == g)
    {
        c.H = (b / 255.0f - r / 255.0f) / delta + 2.0f;
    }
    else if (c_max == b)
    {
        c.H = (r / 255.0f - g / 255.0f) / delta + 4.0f;
    }
    c.H *= 60.0f;
    c.H = c.H >= 0.0f ? c.H : c.H + 360.0f;
    c.H = modulo(c.H, 360.0f);
    return c;
}

int main()
{
    auto black = rgb_to_hsv(0,0,0);
    auto white = rgb_to_hsv(255,255,255);
    auto red = rgb_to_hsv(255, 0, 0);
    auto green = rgb_to_hsv(0, 255, 0);
    auto blue = rgb_to_hsv(0, 0, 255);
}