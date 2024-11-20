// 指定OpenGL着色器语言的版本为3.30
#version 330 core
// 输入变量，表示纹理坐标
in vec2 TexCoord;
// 输出变量，表示片段的最终颜色
out vec4 FragColor;
// uniform变量，表示第一个纹理
uniform sampler2D texture0;
// uniform变量，表示第二个纹理
uniform sampler2D texture1;
// uniform变量，表示混合比例
uniform float blendRatio;

void main() {
	// 使用mix函数根据blendRatio混合两个纹理的颜色，并将结果赋值给输出变量FragColor
	FragColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), blendRatio);
}