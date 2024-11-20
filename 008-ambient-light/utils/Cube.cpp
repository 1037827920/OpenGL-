#include "Cube.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Cube::Cube(GLFWWindowFactory* window) : window(window) {
    this->shader = Shader("shader.vs", "shader.fs");
    this->lightShader = Shader("lightShader.vs", "lightShader.fs");
    // 加载纹理
    loadTexture();
    // 设置顶点数据
    setupVertices();
}

Cube::~Cube() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

/// Public
void Cube::draw() {
    // 存储光源的位置和强度
    vector<float> lightPos = { 2.0f, 1.5f, -1.55f, 1.0f };

    // 使用立方体的着色器
    shader.use();
    // 将立方体的VAO绑定到上下文
    glBindVertexArray(this->VAO);

    // 设置立方体模型矩阵
    auto model = glm::mat4(1.0f);
    // 设置平移矩阵
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
    // 设置旋转矩阵
    model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    // 将uniform变量传递给着色器
    shader.setMat4("model", model);
    shader.setMat4("view", this->window->getViewMatrix());
    shader.setMat4("projection", this->window->getProjectionMatrix());
    shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    shader.setVec3("lightPos", lightPos[0], lightPos[1], lightPos[2]);
    shader.setFloat("blendRatio", 0.5f);

    // 绘制立方体
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // 使用光源的着色器
    lightShader.use();
    // 光源的VAO仍然使用立方体的VAO
    // 设置模型矩阵
    model = glm::mat4(1.0f);
    // 设置平移矩阵
    model = glm::translate(model, glm::vec3(lightPos[0], lightPos[1], lightPos[2]));
    // 设置缩放矩阵
    model = glm::scale(model, glm::vec3(0.2f));

    // 将uniform变量传递给着色器
    lightShader.setMat4("model", model);
    lightShader.setMat4("view", this->window->getViewMatrix());
    lightShader.setMat4("projection", this->window->getProjectionMatrix());
    lightShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

    // 绘制光源
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}


/// Private
// 设置顶点数据
void Cube::setupVertices() {
    // 顶点数据
    float vectices[] = {
        // Front
        -0.75f, -0.75f,0.0f, 0.0f, 0.0f,  // Bottom-left vertex
        0.75f, -0.75f,0.0f, 1.0f, 0.0f,   // Bottom-right vertex
        -0.75f, 0.75f,0.0f, 0.0f, 1.0f,   // Top-left vertex
        0.75f, 0.75f,0.0f, 1.0f, 1.0f,    // Top-right vertex

        // Back
        0.75f, -0.75f, -1.5f, 0.0f, 0.0f,  // Bottom-left vertex
        -0.75f, -0.75f, -1.5f, 1.0f, 0.0f,   // Bottom-right vertex
        0.75f, 0.75f, -1.5f, 0.0f, 1.0f,   // Top-left vertex
        -0.75f, 0.75f, -1.5f, 1.0f, 1.0f,    // Top-right vertex

        // Left
        -0.75f, -0.75f, -1.5f, 0.0f, 0.0f,  // Bottom-left vertex
        -0.75f, -0.75f, 0.0f, 1.0f, 0.0f,   // Bottom-right vertex
        -0.75f, 0.75f, -1.5f, 0.0f, 1.0f,   // Top-left vertex
        -0.75f, 0.75f, 0.0f, 1.0f, 1.0f,    // Top-right vertex

        // Right
        0.75f, -0.75f, 0.0f, 0.0f, 0.0f,  // Bottom-left vertex
        0.75f, -0.75f, -1.5f, 1.0f, 0.0f,   // Bottom-right vertex
        0.75f, 0.75f, 0.0f, 0.0f, 1.0f,   // Top-left vertex
        0.75f, 0.75f, -1.5f, 1.0f, 1.0f,    // Top-right vertex

        // Top
        -0.75f, 0.75f, 0.0f, 0.0f, 0.0f,  // Bottom-left vertex
        0.75f, 0.75f, 0.0f, 1.0f, 0.0f,   // Bottom-right vertex
        -0.75f, 0.75f, -1.5f, 0.0f, 1.0f,   // Top-left vertex
        0.75f, 0.75f, -1.5f, 1.0f, 1.0f,    // Top-right vertex

        // Bottom
        -0.75f, -0.75f, -1.5f, 0.0f, 0.0f,  // Bottom-left vertex
        0.75f, -0.75f, -1.5f, 1.0f, 0.0f,   // Bottom-right vertex
        -0.75f, -0.75f, 0.0f, 0.0f, 1.0f,   // Top-left vertex
        0.75f, -0.75f, 0.0f, 1.0f, 1.0f    // Top-right vertex
    };

    // 索引数据
    int indices[] = {
        0, 1, 2,
        2, 1, 3,

        4, 5, 6,
        6, 5, 7,

        8, 9, 10,
        10, 9, 11,

        12, 13, 14,
        14, 13, 15,

        16, 17, 18,
        18, 17, 19,

        20, 21, 22,
        22, 21, 23
    };

    // 创建VAO, VBO, EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // 绑定VAO
    glBindVertexArray(VAO);

    // 绑定VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 将顶点数据复制到VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vectices), vectices, GL_STATIC_DRAW);

    // 绑定EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // 将索引数据复制到EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 设置顶点位置属性（这里跟顶点着色器源码强相关，每个属性有多少个元素都是看这个顶点着色器源码是怎么写的）
    // 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // 纹理位置属性
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 恢复上下人默认的VAO
    glBindVertexArray(0);
}

// 加载纹理
void Cube::loadTexture() {
    vector<string> paths = { "teenager.png", "tex.png" };
    this->texture.resize(paths.size());
    // 绑定纹理
    for (int i = 0; i < paths.size(); i++) {
        bindTexture(this->texture[i], paths[i].c_str());
    }

    // 激活纹理
    glActiveTexture(GL_TEXTURE0);
    // 将纹理绑定到上下文
    glBindTexture(GL_TEXTURE_2D, this->texture[0]);
    // 激活纹理
    glActiveTexture(GL_TEXTURE1);
    // 将纹理绑定到上下文
    glBindTexture(GL_TEXTURE_2D, this->texture[1]);

    // 使用立方体着色器
    this->shader.use();
    // 为着色器设置uniform变量
    this->shader.setInt("texture0", 0);
    this->shader.setInt("texture1", 1);
}

// 绑定纹理
void Cube::bindTexture(GLuint& textureId, const char* path) {
    // 生成纹理
    glGenTextures(1, &textureId);
    // 绑定上下文的纹理
    glBindTexture(GL_TEXTURE_2D, textureId);

    // 设置纹理环绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // 设置纹理过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 加载和生成纹理
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