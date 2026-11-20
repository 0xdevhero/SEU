#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
GLuint VBO, VAO, shader;

// Vertex Shader code
static const char* vShader = "                                                \n\
#version 330                                                                  \n\
in vec3 pos;                                                                  \n\
void main()                                                                   \n\
{                                                                             \n\
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);                            \n\
}";

// Fragment Shader code: Tree Green color (RGB: 59, 156, 64)
static const char* fShader = "                                                \n\
#version 330                                                                  \n\
out vec4 colour;                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    colour = vec4(0.2314, 0.6118, 0.2510, 1.0);                               \n\
}";

void CreateTriangle() {
    // 17 Triangles (51 vertices) constructing the Triangle Tree
    GLfloat vertices[] = {
        // Tier 1 (Top) - Triangle 1
           0.0000f,    0.8000f,  0.0f,
          -0.2346f,    0.2816f,  0.0f,
          -0.1390f,    0.2816f,  0.0f,
        // Tier 1 (Top) - Triangle 2
           0.0000f,    0.8000f,  0.0f,
          -0.1390f,    0.2816f,  0.0f,
          -0.0022f,    0.4786f,  0.0f,
        // Tier 1 (Top) - Triangle 3
           0.0000f,    0.8000f,  0.0f,
          -0.0022f,    0.4786f,  0.0f,
           0.1064f,    0.3265f,  0.0f,
        // Tier 1 (Top) - Triangle 4
           0.0000f,    0.8000f,  0.0f,
           0.1064f,    0.3265f,  0.0f,
           0.2183f,    0.3265f,  0.0f,
        // Tier 2 (Middle) - Triangle 5
          -0.0022f,    0.4496f,  0.0f,
          -0.3225f,   -0.0195f,  0.0f,
          -0.1781f,   -0.0195f,  0.0f,
        // Tier 2 (Middle) - Triangle 6
          -0.0022f,    0.4496f,  0.0f,
          -0.1781f,   -0.0195f,  0.0f,
           0.0087f,    0.2440f,  0.0f,
        // Tier 2 (Middle) - Triangle 7
          -0.0022f,    0.4496f,  0.0f,
           0.0087f,    0.2440f,  0.0f,
           0.1933f,   -0.0195f,  0.0f,
        // Tier 2 (Middle) - Triangle 8
          -0.0022f,    0.4496f,  0.0f,
           0.1933f,   -0.0195f,  0.0f,
           0.3171f,   -0.0195f,  0.0f,
        // Tier 3 (Bottom Foliage Left Wing) - Triangle 9
           0.0087f,    0.2150f,  0.0f,
          -0.3812f,   -0.3338f,  0.0f,
          -0.0738f,   -0.3338f,  0.0f,
        // Tier 3 (Bottom Foliage Left Center) - Triangle 10
           0.0087f,    0.2150f,  0.0f,
          -0.0738f,   -0.3338f,  0.0f,
           0.1662f,   -0.0065f,  0.0f,
        // Tier 3 (Bottom Foliage Right Wing) - Triangle 11
           0.1716f,   -0.0253f,  0.0f,
           0.3877f,   -0.3338f,  0.0f,
          -0.0532f,   -0.3338f,  0.0f,
        // Left Branch / Strut - Triangle 12
          -0.2107f,   -0.3338f,  0.0f,
          -0.0597f,   -0.5278f,  0.0f,
          -0.0543f,   -0.4568f,  0.0f,
        // Left Branch / Strut - Triangle 13
          -0.2107f,   -0.3338f,  0.0f,
          -0.0543f,   -0.4568f,  0.0f,
          -0.1510f,   -0.3338f,  0.0f,
        // Right Branch / Strut - Triangle 14
           0.1357f,   -0.3338f,  0.0f,
           0.1955f,   -0.3338f,  0.0f,
           0.0597f,   -0.5046f,  0.0f,
        // Right Branch / Strut - Triangle 15
           0.1357f,   -0.3338f,  0.0f,
           0.0597f,   -0.5046f,  0.0f,
           0.0543f,   -0.4395f,  0.0f,
        // Trunk - Triangle 16
          -0.0532f,   -0.3338f,  0.0f,
          -0.0760f,   -0.8000f,  0.0f,
           0.0814f,   -0.8000f,  0.0f,
        // Trunk - Triangle 17
          -0.0532f,   -0.3338f,  0.0f,
           0.0814f,   -0.8000f,  0.0f,
           0.0478f,   -0.3338f,  0.0f,
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

void AddShader(GLuint program, const char* code, GLenum type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);
    glAttachShader(program, shader);
    glDeleteShader(shader);
}

void CompileShaders() {
    shader = glCreateProgram();
    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);
    glLinkProgram(shader);
    glValidateProgram(shader);
}

int main() {
    // Initialise GLFW
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "CSE444 Assignment 1 - Triangle Tree (2022200000061)", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
    glViewport(0, 0, bufferWidth, bufferHeight);

    CreateTriangle();
    CompileShaders();

    // Sky Blue Background matching the assignment picture: RGB (138, 202, 237)
    glClearColor(138.0f / 255.0f, 202.0f / 255.0f, 237.0f / 255.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        glBindVertexArray(VAO);
        // Draw 17 triangles (51 vertices)
        glDrawArrays(GL_TRIANGLES, 0, 51);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    return 0;
}
