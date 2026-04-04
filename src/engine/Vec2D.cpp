#include <vector>
#include <iostream>


class Vec2D {
public:
    double x, y;

    Vec2D(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}

    Vec2D operator+(const Vec2D& other) const { return Vec2D(x + other.x, y + other.y); }
    Vec2D operator-(const Vec2D& other) const { return Vec2D(x - other.x, y - other.y); }
    Vec2D operator*(double scalar) const { return Vec2D(x * scalar, y * scalar); }
    double operator[](int index) const { 
        if(index == 0) {
            return x;
        }
        if(index == 1) {
            return y;
        }
        else {
            std::cerr << "Error: incorrect index." << std::endl;
            return 0;
        }
    };
    double square(const Vec2D& other) const { return x * other.x + y * other.y; }
    double norm() const { return std::sqrt(square(*this)); }
    Vec2D normalized() const { 
        double n = norm();
        if (n > 0) {
            return *this * (1.0 / n);
        } 
        return *this;
    }
};