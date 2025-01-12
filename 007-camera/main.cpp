#include "utils/RectangleModel.h"
#include "utils/windowFactory.h"

int main() {
    // 创建一个窗口Factory对象
    GLFWWindowFactory myWindow(800, 600, "This is Title");
    // 创建一个着色器对象
    Shader shader("shader.vs", "shader.fs");
    // 创建一个矩形模型对象
    RectangleModel rectangle(shader);
    
    // 运行窗口，传入一个lambda表达式，用于自定义渲染逻辑
    myWindow.run([&]() {
        // 设置投影矩阵
        shader.setMat4("projection", myWindow.getProjectionMatrix());
        // 设置视图矩阵
        shader.setMat4("view", myWindow.getViewMatrix());
        // 绘制矩形
        rectangle.draw();
    });
    
    return 0;
}