#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using std::cout;
using std::endl;

// 屏幕宽度
const unsigned int SCR_WIDTH = 800;
// 屏幕高度
const unsigned int SCR_HEIGHT = 600;

// 窗口大小改变的回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // 确保视口与新窗口尺寸匹配，注意在视网膜显示器上，宽度和高度会显著大于指定值
    glViewport(0, 0, width, height);
}

// 处理输入
void process_input(GLFWwindow* window) {
    // 按下ESC键时进入if块
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        // 关闭窗口
        glfwSetWindowShouldClose(window, true);
}

int main() {
    // 初始化glfw
    glfwInit();
    // 设置opengl版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 使用核心模式：确保不使用任何被弃用的功能
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
    // 创建glfw窗口
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "I am window title", NULL, NULL);
    if (window == NULL) {
        cout << "Failed to create glfw window" << endl;
        // 终止GLFW
        glfwTerminate();
        return -1;
    }
    // 设置当前窗口的上下文
    glfwMakeContextCurrent(window);
    // 设置窗口大小改变的回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // 加载opengl函数指针
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }
    
    // 循环渲染
    while (!glfwWindowShouldClose(window)) { // 检查是否应该关闭窗口
        // 处理输入
        process_input(window);
        
        // 清空屏幕所用的颜色
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        // 清空颜色缓冲，主要目的是为每一帧的渲染准备一个干净的画布
        glClear(GL_COLOR_BUFFER_BIT);
        
        // 交换缓冲区
        glfwSwapBuffers(window);
        // 处理所有待处理事件，去poll所有事件，看看哪个没处理的
        glfwPollEvents();
    }
    
    // 终止GLFW，清理GLFW分配的资源
    glfwTerminate();
    return 0;
}