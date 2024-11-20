// 指定OpenGL着色器语言的版本为3.30
#version 330 core
// 输入变量，表示传入的颜色值
in vec3 ourColor;
// 输出变量，表示片段的最终颜色
out vec4 FragColor;

void main() {
	// 将输入的颜色值转换为vec4，并将alpha值设置为1.0，赋值给输出变量
	FragColor = vec4(ourColor, 1.0f);
}