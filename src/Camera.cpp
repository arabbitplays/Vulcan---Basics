//
// Created by oster on 14.09.2024.
//

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/detail/type_quat.hpp>
#include "Camera.hpp"
#include "SDL3/SDL.h"

void Camera::update() {
    glm::mat4 cameraRotation = getRotationMatrix();
    position += glm::vec3(cameraRotation * glm::vec4(velocity * 0.5f, 0.f));
}

void Camera::processSDLEvent(SDL_Event &e) {
    if (e.type == SDL_EVENT_KEY_DOWN) {
        if (e.key.key == SDLK_W) { velocity.z = -1; }
        if (e.key.key == SDLK_S) { velocity.z = 1; }
        if (e.key.key == SDLK_A) { velocity.x = -1; }
        if (e.key.key == SDLK_D) { velocity.x = 1; }
    }

    if (e.type == SDL_EVENT_KEY_UP) {
        if (e.key.key == SDLK_W) { velocity.z = 0; }
        if (e.key.key == SDLK_S) { velocity.z = 0; }
        if (e.key.key == SDLK_A) { velocity.x = 0; }
        if (e.key.key == SDLK_D) { velocity.x = 0; }
    }

    if (e.type == SDL_EVENT_MOUSE_MOTION) {
        yaw += (float)e.motion.xrel / 200.f;
        pitch -= (float)e.motion.yrel / 200.f;
    }
}

glm::mat4 Camera::getViewMatrix() {
    // to create a correct model view, we need to move the world in opposite
    // direction to the camera
    // so we will create the camera model matrix and invert
    glm::mat4 cameraTranslation = glm::translate(glm::mat4(1.f), position);
    glm::mat4 cameraRotation = getRotationMatrix();
    return glm::inverse(cameraTranslation * cameraRotation);
}

glm::mat4 Camera::getRotationMatrix() {
    glm::quat pitchRotation = glm::angleAxis(pitch, glm::vec3( 1.f, 0.f, 0.f));
    glm::quat yawRotation = glm::angleAxis(yaw, glm::vec3( 0.f, -1.f, 0.f));

    return glm::toMat4(yawRotation) * glm::toMat4(pitchRotation);
}
