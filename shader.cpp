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

void Shader::InitUniformPositions() {
  m_uniform[(int)ShaderUniform::ModelViewProjection] = glGetUniformLocation(m_program, "MVP");
  m_uniform[(int)ShaderUniform::Model] = glGetUniformLocation(m_program, "Normal");
  m_uniform[(int)ShaderUniform::LightDirection] = glGetUniformLocation(m_program, "lightDirection");
}

void Shader::SetUniforms(glm::mat4& MVP, glm::mat4& model, glm::vec3 lightDir) {
  glUniform3fv(m_uniform[(int)ShaderUniform::ModelViewProjection], 1, glm::value_ptr(MVP));
  glUniform3fv(m_uniform[(int)ShaderUniform::Model], 1, glm::value_ptr(model));
  glUniform3fv(m_uniform[(int)ShaderUniform::LightDirection], 1, glm::value_ptr(lightDir));
}

void Shader::Use()
{
  glUseProgram(m_program);
}



