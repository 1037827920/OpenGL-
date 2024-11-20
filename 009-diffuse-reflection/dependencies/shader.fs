#version 330 core

in vec2 TexCoord;
// 表示片段的法向量，用于确定片段相对于光源的角度
in vec3 Normal;
// 表示片段在世界空间中的位置，用于确定片段相对于光源的距离
in vec3 FragPos;

// 第一个纹理
uniform sampler2D texture0;
// 第二个纹理
uniform sampler2D texture1;
// 混合比例
uniform float blendRatio;
// 立方体本身的环境光 光源颜色
uniform vec3 lightColor;
// 点光源位置
uniform vec3 lightPos;

out vec4 FragColor;

void main()
{
    // 环境光强度
    float ambientStrength = 0.2;
    // 计算环境光分量
    vec3 ambient = ambientStrength * lightColor;

    // 标准化法向量
    vec3 norm = normalize(Normal);
    // 计算片段位置和光源位置之间的方向向量
    vec3 lightDir = normalize(lightPos - FragPos);
    // 计算光源到片段的距离
    float distance = length(lightPos - FragPos);
    // 计算衰减
    float attenuation = 1.0 / (distance * distance);
    // 计算漫反射分量
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * attenuation;
 
    // 最终颜色结果
    vec3 lighting = ambient + diffuse;

    // 将两个纹理混合并乘以环境光分量
    FragColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), blendRatio) * vec4(lighting, 1.0);
}