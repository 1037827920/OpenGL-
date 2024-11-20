#include "RectangleModel.h"
#include <iostream>

using std::cout;
using std::endl;

// 顶点属性位置
const int VERTEX_ATTR_POSITION = 0;
// 每个顶点的组件数
const int NUM_COMPONENTS_PER_VERTEX = 2;

// 构造函数
RectangleModel::RectangleModel() {
    // 编译着色器
    compileShaders();
    // 设置缓冲区
    setElements();
}

// 析构函数
RectangleModel::~RectangleModel() {
    // 删除VAO
    glDeleteVertexArrays(1, &this->VAO);
    // 删除VBO
    glDeleteBuffers(1, &this->VBO);
    // 删除EBO
    glDeleteBuffers(1, &this->EBO);
}

/// public
// 绘制矩形
void RectangleModel::draw() {
    // 使用着色器程序
    glUseProgram(shaderProgram);
    // 绑定VAO
    glBindVertexArray(VAO);
    // 绘制矩形，即绘制两个三角形，GL_UNSIGNED_INT表示索引数组中的每个元素都是一个无符号整数
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

/// private
// 编译着色器
void RectangleModel::compileShaders() {
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
    this->shaderProgram = glCreateProgram();
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
}

void RectangleModel::setElements() {
    // 顶点数据
    float vertices[] = {
        -0.75f, -0.75f,
        0.75f, -0.75f,
        -0.75f, 0.75f,
        0.75f, 0.75f
    };
    // 索引数据
    int indices[] = {
        0, 1, 2,
        1, 2, 3, };
    
    // 生成一个VAO
    glGenVertexArrays(1, &this->VAO);
    // 绑定VAO，使其成为当前操作的VAO
    glBindVertexArray(this->VAO);
    // 生成一个VBO
    glGenBuffers(1, &this->VBO);
    // 绑定VBO, 使其成为当前操作的VBO，GL_ARRAY_BUFFER表示顶点缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    // 为当前绑定的VBO创建并初始化数据存储，GL_STATIC_DRAW表示数据将一次性提供给缓冲区，并且在之后的绘制过程中不会频繁更改
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 生成一个EBO
    glGenBuffers(1, &this->EBO);
    // 绑定EBO，使其成为当前操作的EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // 传递索引数据
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // 定义顶点属性的布局
    // - index：顶点属性的索引
    // - size：每个顶点属性的数量，每个顶点有三个分享
    // - type：数据类型
    // - normalized：是否将非浮点数值归一化
    // - stride：连续顶点属性之间的间隔
    // - pointer：数据在缓冲区中的偏移量
    glVertexAttribPointer(VERTEX_ATTR_POSITION, NUM_COMPONENTS_PER_VERTEX, GL_FLOAT, GL_FALSE, NUM_COMPONENTS_PER_VERTEX * sizeof(float), (void*)0);
    // 启用顶点属性数组
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
}