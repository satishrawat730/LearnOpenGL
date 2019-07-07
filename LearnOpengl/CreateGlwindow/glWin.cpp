#include <glfw3.h>

#include <stdlib.h>
#include <iostream>
#include <stdio.h>

using namespace std;

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
  if (!glfwInit())
  {
    cout << "Initialization failed";
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  /*GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
  if (!window)
  {
    cout << "Window or OpenGL context creation failed";
  }*/

  /*while (!glfwWindowShouldClose(window))
  {
      glfwSwapBuffers(window);
      glfwPollEvents();
  }

  glfwDestroyWindow(window);*/
  glfwTerminate();

  exit(EXIT_SUCCESS);
  return 0;
}
