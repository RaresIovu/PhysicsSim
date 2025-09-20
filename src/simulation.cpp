#include <GLFW/glfw3.h>
#include <Shape.h>
void simulation(std::vector<Shape> &bodies, bool paused)
{
    glClear(GL_COLOR_BUFFER_BIT);
    for (Shape &body : bodies)
    {
        if (body.tag == 'P')
        {
            if (body.alive)
            {
                body.draw();
                body.drawArrow();
                if (!paused)
                {
                    for (Shape &star : bodies)
                        if (star.tag == 'S')
                            body.updateGravity(star);
                }
                body.drawTrail();
            }
            if (!paused)
            {
                body.updateTrail();
            }
        }
        else
        {
            body.draw();
        }
    }
}
