#version 330 core

// 光源颜色
uniform vec3 lightColor;

// 输出的片段颜色
out vec4 FragColor;

void main()
{
    FragColor = vec4(lightColor, 1.0);
}