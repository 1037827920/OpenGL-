#include "RectangleModel.h"
#include <iostream>

using std::cout;
using std::endl;

// 构造函数
RectangleModel::RectangleModel(const Shader& shader) : shader(shader) {
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
    this->shader.use();
    // 绑定VAO
    glBindVertexArray(VAO);
    // 绘制矩形，即绘制两个三角形，GL_UNSIGNED_INT表示索引数组中的每个元素都是一个无符号整数
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

/// private
void RectangleModel::setElements() {
    // 顶点数据
    float vertices[] = {
        -0.75f, -0.75f, 1.0f, 0.0f, 0.0f,
        0.75f, -0.75f, 1.0f, 0.5f, 0.0f,
        -0.75f, 0.75f, 1.0f, 0.0f, 1.0f,
        0.75f, 0.75f, 0.0f,1.0f,0.0f,
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
    // 设置顶点属性指针，位置属性
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    // 启用顶点属性
    glEnableVertexAttribArray(0);
    // 设置顶点属性指针，颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    // 启用顶点属性
    glEnableVertexAttribArray(1);
}