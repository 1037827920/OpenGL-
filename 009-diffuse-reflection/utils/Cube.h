#pragma once
#include "windowFactory.h"

#include <glad/glad.h>
#include "shader.h"
#include <vector>
#include <cmath>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using std::vector;
using std::string;


class Cube {
public:
    // 构造函数
    Cube(GLFWWindowFactory* window);

    // 析构函数
    ~Cube();

    // 绘制函数
    void draw();

private:
    // 顶点数组对象
    GLuint VAO;
    // 顶点缓冲对象
    GLuint VBO;
    // 索引缓冲对象
    GLuint EBO;
    // 着色器对象
    Shader shader;
    // 点光源着色器对象
    Shader lightShader;
    // 窗口对象
    GLFWWindowFactory* window;
    // 纹理对象
    vector<GLuint> texture;

    // 设置顶点数据
    void setupVertices();
    // 加载纹理
    void loadTexture();
    // 绑定纹理
    void bindTexture(GLuint& textureId, const char* path);
};