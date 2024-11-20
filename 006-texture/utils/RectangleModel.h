#pragma once
#include <glad/glad.h>
#include "shader.h"
#include <vector>
#include <chrono>
#include <cmath>

class RectangleModel {
public:
    // 构造函数
    RectangleModel(const Shader& shader);
    // 析构函数
    ~RectangleModel();
    
    // 绘制矩形
    void draw();

private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    Shader shader;
    
    // 纹理
    std::vector<unsigned int>texture;
    
    
    // 编译着色器
    void compileShaders();
    // 设置缓冲区
    void setElements();
    // 加载纹理
    void loadTexture();
    // 绑定纹理
    void bindTexture(GLuint& textured, const char* path);
};