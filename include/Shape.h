#ifndef SHAPE_H
#define SHAPE_H
#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include <cmath>
#include <Vec2.h>
#include <vector>
class Shape
{
public:
    Vec2 pos;
    Vec2 velocity;
    Vec2 acceleration;
    Vec2 pos0;
    Vec2 velocity0;
    Vec2 acceleration0;
    bool alive = true;
    float radius;
    int sides;
    float r, g, b;
    float mass;
    char tag;
    std::vector<Vec2> trail;
    Shape(Vec2 p, Vec2 v, float m, float r, char tag);
    void draw();
    void updateGravity(const Shape &shape);
    void updateTrail();
    void drawTrail();
    void drawArrow();
    void drawHead(float r, float g, float b, Vec2 arrow, Vec2 vector);
    void reset();
};
#endif