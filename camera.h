#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

enum Camera_Movement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
};

class Camera
{
 public:
  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Up;
  glm::vec3 Right;
  glm::vec3 WorldUp;

  GLfloat Yaw;
  GLfloat Pitch;
  GLfloat MovementSpeed;
  GLfloat MouseSensitivity;
  GLfloat Zoom;

  void Init(glm::vec3 position);

  glm::mat4 GetViewMatrix();

  void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
  void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset);

  void UpdateCameraVectors();
};
