#pragma once
#include "windowFactory.h"
#include "shader.h"
#include <vector>
#include <cmath>
#include "glm/glm.hpp" 
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "objModel.h"

using std::string;
using std::vector;  

class RectangleModel {
    // 光结构体
    struct DirectionalLight {
        // 光的方向
        glm::vec3 direction;
        // 环境光分量
        glm::vec3 ambient;
        // 漫反射光分量
        glm::vec3 diffuse;
        // 镜面反射光分量
        glm::vec3 specular;
        // 光的颜色
        glm::vec3 lightColor;
    };
    // 模型信息结构体
    struct ModelInfo {
        // 模型位置
        glm::vec3 position;
        // 模型旋转
        glm::vec3 rotation;
        // 模型缩放
        glm::vec3 scale;
        // 模型文件路径
        string path;
        // 模型指针
        Model* model = nullptr;
    };

    // 点光源结构体
    struct PointLight {
        // 模型文件路径
        string path;
        // 模型指针
        Model* model = nullptr;

        // 点光源位置
        glm::vec3 position;
        // 环境光分量
        glm::vec3 ambient;
        // 漫反射光分量
        glm::vec3 diffuse;
        // 镜面反射光分量
        glm::vec3 specular;
        // 光的颜色
        glm::vec3 lightColor;
        // 常数衰减
        float constant;
        // 线性衰减
        float linear;
        // 二次衰减
        float quadratic;
    };

public:
    // 构造函数
    RectangleModel(GLFWWindowFactory* window);
    // 析构函数
    ~RectangleModel();

    // 绘制函数
    void draw();
    // 加载场景函数
    vector<ModelInfo> loadScene(const std::string& fileName);
    // 加载定向光函数
    vector<DirectionalLight> loadDirectionalLights(const string& filePath);
    // 加载点光源函数
    vector<PointLight> loadPointLights(const string& filePath);

private:
    // 着色器
    Shader shader;
    // 灯光着色器
    Shader lightShader;
    // 纹理
    vector<unsigned int> textures;
    // 窗口指针
    GLFWWindowFactory* window;

    // 模型信息列表
    vector<ModelInfo> modelInfos;
    // 定向光列表
    vector<DirectionalLight> directionalLights;
    // 点光源列表
    vector<PointLight> pointLights;
};