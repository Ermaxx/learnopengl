#pragma once

#include <vector>

#include <glm/glm.hpp>

class Shader
{
  unsigned int m_program;

  std::vector<int> m_uniform_handles;
  size_t m_current_uniform_index;

 public:

  void Load(const char *vertexPath, const char *fragmentPath);
  void Use();

  void SetUniformNames(std::vector<const char *> uniform_names);
  void StartPassingUniforms();
  void SetUniform(glm::mat4& mat4);
  void SetUniform(glm::vec3& vec3);
};
