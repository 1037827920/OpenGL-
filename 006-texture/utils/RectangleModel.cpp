#include "RectangleModel.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using std::cout;
using std::endl;

// 构造函数
RectangleModel::RectangleModel(const Shader& shader) : shader(shader) {
    // 加载纹理
    loadTexture();
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

    // 获取当前时间
    auto now = std::chrono::system_clock::now();
    // 计算毫秒数
    auto duration = now.time_since_epoch();
    double milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    // 计算混合比例
    float blendRatio = 0.5f * (std::sin(milliseconds / 1000.0) + 1.0f);
    // 设置uniform变量
    shader.setFloat("blendRatio", blendRatio);

    // 绘制矩形，即绘制两个三角形，GL_UNSIGNED_INT表示索引数组中的每个元素都是一个无符号整数
    // 六个矩形
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

/// private
void RectangleModel::setElements() {
    float vertices[] = {
        // 矩形1
        -0.9f, -0.9f, 0.0f, 0.0f,
        -0.5f, -0.9f, 1.0f, 0.0f,
        -0.9f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 1.0f, 1.0f,

        // 矩形2
        -0.4f, -0.9f, 0.0f, 0.0f,
        0.0f, -0.9f, 1.0f, 0.0f,
        -0.4f, -0.5f, 0.0f, 1.0f,
        0.0f, -0.5f, 1.0f, 1.0f,

        // 矩形3
        0.1f, -0.9f, 0.0f, 0.0f,
        0.5f, -0.9f, 1.0f, 0.0f,
        0.1f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 1.0f, 1.0f,

        // 矩形4
        -0.9f, 0.1f, 0.0f, 0.0f,
        -0.5f, 0.1f, 1.0f, 0.0f,
        -0.9f, 0.5f, 0.0f, 1.0f,
        -0.5f, 0.5f, 1.0f, 1.0f,

        // 矩形5
        -0.4f, 0.1f, 0.0f, 0.0f,
        0.0f, 0.1f, 1.0f, 0.0f,
        -0.4f, 0.5f, 0.0f, 1.0f,
        0.0f, 0.5f, 1.0f, 1.0f,

        // 矩形6
        0.1f, 0.1f, 0.0f, 0.0f,
        0.5f, 0.1f, 1.0f, 0.0f,
        0.1f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 1.0f, 1.0f
    };
    // 索引数据
    int indices[] = {
        // 矩形 1
        0, 1, 2,
        1, 2, 3,

        // 矩形 2
        4, 5, 6,
        5, 6, 7,

        // 矩形 3
        8, 9, 10,
        9, 10, 11,

        // 矩形 4
        12, 13, 14,
        13, 14, 15,

        // 矩形5
        16, 17, 18,
        17, 18, 19,

        // 矩形6
        20, 21, 22,
        21, 22, 23
    };

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
    // - size：每个顶点属性的数量
    // - type：数据类型
    // - normalized：是否将非浮点数值归一化
    // - stride：连续顶点属性之间的间隔
    // - pointer：数据在缓冲区中的偏移量
    // 设置顶点属性指针，位置属性
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    // 启用顶点属性
    glEnableVertexAttribArray(0);
    // 设置顶点属性指针，颜色属性
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    // 启用顶点属性
    glEnableVertexAttribArray(1);
}

// 加载纹理
void RectangleModel::loadTexture() {
    std::vector<std::string> path = { "teenager.png", "tex.png" };
    texture.resize(path.size());
    for (int i = 0; i < path.size(); i++) {
        bindTexture(texture[i], path[i].c_str());
    }
    // 参数传入指定要激活的纹理单元，例如GL_TEXTURE0/1/*
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture[1]);

    // 使用着色器程序
    shader.use();
    // 设置uniform变量
    shader.setInt("texture0", 0);
    shader.setInt("texture1", 1);
}

// 绑定纹理
void RectangleModel::bindTexture(GLuint& textureId, const char* path) {
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    // 设置纹理环绕和过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载并生成纹理
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 4)
            format = GL_RGBA;
        else if (nrChannels == 3)
            format = GL_RGB;
        else
            format = GL_RED;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}