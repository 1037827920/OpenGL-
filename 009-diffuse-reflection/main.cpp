#include "utils/Cube.h"
#include "utils/windowFactory.h"

int main() {
    // 创建一个窗口Factory对象
    GLFWWindowFactory myWindow(800, 600, "This is Title");
    // 创建一个矩形模型对象
    Cube cube(&myWindow);
    
    // 运行窗口，传入一个lambda表达式，用于自定义渲染逻辑
    myWindow.run([&]() {
        // 绘制矩形
        cube.draw();
    });
    
    return 0;
}