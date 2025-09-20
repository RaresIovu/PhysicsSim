#define _USE_MATH_DEFINES
#include <Shape.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <Vec2.h>
#include <vector>
Shape::Shape(Vec2 p, Vec2 v, float m, float r, char tag)
    : pos(p), velocity(v), mass(m), radius(r), pos0(p), velocity0(v), tag(tag) {}
void Shape::draw()
{
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(pos.x, pos.y);
    for (int i = 0; i <= 100; ++i)
    {
        float angle = 2.0f * M_PI * i / 100;
        float x = pos.x + sin(angle) * radius;
        float y = pos.y + cos(angle) * radius;
        glVertex2f(x, y);
    }
    glEnd();
}
float epsilon = 10.0f;
float minDistance = 40.0f;
void Shape::updateGravity(const Shape &shape)
{
    Vec2 delta = shape.pos - pos;
    Vec2 direction = delta.normalize();
    float distance = std::max(delta.lenght(), minDistance);
    acceleration = direction * (shape.mass / (distance * distance + epsilon * epsilon));
    velocity = velocity + acceleration;
    pos = pos + velocity;
    if (distance <= shape.radius)
    {
        alive = false;
    }
}
void Shape::updateTrail()
{

    trail.push_back(pos);
    if (trail.size() > 1300)
    {
        trail.erase(trail.begin());
    }
}
void Shape::drawTrail()
{
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < trail.size(); ++i)
    {
        float alpha = (float)i / trail.size();
        glColor4f(1.0f, 1.0f, 1.0f, alpha);
        glVertex2d(trail[i].x, trail[i].y);
    }
    glEnd();
}
void Shape::drawArrow()
{
    Vec2 arrowEndv = pos + velocity * 50;
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    glVertex2d(pos.x, pos.y);
    glVertex2d(arrowEndv.x, arrowEndv.y);
    glEnd();
    drawHead(0, 1, 0, arrowEndv, velocity);

    Vec2 arrowEnda = pos + acceleration * 4000;
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2d(pos.x, pos.y);
    glVertex2d(arrowEnda.x, arrowEnda.y);
    glEnd();
    drawHead(1, 0, 0, arrowEnda, acceleration);
}
void Shape::drawHead(float r, float g, float b, Vec2 arrow, Vec2 vector)
{
    Vec2 dir = vector.normalize();
    Vec2 perp(-dir.y, dir.x);
    float size = 10.0f;
    Vec2 left = arrow - dir * size + perp * size * 0.5f;
    Vec2 right = arrow - dir * size - perp * size * 0.5f;
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex2d(arrow.x, arrow.y);
    glVertex2d(left.x, left.y);
    glVertex2d(right.x, right.y);
    glEnd();
}
void Shape::reset()
{
    pos = pos0;
    velocity = velocity0;
    acceleration = {0, 0};
    trail.clear();
}