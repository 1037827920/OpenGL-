#include <glad/glad.h>

class TriangleModel {
public: 
    // 默认构造函数
    TriangleModel();
    // 默认析构函数
    ~TriangleModel();
    
    // 绘制三角形
    void draw();
    
private:
    unsigned int VAO;
    unsigned int VBO;
    // 着色器程序
    unsigned int shaderProgram;
    
    // 编译着色器
    void compileShaders();
    // 设置缓冲区
    void setupBuffers();
};