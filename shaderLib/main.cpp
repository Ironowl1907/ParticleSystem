#include "../glad/include/glad/glad.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "shader.h"

void Shader::ParseFile(const std::string &filepath) {
  std::cout << "[SHADER INFO] Parsing file\n";
  std::ifstream file(filepath);
  if (!file) {
    std::cout << "[ERROR] No File\n";
    return;
  }
  std::stringstream ss[2];
  ShaderType type = ShaderType::NONE;

  std::string line;
  while (std::getline(file, line)) {
    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos) {
        std::cout << "[SHADER INFO] Found Vertex Shader\n";
        // Set mode to verte
        type = ShaderType::VERTEX;
      } else if (line.find("fragment") != std::string::npos) {
        std::cout << "[SHADER INFO] Found Fragment Shader\n";
        // Set mode to fragment
        type = ShaderType::FRAGMENT;
      }
    } else {
      if (type != ShaderType::NONE)
        ss[(int)type] << line << '\n';
    }
  }
  Shader::ShaderSource[(int)ShaderType::VERTEX] =
      ss[(int)ShaderType::VERTEX].str();
  Shader::ShaderSource[(int)ShaderType::FRAGMENT] =
      ss[(int)ShaderType::FRAGMENT].str();

  /*std::cout << "[Vertex] " << ShaderSource[0] << '\n'*/
  /*          << "[Fragment] " << ShaderSource[1] << '\n';*/
}

unsigned int Shader::CompileShader(unsigned int type) {
  // Create a shader with the type input
  unsigned int id = glCreateShader(type);
  // converting the source string to a cosnt char*
  std::string source = Shader::ShaderSource[(type == GL_VERTEX_SHADER) ? 0 : 1];
  const char *src = source.c_str();
  // Attach the shader source code to the shader object
  glShaderSource(id, 1, &src, nullptr);
  // Compile it
  glCompileShader(id);

  // Error handling
  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char *message = (char *)alloca(length * sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);
    std::cout << "[SHADER ERROR] Failed To Compile "
              << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
              << " Shader!\n";
    std::cout << message << '\n';
    glDeleteShader(id);
    return id;
  }

  return id;
}

void Shader::CreateShader() {
  Shader::ProgramID = glCreateProgram();
  unsigned int vs = CompileShader(GL_VERTEX_SHADER);
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER);

  glAttachShader(Shader::ProgramID, vs);
  glAttachShader(Shader::ProgramID, fs);
  glLinkProgram(Shader::ProgramID);
  glValidateProgram(Shader::ProgramID);

  glDeleteShader(vs);
  glDeleteShader(fs);
}
