#pragma once
#include<glad/glad.h>

class RectangleModel {
public:
    // 构造函数
    RectangleModel();
    // 析构函数
    ~RectangleModel();

    // 绘制矩形
    void draw();

private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    // 着色器程序
    unsigned int shaderProgram;

    // 编译着色器
    void compileShaders();
    // 设置缓冲区
    void setElements();
};