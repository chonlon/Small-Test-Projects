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

void main() {
  gl_Position = vec4(triangle_vertex.x, triangle_vertex.y, triangle_vertex.z, 1.0);
}
)";
  auto fragment_shader = R"(
#version 330 core

out vec4 vertex_color;

void main() {
  vertex_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
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

  float vertices[] = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f, 0.5f, 0.0f
  };

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  auto program = prepareProgram();

  while(!glfwWindowShouldClose(window)) {
    processKeyEvent(window);
    processMouseEvent(window);

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // 一般都需要swap buffer, 那么是程序框架做好了framebuffer, 来保证双缓冲吗?
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}