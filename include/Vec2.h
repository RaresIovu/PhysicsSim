#ifndef VEC2_H
#define VEC2_H
#include <cmath>
struct Vec2
{
    float x, y;

    Vec2() : x(0), y(0) {}
    Vec2(float x, float y) : x(x), y(y) {}
    Vec2 operator+(const Vec2 &other) const { return {x + other.x, y + other.y}; }
    Vec2 operator-(const Vec2 &other) const { return {x - other.x, y - other.y}; }
    Vec2 operator*(float s) const { return {x * s, y * s}; }
    float lenght() const { return {std::sqrt(x * x + y * y)}; }
    Vec2 normalize() const
    {
        float len = lenght();
        return len == 0 ? Vec2(0, 0) : Vec2(x / len, y / len);
    }
    float dot(const Vec2 &other) const
    {
        return x * other.x + y * other.y;
    }
};

inline float clamp(float val, float minVal, float maxVal)
{
    if (val < minVal)
        return minVal;
    if (val > maxVal)
        return maxVal;
    return val;
}
#endif