#pragma once

class Shader
{
 public:
  unsigned int m_program;

  void Load(const char *vertexPath, const char *fragmentPath);

  void Use();
};
