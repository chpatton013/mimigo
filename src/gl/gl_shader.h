#ifndef _GL_SHADER_H_
#define _GL_SHADER_H_

#include <string>

class GLShader {
  public:
   GLShader(const std::string& shader_name,
            const std::string& vert_shader_name,
            const std::string& frag_shader_name);
  private:
   static bool Install(const std::string& shader_name,
                const std::string& vert_shader_name,
                const std::string& frag_shader_name);
};

#endif
