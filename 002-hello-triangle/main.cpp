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

// 顶点着色器源码
const char* vertexShaderSource = "#version 330 core\n" // 指定了GLSL（OpenGL着色器语言）的版本
"layout (location = 0) in vec3 aPos;\n" // 定义了一个输入变量aPos，它是一个vec3类型的变量, 并且指定了它的位置值为0, 这意味着顶点属性数组的第一个属性将被绑定到这个变量
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" // 将输入的顶点位置aPos转换为一个四维向量，gl_Postion是OpengGL固定功能管线中用于存储顶点位置的变量
"}\0";

// 片段着色器源码
const char* fragmentShaderSource = "#version 330 core\n" // 指定了GLSL（OpenGL着色器语言）的版本
"out vec4 FragColor;\n" // 定义了一个输出变量FragColor，它是一个vec4类型的变量，表示片段颜色，out关键字表示这个变量将输出到渲染管线的下一个阶段
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n" // 将输出颜色设置为橙色
"}\n\0";

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

    // 构建并编译顶点着色程序
    // 创建一个着色器对象，GL_VERTEX_SHADER表示顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 将着色器源码附加到着色器对象上
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // 编译着色器
    glCompileShader(vertexShader);
    // 检查着色器是否编译成功
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
            << infoLog << endl;
    }
    // 构建并编译片段着色器
    // 创建一个着色器对象，GL_FRAGMENT_SHADER表示片段着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // 将着色器源码附加到着色器对象上
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // 编译着色器
    glCompileShader(fragmentShader);
    // 检查着色器是否编译成功
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
            << infoLog << endl;
    }
    // 创建着色器程序对象
    unsigned int shaderProgram = glCreateProgram();
    // 将着色器对象附加到着色器程序上
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // 链接程序对象
    glLinkProgram(shaderProgram);
    // 检查链接是否成功
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
            << infoLog << endl;
    }
    // 删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 设置三角形的顶点数据
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // 左下角
        0.5f, -0.5f, 0.0f,  // 右下角
        0.0f, 0.5f, 0.0f    // 顶部
    };
    // 生成一个VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // 绑定VAO，使其成为当前操作的VAO
    glBindVertexArray(VAO);
    // 生成一个VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    // 绑定VBO, 使其成为当前操作的VBO，GL_ARRAY_BUFFER表示顶点缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 为当前绑定的VBO创建并初始化数据存储，GL_STATIC_DRAW表示数据将一次性提供给缓冲区，并且在之后的绘制过程中不会频繁更改
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 定义顶点属性的布局
    // - index：顶点属性的索引
    // - size：每个顶点属性的数量，每个顶点有三个分享
    // - type：数据类型
    // - normalized：是否将非浮点数值归一化
    // - stride：连续顶点属性之间的间隔
    // - pointer：数据在缓冲区中的偏移量
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // 启用顶点属性数组
    glEnableVertexAttribArray(0);
    // 解绑VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // 解绑VAO
    glBindVertexArray(0);

    // 循环渲染
    while (!glfwWindowShouldClose(window)) { // 检查是否应该关闭窗口
        // 处理输入
        process_input(window);

        // 清空屏幕所用的颜色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 清空颜色缓冲，主要目的是为每一帧的渲染准备一个干净的画布
        glClear(GL_COLOR_BUFFER_BIT);

        // 使用着色器程序
        glUseProgram(shaderProgram);
        // 绑定VAO
        glBindVertexArray(VAO);
        // 绘制三角形
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 交换缓冲区
        glfwSwapBuffers(window);
        // 处理所有待处理事件，去poll所有事件，看看哪个没处理的
        glfwPollEvents();
    }

    // 删除VAO
    glDeleteVertexArrays(1, &VAO);
    // 删除VBO
    glDeleteBuffers(1, &VBO);
    // 删除着色器程序
    glDeleteProgram(shaderProgram);

    // 终止GLFW，清理GLFW分配的资源
    glfwTerminate();
    return 0;
}