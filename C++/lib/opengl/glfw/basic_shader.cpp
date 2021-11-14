#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <base.h>
#include <iostream>

static unsigned int CompileShader(unsigned int type, const std::string& shader) {
    unsigned id = glCreateShader(type);
    const char* src = shader.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = static_cast<char*>(alloca(length * sizeof(char)));

        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " " << message << std::endl;
        return 0;
    }

    return id;
}

static const char* vertex_shader_str =
R"(
#version 410 core
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec4 position;

void main() {
    gl_Position = position + 3;
}
)";

static const char* fragment_shader_str =
        R"(
#version 410 core

layout(location = 0) out vec4 color;

void main() {
    color = vec4(1.0, 0.0, 0.0, 1.0);
}
)";


static unsigned  int CreateShader(const std::string& vertex_shader, const std::string& fragment_shader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex_shader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment_shader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "TRIANGLE", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cerr << "wrong glew init\n";
    }

    std::cout << "opengl version: " << glGetString(GL_VERSION) << std::endl;

    float position[6] = {
        -0.5,
        -0.5,
        0.0,
        0.5,
        0.5,
        -0.5,
    };

    // 创建opengl buffer.
    unsigned int buffer_handle;
    glGenBuffers(1, &buffer_handle);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_handle);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(position) * sizeof(float),
                 position,
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    unsigned int shader = CreateShader(vertex_shader_str, fragment_shader_str);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}