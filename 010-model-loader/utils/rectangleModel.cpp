#include "rectangleModel.h"
#include <iostream>
#include <yaml-cpp/yaml.h>

using std::cout;
using std::endl;
using std::cerr;

// 构造函数
RectangleModel::RectangleModel(GLFWWindowFactory* window) : window(window) {
    // 加载定向光信息
    this->directionalLights = loadDirectionalLights("config/directionalLights.yaml");
    // 加载光源信息
    this->pointLights = loadPointLights("config/pointLights.yaml");
    // 加载场景信息
    this->modelInfos = loadScene("config/scene.yaml");

    // 为每个模型信息创建模型对象
    for (auto &modelInfo : this->modelInfos) {
        modelInfo.model = new Model(modelInfo.path);
    }

    // 初始化着色器
    this->shader = Shader("shader.vs", "shader.fs");
}

// 析构函数
RectangleModel::~RectangleModel() {}

// 绘制函数
void RectangleModel::draw() {
    // 使用着色器
    this->shader.use();

    // 设置定向光数量
    this->shader.setInt("numDirectionalLights", this->directionalLights.size());
    // 设置每个定向光的属性
    for (auto i = 0; i < this->directionalLights.size(); i++) {
        string number = std::to_string(i);
        this->shader.setVec3("directionalLights[" + number + "].direction", this->directionalLights[i].direction);
        this->shader.setVec3("directionalLights[" + number + "].ambient", this->directionalLights[i].ambient);
        this->shader.setVec3("directionalLights[" + number + "].diffuse", this->directionalLights[i].diffuse);
        this->shader.setVec3("directionalLights[" + number + "].specular", this->directionalLights[i].specular);
        this->shader.setVec3("directionalLights[" + number + "].lightColor", this->directionalLights[i].lightColor);
    }

    // 设置点光源数量
    this->shader.setInt("numPointLights", this->pointLights.size());
    // 设置每个点光源的属性
    for (auto i = 0; i < this->pointLights.size(); i++) {
        string number = std::to_string(i);
        this->shader.setVec3("pointLights[" + number + "].position", this->pointLights[i].position);
        this->shader.setVec3("pointLights[" + number + "].ambient", this->pointLights[i].ambient);
        this->shader.setVec3("pointLights[" + number + "].diffuse", this->pointLights[i].diffuse);
        this->shader.setVec3("pointLights[" + number + "].specular", this->pointLights[i].specular);
        this->shader.setFloat("pointLights[" + number + "].constant", this->pointLights[i].constant);
        this->shader.setFloat("pointLights[" + number + "].linear", this->pointLights[i].linear);
        this->shader.setFloat("pointLights[" + number + "].quadratic", this->pointLights[i].quadratic);
        this->shader.setVec3("pointLights[" + number + "].lightColor", this->pointLights[i].lightColor);
    }

    // 绘制每个模型
    for (const auto &modelInfo : this->modelInfos) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, modelInfo.position);
        model = glm::rotate(model, glm::radians(modelInfo.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(modelInfo.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(modelInfo.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, modelInfo.scale);

        this->shader.setMat4("model", model);
        modelInfo.model->draw(this->shader);
    }

    // 设置投影矩阵和视图矩阵
    this->shader.setMat4("projection", this->window->getProjectionMatrix());
    this->shader.setMat4("view", this->window->getViewMatrix());
    auto camera = this->window->camera;
    this->shader.setVec3("viewPos", camera.Position);
    this->shader.setFloat("shininess", 32.0f);
}

// 加载定向光信息
vector<RectangleModel::DirectionalLight> RectangleModel::loadDirectionalLights(const string& filePath) {
    vector<DirectionalLight> directionalLights;
    try {
        YAML::Node scene = YAML::LoadFile(filePath);
        if (scene["directionalLights"]) {
            for (size_t i = 0; i < scene["directionalLights"].size(); i++) {
                DirectionalLight light;
                light.direction.x = scene["directionalLights"][i]["direction"]["x"].as<float>();
                light.direction.y = scene["directionalLights"][i]["direction"]["y"].as<float>();
                light.direction.z = scene["directionalLights"][i]["direction"]["z"].as<float>();
                light.ambient.x = scene["directionalLights"][i]["ambient"]["x"].as<float>();
                light.ambient.y = scene["directionalLights"][i]["ambient"]["y"].as<float>();
                light.ambient.z = scene["directionalLights"][i]["ambient"]["z"].as<float>();
                light.diffuse.x = scene["directionalLights"][i]["diffuse"]["x"].as<float>();
                light.diffuse.y = scene["directionalLights"][i]["diffuse"]["y"].as<float>();
                light.diffuse.z = scene["directionalLights"][i]["diffuse"]["z"].as<float>();
                light.specular.x = scene["directionalLights"][i]["specular"]["x"].as<float>();
                light.specular.y = scene["directionalLights"][i]["specular"]["y"].as<float>();
                light.specular.z = scene["directionalLights"][i]["specular"]["z"].as<float>();
                light.lightColor.x = scene["directionalLights"][i]["lightColor"]["x"].as<float>();
                light.lightColor.y = scene["directionalLights"][i]["lightColor"]["y"].as<float>();
                light.lightColor.z = scene["directionalLights"][i]["lightColor"]["z"].as<float>();
                directionalLights.push_back(light);
            }
        }
    } catch (const YAML::Exception& e) {
        cerr << "YAML Exception: " << e.what() << endl;
    }

    return directionalLights;
}

// 加载点光源信息
vector<RectangleModel::PointLight> RectangleModel::loadPointLights(const string& filePath) {
    vector<PointLight> pointLights;
    try {
        YAML::Node scene = YAML::LoadFile(filePath);
        if (scene["pointLights"]) {
            for (size_t i = 0; i < scene["pointLights"].size(); i++) {
                PointLight light;
                light.position.x = scene["pointLights"][i]["position"]["x"].as<float>();
                light.position.y = scene["pointLights"][i]["position"]["y"].as<float>();
                light.position.z = scene["pointLights"][i]["position"]["z"].as<float>();
                light.constant = scene["pointLights"][i]["constant"].as<float>();
                light.linear = scene["pointLights"][i]["linear"].as<float>();
                light.quadratic = scene["pointLights"][i]["quadratic"].as<float>();
                light.ambient.x = scene["pointLights"][i]["ambient"]["x"].as<float>();
                light.ambient.y = scene["pointLights"][i]["ambient"]["y"].as<float>();
                light.ambient.z = scene["pointLights"][i]["ambient"]["z"].as<float>();
                light.diffuse.x = scene["pointLights"][i]["diffuse"]["x"].as<float>();
                light.diffuse.y = scene["pointLights"][i]["diffuse"]["y"].as<float>();
                light.diffuse.z = scene["pointLights"][i]["diffuse"]["z"].as<float>();
                light.specular.x = scene["pointLights"][i]["specular"]["x"].as<float>();
                light.specular.y = scene["pointLights"][i]["specular"]["y"].as<float>();
                light.specular.z = scene["pointLights"][i]["specular"]["z"].as<float>();
                light.lightColor.x = scene["pointLights"][i]["lightColor"]["x"].as<float>();
                light.lightColor.y = scene["pointLights"][i]["lightColor"]["y"].as<float>();
                light.lightColor.z = scene["pointLights"][i]["lightColor"]["z"].as<float>();
                pointLights.push_back(light);
            }
        }
    } catch (const YAML::Exception& e) {
        cerr << "YAML Exception: " << e.what() << endl;
    }

    return pointLights;
}

// 加载场景信息
vector<RectangleModel::ModelInfo> RectangleModel::loadScene(const string& filePath) {
    vector<ModelInfo> models;
    try {
        YAML::Node scene = YAML::LoadFile(filePath);
        if (scene["models"]) {
            for (size_t i = 0; i < scene["models"].size(); i++) {
                ModelInfo info;
                info.path = scene["models"][i]["path"].as<string>();
                info.position.x = scene["models"][i]["position"]["x"].as<float>();
                info.position.y = scene["models"][i]["position"]["y"].as<float>();
                info.position.z = scene["models"][i]["position"]["z"].as<float>();
                info.rotation.x = scene["models"][i]["rotation"]["x"].as<float>();
                info.rotation.y = scene["models"][i]["rotation"]["y"].as<float>();
                info.rotation.z = scene["models"][i]["rotation"]["z"].as<float>();
                info.scale.x = scene["models"][i]["scale"]["x"].as<float>();
                info.scale.y = scene["models"][i]["scale"]["y"].as<float>();
                info.scale.z = scene["models"][i]["scale"]["z"].as<float>();
                models.push_back(info);

                // 输出模型信息
                cout << "Model Path: " << info.path << endl;
                cout << "Model Position: (" << info.position.x << ", " << info.position.y << ", " << info.position.z << ")" << endl;
                cout << "Model Rotation: (" << info.rotation.x << ", " << info.rotation.y << ", " << info.rotation.z << ")" << endl;
                cout << "Model Scale: (" << info.scale.x << ", " << info.scale.y << ", " << info.scale.z << ")" << endl;
            }
        }
    } catch (const YAML::BadFile& e) {
        cerr << "Error: Unable to open file" << filePath << endl;
    } catch (const YAML::ParserException& e) {
        cerr << "Error: Parsing faild: " << e.what() << endl;
    }

    return models;
}
