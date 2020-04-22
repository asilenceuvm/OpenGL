#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera {
public:
    Camera() {
        cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    }

    void moveCamForward(const float delta) {
        cameraPos += delta * cameraFront;
    }
    void moveCamBack(const float delta) {
        cameraPos -= delta * cameraFront;
    }
    void moveCamLeft(const float delta) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * delta;
    }
    void moveCamRight(const float delta) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * delta;
    }

    void rotateCamera(float xoffset, float yoffset, float sensitivity) {
        yaw += xoffset * sensitivity;
        pitch += yoffset * sensitivity;

        //clamp y look
        if (pitch > 89.0f) {
            pitch = 89.0f;
        }
        if (pitch < -89.0f) {
            pitch = -89.0f;
        }
        
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);
    }

    glm::vec3 getCameraPos() {
        return cameraPos;
    }

    glm::vec3 getCameraFront() {
        return cameraFront;
    }

    glm::vec3 getCameraUp() {
        return cameraUp;
    }
private:
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    glm::vec3 direction;
    float yaw, pitch;
};