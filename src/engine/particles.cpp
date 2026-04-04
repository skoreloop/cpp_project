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

class Particle {
public:

    double mass;         
    Vec2D position;       
    Vec2D velocity;       
    Vec2D force;          

    Particle(double m = 1.0, const Vec2D& pos = Vec2D(), const Vec2D& vel = Vec2D()) : mass(m), position(pos), velocity(vel), force() {}

    void WallCollision(double boxSize_x, double boxSize_y) {
        if (position.x < 0) {
            position.x = -position.x;          
            velocity.x = -velocity.x;          
        } else if (position.x > boxSize_x) {
            position.x = 2.0 * boxSize_x - position.x;
            velocity.x = -velocity.x;
        }

        if (position.y < 0) {
            position.y = -position.y;
            velocity.y = -velocity.y;
        } else if (position.y > boxSize_y) {
            position.y = 2.0 * boxSize_y - position.y;
            velocity.y = -velocity.y;
        }
    }

    void VelocityStep(double dt, const std::vector<Particle>& particles, double boxSize_x, double boxSize_y) {
        velocity = velocity + force * (dt / mass);
        position = position + velocity * dt;

        WallCollision(boxSize_x, boxSize_y);
    }
};