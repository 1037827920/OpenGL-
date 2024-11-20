#include "utils/TriangleModel.h"
#include "utils/windowFactory.h"

int main() {
    // 创建一个窗口Factory对象
    GLFWWindowFactory myWindow(800, 600, "This is Title");
    
    // 创建一个三角形模型对象
    TriangleModel triangle;
    
    // 运行窗口，传入一个lambda表达式，用于自定义渲染逻辑
    myWindow.run([&]() {
        // 绘制三角形
        triangle.draw();
    });
    
    return 0;
}