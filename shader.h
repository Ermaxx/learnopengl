#pragma once

#include <glm/glm.hpp>

enum class ShaderUniform {
  ModelViewProjection = 0,
  Model = 1,
  LightDirection = 2,
  Max = 3,
};

class Shader
{
 public:
  int m_uniform[(int)ShaderUniform::Max];
  
  unsigned int m_program;

  void Load(const char *vertexPath, const char *fragmentPath);
  void Use();

  void InitUniformPositions();
  void SetUniforms(glm::mat4& MVP, glm::mat4& model, glm::vec3 lightDir);
};
