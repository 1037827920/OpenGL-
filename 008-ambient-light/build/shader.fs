#version 330 core

in vec2 TexCoord;

// 第一个纹理
uniform sampler2D texture0;
// 第二个纹理
uniform sampler2D texture1;
// 混合比例
uniform float blendRatio;
// 光源颜色
uniform vec3 lightColor;

out vec4 FragColor;

void main()
{
    // 环境光强度
    float ambientStrength = 0.2;
    // 计算环境光分量
    vec3 ambient = ambientStrength * lightColor;

    // 最终颜色结果
    vec3 lighting = ambient;

    // 将两个纹理混合并乘以环境光分量
    FragColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), blendRatio) * vec4(lighting, 1.0);
}