//
// Created by lon on 6/12/2021.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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

  // equal frame buffer size?
  glViewport(0, 0, 800, 600);

  // set resize call back function
  auto framebuffer_resize_cb = [](GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
  };
  glfwSetFramebufferSizeCallback(window, framebuffer_resize_cb);

  while(!glfwWindowShouldClose(window)) {
    // 一般都需要swap buffer, 那么是程序框架做好了framebuffer, 来保证双缓冲吗?
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}