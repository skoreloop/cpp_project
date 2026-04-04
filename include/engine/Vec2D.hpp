#ifndef VEC2D_HPP
#define VEC2D_HPP

#include <cmath>
#include <iostream>

class Vec2D {
public:
    double x, y;
    Vec2D(double x_ = 0, double y_ = 0);
    Vec2D operator+(const Vec2D& other) const;
    Vec2D operator-(const Vec2D& other) const;
    Vec2D operator*(double scalar) const;
    double operator[](int index) const;
    double square(const Vec2D& other) const;
    double norm() const;
    Vec2D normalized() const;
};

#endif