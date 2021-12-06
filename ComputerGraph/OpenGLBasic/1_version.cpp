//
// Created by lon on 6/12/2021.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void processKeyEvent(GLFWwindow* window) {
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void processMouseEvent(GLFWwindow* window) {
}

void printInfo() {
  std::cout << "version: " << glGetString(GL_VERSION) << "\n";
  std::cout << "shader version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';
}
int main() {
  // init glfw window ...
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // create glfw window ...
  auto window = glfwCreateWindow(900, 600, "1_version", nullptr, nullptr);
  if(window == nullptr) {
    std::cout << "Failed to create glfw windows\n";
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // init glad context
  if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    std::cout << "Failed to initialize GLAD\n";
    glfwTerminate();
    return -1;
  }

  printInfo();

  // equal frame buffer size?
  glViewport(0, 0, 800, 600);

  // set resize call back function
  auto framebuffer_resize_cb = [](GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
  };
  glfwSetFramebufferSizeCallback(window, framebuffer_resize_cb);


  // set clear color
  glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

  while(!glfwWindowShouldClose(window)) {
    processKeyEvent(window);
    processMouseEvent(window);

    glClear(GL_COLOR_BUFFER_BIT);

    // 一般都需要swap buffer, 那么是程序框架做好了framebuffer, 来保证双缓冲吗?
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}