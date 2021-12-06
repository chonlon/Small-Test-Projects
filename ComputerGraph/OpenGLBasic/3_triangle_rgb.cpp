//
// Created by lon on 6/12/2021.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

auto initGLFW() {
  // init glfw window ...
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

auto createGLFWWindow() -> GLFWwindow* {
  // create glfw window ...
  auto window = glfwCreateWindow(900, 600, "1_version", nullptr, nullptr);
  if(window == nullptr) {
    std::cout << "Failed to create glfw windows\n";
    glfwTerminate();
    exit(-1);
  }
  glfwMakeContextCurrent(window);
  return window;
}

auto initGLAD() {
  // init glad context
  if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    std::cout << "Failed to initialize GLAD\n";
    glfwTerminate();
    exit(-1);
  }
}

auto printInfo() {
  std::cout << "version: " << glGetString(GL_VERSION) << "\n";
  std::cout << "shader version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';
}

auto setupGLViewport(GLFWwindow* window) {
  // equal frame buffer size?
  glViewport(0, 0, 800, 600);

  // set resize call back function
  auto framebuffer_resize_cb = [](GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
  };
  glfwSetFramebufferSizeCallback(window, framebuffer_resize_cb);

}

auto processKeyEvent(GLFWwindow* window) {
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

auto processMouseEvent(GLFWwindow* window) {
}

auto prepareProgram() {
  auto vertex_shader = R"(
#version 330 core

layout (location = 0) in vec3 triangle_vertex;
layout (location = 1) in vec3 triangle_vertex_color;
out vec3 o_triangle_vertex_color;

void main() {
  gl_Position = vec4(triangle_vertex, 1.0);
  o_triangle_vertex_color = triangle_vertex_color;
}
)";
  auto fragment_shader = R"(
#version 330 core

in vec3 o_triangle_vertex_color;
out vec4 vertex_color;

void main() {
  vertex_color = vec4(o_triangle_vertex_color, 1.0);
//  o_vertex_color = vec4(1.0, 0, 0, 1.0);
}
)";
  int success = true;
  char info[512]{};

  unsigned int vertex_shader_handle = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader_handle, 1, &vertex_shader, nullptr);
  glCompileShader(vertex_shader_handle);

  glGetShaderiv(vertex_shader_handle, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertex_shader_handle, 512, nullptr, info);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info << std::endl;
  }

  unsigned int fragment_shader_handle = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader_handle, 1, &fragment_shader, nullptr);
  glCompileShader(fragment_shader_handle);
  glGetShaderiv(fragment_shader_handle, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragment_shader_handle, 512, nullptr, info);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info << std::endl;
  }

  unsigned int shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader_handle);
  glAttachShader(shader_program, fragment_shader_handle);
  glLinkProgram(shader_program);

  glUseProgram(shader_program);
  glDeleteShader(vertex_shader_handle);
  glDeleteShader(fragment_shader_handle);
  return shader_program;
}


int main() {
  initGLFW();
  auto window = createGLFWWindow();
  initGLAD();

  printInfo();

  setupGLViewport(window);

  // set clear color
  glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
  auto program = prepareProgram();

  float vertices[] = {
      // 位置              // 颜色
      0.5f, -0.4f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
      -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
      0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
  };

  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(0));
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);
  
  glUseProgram(program);

  while(!glfwWindowShouldClose(window)) {
    processKeyEvent(window);
    processMouseEvent(window);

    glClear(GL_COLOR_BUFFER_BIT);


    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // 一般都需要swap buffer, 那么是程序框架做好了framebuffer, 来保证双缓冲吗?
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}