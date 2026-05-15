#ifndef VEC2D_HPP
#define VEC2D_HPP

#include <cmath>

class Vec2D {
public:
    double x, y;
    inline Vec2D(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
    
    inline Vec2D operator+(const Vec2D& other) const { return Vec2D(x + other.x, y + other.y); }
    inline Vec2D operator-(const Vec2D& other) const { return Vec2D(x - other.x, y - other.y); }
    inline Vec2D operator*(double scalar) const { return Vec2D(x * scalar, y * scalar); }
};

#endif