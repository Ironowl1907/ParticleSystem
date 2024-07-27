#include <string>

enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
class Shader {
private:
  std::string ShaderSource[2];

public:
  unsigned int ProgramID;
  void ParseFile(const std::string &filepath);

  unsigned int CompileShader(unsigned int type);
  void CreateShader();
};
