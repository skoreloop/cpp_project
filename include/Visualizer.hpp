#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <optional>

// Простая структура для 2D вектора
struct Vec2D {
    double x, y;
    Vec2D(double x_val = 0, double y_val = 0) : x(x_val), y(y_val) {}
    Vec2D operator+(const Vec2D& other) const { return {x + other.x, y + other.y}; }
    Vec2D operator-(const Vec2D& other) const { return {x - other.x, y - other.y}; }
    Vec2D operator*(double scalar) const { return {x * scalar, y * scalar}; }
    Vec2D operator/(double scalar) const { return {x / scalar, y / scalar}; }
};

// Структура частицы для MD 
struct Particle {
    Vec2D position;
    Vec2D velocity;
    Vec2D force;
    double mass;
    float radius;

    Particle(double m, Vec2D pos, Vec2D vel, float r) 
        : position(pos), velocity(vel), force(0, 0), mass(m), radius(r) {}
};

class Visualizer {
public:
    Visualizer(unsigned int width, unsigned int height, const std::string& title);
    void render(const std::vector<Particle>& particles);
    void handleEvents();
    bool isOpen() const;

private:
    sf::RenderWindow window;
};

#endif