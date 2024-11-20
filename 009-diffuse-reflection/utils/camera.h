#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// 定义摄像机移动的几种可能选项
enum Camera_Movement {
    FORWARD, // 向前
    BACKWARD, // 向后
	LEFT, // 向左
    RIGHT, // 向右
    UP, // 向上
    DOWN, // 向下
    ROLL_LEFT, // 左旋转
    ROLL_RIGHT, // 右旋转
    PITCH_UP, // 向上俯仰
    PITCH_DOWN, // 向下俯仰
    YAW_LEFT, // 向左偏航
    YAW_RIGHT, // 向右偏航
};

// 摄像机默认参数
// 偏航角
const float YAW = -90.0f;
// 俯仰角
const float PITCH = 0.0f;
// 滚转角
const float ROLL = 0.0f;
// 移动速度
const float SPEED = 12.5f;
// 鼠标灵敏度
const float SENSITIVITY = 0.1f;
// 缩放
const float ZOOM = 45.0f;

// 摄像机类
class Camera {
public:
    // 位置
    glm::vec3 Position;
    // 前向量
    glm::vec3 Front;
    // 上向量
    glm::vec3 Up;
    // 右向量
    glm::vec3 Right;
    // 世界上向量
    glm::vec3 WorldUp;
    
    // 偏航角，控制摄像机左右旋转
    float Yaw;
    // 俯仰角，控制摄像机上下旋转
    float Pitch;
    // 滚转角，控制摄像机的左右倾斜
    float Roll;
    
    // 移动速度
    float MovementSpeed;
    // 鼠标灵敏度
    float MouseSensitivity;
    // 缩放
    float Zoom;
    
    // 使用向量的构造函数
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH, float roll = ROLL) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        Roll = roll;
        updateCameraVectors();
    }
    // 使用标量的构造函数
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch, float roll = ROLL) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        Roll = roll;
        updateCameraVectors();
    }
    
    // 返回使用前向量和上向量以计算的视图矩阵
    glm::mat4 GetViewMatrix() {
        return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
    }
    
    // 处理键盘输入
    void ProcessKeyboard(Camera_Movement direction, float deltaTime) {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD) 
            this->Position += this->Front * velocity;
        if (direction == BACKWARD) 
            this->Position -= this->Front * velocity;
        if (direction == LEFT)
            this->Position -= this->Right * velocity;
        if (direction == RIGHT) 
            this->Position += this->Right * velocity;
        if (direction == UP)
            this->Position += this->Up * velocity;
        if (direction == DOWN)
            this->Position -= this->Up * velocity;
        if (direction == ROLL_LEFT)
            this->Roll -= velocity;
        if (direction == ROLL_RIGHT)
            this->Roll += velocity;
        if (direction == PITCH_UP)
            this->Pitch += velocity;
        if (direction == PITCH_DOWN)
            this->Pitch -= velocity;
        if (direction == YAW_LEFT)
            this->Yaw -= velocity;
        if (direction == YAW_RIGHT)
            this->Yaw += velocity;
        
        updateAngles();
        updateCameraVectors();
    }
    
    // 处理鼠标的移动
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        this->Yaw += xoffset;
        this->Pitch += yoffset;

        // 确保当前俯仰角超出范围时，屏幕不会翻转
        if (constrainPitch) {
            if (this->Pitch > 89.0f)
                this->Pitch = 89.0f;
            if (this->Pitch < -89.0f)
                this->Pitch = -89.0f;
        }

        // 使用更新的欧拉角更新前向量、右向量和上向量
        updateCameraVectors();
    }

    // 处理鼠标滚轮事件，只处理在垂直滚轮轴上的输入
    void ProcessMouseScroll(float yoffset) {
        this->Zoom -= (float)yoffset;
        if (this->Zoom < 1.0f) 
            this->Zoom = 1.0f;
        if (this->Zoom > 45.0f)
            this->Zoom = 45.0f;
    }
    
private:
    // 更新角度，确保俯仰角在合理范围内
    void updateAngles() {
        if (this->Pitch > 89.9f)
            this->Pitch = 89.9f;
        if (this->Pitch < -89.9f) 
            this->Pitch = -89.9f;
    }
    // 更新前向量，上向量和右向量
    void updateCameraVectors() {
        // 计算新的前向量
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        this->Front = glm::normalize(front);
        
        // 计算新的右向量
        this->Right = glm::normalize(glm::cross(Front, WorldUp));
        glm::mat4 rollMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(this->Roll), this->Front);
        this-> Right = glm::vec3(rollMatrix * glm::vec4(this->Right, 0.0f));
        
        // 计算新的上向量
        Up = glm::normalize(glm::cross(this->Right, this->Front));
    }
};
#endif