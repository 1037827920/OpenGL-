#pragma once
#include <glad/glad.h> // gald前面不能包含任何opengl头文件
#include <GLFW/glfw3.h>
#include <functional>
#include <iostream>

using std::cout;
using std::endl;

class GLFWWindowFactory {
public:
    // 默认构造函数
    GLFWWindowFactory() {}
    // 构造函数，初始化窗口
    GLFWWindowFactory(int width, int height, const char* title) {
        // 初始化glfw
        glfwInit();
        // 设置opengl版本
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        // 使用核心模式：确保不使用任何被弃用的功能
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // 创建glfw窗口
        this->window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (this->window == NULL) {
            cout << "Failed to create GLFW window" << endl;
            glfwTerminate();
            exit(-1);
        }
        // 设置当前窗口的上下文
        glfwMakeContextCurrent(this->window);
        // 设置窗口大小改变的回调函数
        glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
        // 加载所有opengl函数指针
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            cout << "Failed to initialize GLAD" << endl;
        }
        // 再次设置当前窗口的上下文，确保当前上下文仍然是刚刚创建的窗口，是一个安全措施
        glfwMakeContextCurrent(this->window);
        // 设置窗口大小改变的回调函数
        glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
    }

    // 获取窗口对象
    GLFWwindow* getWindow() {
        return this->window;
    }

    // 运行窗口，传入一个自定义的更新函数
    void run(std::function<void()> updateFunc) {
        // 启用深度测试，opengl将在绘制每个像素之前比较其深度值，以确定该像素是否应该被绘制
        glEnable(GL_DEPTH_TEST);

        // 循环渲染
        while (!glfwWindowShouldClose(this->window)) { // 检查是否应该关闭窗口
            // 清空屏幕所用的颜色
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            // 清空颜色缓冲，主要目的是为每一帧的渲染准备一个干净的画布
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // 处理输入
            GLFWWindowFactory::process_input(this->window);

            // 执行更新函数
            updateFunc();

            // 交换缓冲区
            glfwSwapBuffers(this->window);
            // 处理所有待处理事件，去poll所有事件，看看哪个没处理的
            glfwPollEvents();
        }

        // 终止GLFW，清理GLFW分配的资源
        glfwTerminate();
    }

    // 窗口大小改变的回调函数
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        // 确保视口与新窗口尺寸匹配，注意在视网膜显示器上，宽度和高度会显著大于指定值
        glViewport(0, 0, width, height);
    }

    // 处理输入
    static void process_input(GLFWwindow* window) {
        // 按下ESC键时进入if块
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            // 关闭窗口
            glfwSetWindowShouldClose(window, true);
    }

private:
    // 窗口对象
    GLFWwindow* window;
};