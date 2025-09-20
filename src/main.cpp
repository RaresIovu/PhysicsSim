#include <GLFW/glfw3.h>
#include <Shape.h>
#include <iostream>
#include <cmath>
#include <Vec2.h>
#include <unordered_map>
#include <simulation.h>
int fbwidth, fbheight;
bool paused = false;
std::unordered_map<char, int> Key;
std::vector<Shape> bodies;
GLFWwindow *StartGLFW();

int main()
{
  Key[GLFW_KEY_SPACE] = 0;
  Key[GLFW_KEY_R] = 0;
  GLFWwindow *window = StartGLFW();
  glfwGetFramebufferSize(window, &fbwidth, &fbheight);
  glViewport(0, 0, (int)fbwidth, (int)fbheight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, fbwidth, 0, fbheight, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(0, 0, 0, 1);
  glEnable(GL_LINE_SMOOTH);
  glDisable(GL_DEPTH_TEST);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glLineWidth(2.0f);
  float centerX = fbwidth / 2.0f;
  float centerY = fbheight / 2.0f;
  int radius = 50;
  int sides = 4;
  float offset = M_PI / 4.0f;
  Shape star(
      Vec2(centerX, centerY),
      Vec2(0, 0),
      1000,
      100,
      'S');
  star.r = 1.0f;
  star.g = 0.5f;
  star.b = 0.0f;
  Shape planet(
      Vec2(500, 500),
      Vec2(0, 1.5f),
      1,
      25,
      'P');
  planet.b = 1.0f;
  bodies.push_back(planet);
  bodies.push_back(star);
  std::vector<Shape> initialBodies = bodies;
  while (!glfwWindowShouldClose(window))
  {
    for (auto &[key, value] : Key)
    {
      if (value > 0)
        value--;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
      if (Key.at(GLFW_KEY_SPACE) == 0)
      {
        paused = !paused;
        Key.at(GLFW_KEY_SPACE) = 20;
      }
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
      if (Key.at(GLFW_KEY_R) == 0)
      {
        bodies = initialBodies;
        Key.at(GLFW_KEY_R) = 20;
      }
    }
    simulation(bodies, paused);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

GLFWwindow *StartGLFW()
{

  if (!glfwInit())
  {
    std::cerr << "no glfw brochacho" << std::endl;
    return nullptr;
  }

  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  if (!monitor)
  {
    std::cerr << "No monitor found brochacho" << std::endl;
    glfwTerminate();
    return nullptr;
  }
  const GLFWvidmode *mode = glfwGetVideoMode(monitor);
  if (!mode)
  {
    std::cerr << "No mode found brochacho " << std::endl;
    glfwTerminate();
    return nullptr;
  }

  GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "fapny", monitor, NULL);
  if (!window)
  {
    std::cerr << "No window brochacho" << std::endl;
    glfwTerminate();
    return nullptr;
  }

  glfwMakeContextCurrent(window);
  return window;
}
