//
// Created by jwats on 8/3/2021.
//

// Constant expressions are expressions that can be evaluated at compile time. For performance and safety reasons,
// whenever a computation can be done at compile time rather than runtime, you should do it.
// You can extend the reach of the compiler by using the expression constexpr. Whenever all the information required
// to compute an expression is present at compile time, the compiler is compelled to do so if that expression is marked
// constexpr.

// Both const and constexpr are closely related. Whereas constexpr enforces that an expression is compile time evaluable,
// const enforces that a variable cannot change within some scope (at runtime). All constexpr expressions are const because
// they're always fixed at runtime.
// constexpr expressions are more robust and easier to understand, because you can eliminate so-called magic values --
// manually calculated constants copy and pasted directly into source code.

#include <cstdint>

// Here, Color objects are encoded using the hue-saturation-value (HSV) representation:
struct Color {
    float H, S, V;
};

constexpr uint8_t  max(uint8_t a, uint8_t b)
{
    return a > b ? a : b;
}

constexpr uint8_t max(uint8_t a, uint8_t b, uint8_t c)
{
    return max(max(a,b), max(a,c));
}

constexpr uint8_t min(uint8_t a, uint8_t b)
{
    return a < b ? a : b;
}

constexpr uint8_t min(uint8_t a, uint8_t b, uint8_t c)
{
    return min(min(a, b), min(a, c));
}

constexpr float modulo(float dividend, float divisor)
{
    const auto quotient = dividend / divisor;
    return divisor * (quotient - static_cast<uint8_t>(quotient));
}

// Suppose you want to instantiate Color objects using red-green-blue (RGB) representations. You could use a converter to
// calculate the RGB to HSV manually, but you can use constexpr to eliminate magic values.

constexpr Color rgb_to_hsv(uint8_t r, uint8_t g, uint8_t b)
{
    Color c{};
    const auto c_max = max(r, g, b);
    c.V = c_max / 255.0f;

    const auto c_min = min(r, g, b);
    const auto delta = c.V - c_min / 255.0f;
    c.S = c_max == 0 ?  0 : delta / c.V;

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

// There's quite a bit going on, but it's all computed at compile time. The compiler initializes a Color with all of the
// HSV field floats filled in.

int main()
{
    auto black = rgb_to_hsv(0, 0, 0);
    auto white = rgb_to_hsv(255, 255, 255);
    auto red = rgb_to_hsv(255, 0, 0);
    auto green = rgb_to_hsv(0, 255, 0);
    auto blue = rgb_to_hsv(0, 0, 255);
}

// You've told the compiler that each of these color values is compile-time evaluable. The compiler can decide whether or not
// to evaluate them at compile time or runtime. The upshot is that the compiler can usually emit instructions with
// hardcoded magic numbers corresponding to the correct HSV values for each Color.