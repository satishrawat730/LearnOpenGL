#include "glew.h"
#include <glfw3.h>

#include <stdlib.h>
#include <iostream>
#include <stdio.h>

using namespace std;

GLint Width = 800, Height = 600;

GLuint VAO, VBO, shader;

// vertex shader
static const char* vshader = " #version 330 \n\
layout (location = 0) in vec3 pos; \n\
void main()  {  gl_Position = vec4( pos, 1.0); }";

// fragment shader
static const char* fshader = " #version 330 \n\
out vec4 color; \n\
void main() { color = vec4( 1., .5, 0., 1.0); }";

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType);

    const GLchar * theCode[1];
    theCode[0] = shaderCode;

    GLint theCodeLength[1];
    theCodeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, theCodeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar elog[1024] = { 0 };
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

    if (!result)
    {
        glGetShaderInfoLog(theShader, sizeof(elog), NULL, elog);
        cout << " Error compling the "<<shaderType <<" shader: " << elog << "\n";
        return;
    }

    glAttachShader(theProgram, theShader);
    return;
}

void CompileShaders()
{
    shader = glCreateProgram();

    if (!shader)
    {
        cout << "Error creating shader Program";
        return;
    }

    AddShader(shader, vshader, GL_VERTEX_SHADER);
    AddShader(shader, fshader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar elog[1024] = { 0 };

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);

    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(elog), NULL, elog);
        cout << " Error Linking program: " << elog << "\n";
        return;
    }
    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);

    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(elog), NULL, elog);
        cout << " Error validating program: " << elog << "\n";
        return;
    }
}

void CreateTriangle()
{
    GLfloat vertices[] = {
        -1., -1., 0.,
        1., -1., 0.,
        0., 1., 0.
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

//void error_callback(int error, const char* description)
//{
//    fprintf(stderr, "Error: %s\n", description);
//}

//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//    glfwSetWindowShouldClose(window, GLFW_TRUE);
//}

int main()
{
    cout << "hello";
    if (!glfwInit())
    {
        cout << "Initialization failed";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Setup GLFW window properties
    // Opengl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core profile -- no backward compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(Width, Height, "Opengl Window", NULL, NULL);
    if (!window)
    {
        cout << "Window or OpenGL context creation failed";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    // Get frame buffer size info
    int bufferWidth, bufferHeigth;
    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeigth);

    // set context for GLEW to use
    glfwMakeContextCurrent(window);

    // Allow modern extension features
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        cout << "GLEW intialization failed";
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }

    // setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeigth);

    CreateTriangle();
    CompileShaders();

    //loop until window closed
    while (!glfwWindowShouldClose(window))
    {
        // get + handle input events
        glfwPollEvents();

        // clear window 
        glClearColor(0.3f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);
    return 0;
}
