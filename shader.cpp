#include "./shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

#include <glm/gtc/type_ptr.hpp>

void Shader::Load(const char *vertexPath, const char *fragmentPath)
{
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  vShaderFile.exceptions(std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::badbit);

  try
    {
      vShaderFile.open(vertexPath);
      fShaderFile.open(fragmentPath);

      std::stringstream vShaderStream, fShaderStream;

      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();

      vShaderFile.close();
      fShaderFile.close();

      vertexCode = vShaderStream.str();
      fragmentCode = fShaderStream.str();
    }
  catch(std::ifstream::failure e)
    {
      std::cout << "Couldn't read shader file" << std::endl;
    }

  const GLchar *vShaderCode = vertexCode.c_str();
  const GLchar *fShaderCode = fragmentCode.c_str();

  GLuint vertex, fragment;
  GLint success;
  GLchar infoLog[512];

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if(!success)
    {
      glGetShaderInfoLog(vertex, 512, NULL, infoLog);
      std::cout << "Vertex shader error: " << infoLog << std::endl;
    }

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if(!success)
    {
      glGetShaderInfoLog(fragment, 512, NULL, infoLog);
      std::cout << "Fragment shader error: " << infoLog << std::endl;
    }

  m_program = glCreateProgram();
  glAttachShader(m_program, vertex);
  glAttachShader(m_program, fragment);
  glLinkProgram(m_program);

  {
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if(success == false)
      {
	glGetProgramInfoLog(m_program, 512, NULL, infoLog);
	std::cout << "Couldn't link shader: " << infoLog << std::endl;
      }
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::SetUniformNames(std::vector<const char *> uniform_names) {
  m_uniform_handles.resize(uniform_names.size());

  for(size_t i = 0; i < uniform_names.size(); i++)
    {
      m_uniform_handles[i] = glGetUniformLocation(m_program, uniform_names[i]);
      if(m_uniform_handles[i] == -1)
	{
	  printf("Error: Couldn't get uniform location for: %s\n", uniform_names[i]);
	}
    }
}

void Shader::StartPassingUniforms()
{
  m_current_uniform_index = 0;
}

void Shader::SetUniform(glm::mat4& mat4)
{
  glUniformMatrix4fv(m_uniform_handles[m_current_uniform_index], 1, GL_FALSE, glm::value_ptr(mat4));
  m_current_uniform_index++;
}

void Shader::SetUniform(glm::vec3& vec3)
{
  glUniform3fv(m_uniform_handles[m_current_uniform_index], 1, glm::value_ptr(vec3));
  m_current_uniform_index++;
}

void Shader::Use()
{
  glUseProgram(m_program);
}
