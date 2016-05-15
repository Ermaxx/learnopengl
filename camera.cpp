#include "./camera.h"

#include <glm/gtc/matrix_transform.hpp>

const GLfloat YAW = 90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;

void Camera::Init(glm::vec3 position)
{
  Position = position;
  WorldUp = glm::vec3(0, 1, 0);
  Yaw = YAW;
  Pitch = PITCH;

  UpdateCameraVectors();

  MovementSpeed = SPEED;
  MouseSensitivity = SENSITIVITY;
  Zoom = ZOOM;

}

glm::mat4 Camera::GetViewMatrix()
{
  return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
  GLfloat velocity = MovementSpeed * deltaTime;
  if(direction == FORWARD)
    {
      Position += Front * velocity;
    }
  else if(direction == BACKWARD)
    {
      Position -= Front * velocity;
    }
  else if(direction == LEFT)
    {
      Position -= Right * velocity;
    }
  else if(direction == RIGHT)
    {
      Position += Right * velocity;
    }
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset)
{
  xoffset *= MouseSensitivity;
  yoffset *= MouseSensitivity;

  Yaw += xoffset;
  Pitch -= yoffset;

  if(Pitch > 89.0) {
      Pitch = 89.0;
    }
  if(Pitch < -89.0)
    {
      Pitch = -89.0;
    }
  UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
  glm::vec3 front;
  front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  front.y = sin(glm::radians(Pitch));
  front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  Front = glm::normalize(front);
  Right = glm::normalize(glm::cross(Front, WorldUp));
  Up = glm::normalize(glm::cross(Right, Front));
}
