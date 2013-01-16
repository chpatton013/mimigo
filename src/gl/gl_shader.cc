#include <stdio.h>
#include "gl_shader.h"
#include "../global/handles.h"
#include "../gl/GLSL_helper.h"

GLShader::GLShader(const std::string& shader_name,
                   const std::string& vert_shader_name,
                   const std::string& frag_shader_name) {
   Install(shader_name, vert_shader_name, frag_shader_name);
}

bool GLShader::Install(const std::string& shader_name,
                       const std::string& vert_shader_name,
                       const std::string& frag_shader_name) {
   const GLchar* f_frag_shader = textFileRead((char*)frag_shader_name.c_str());
   const GLchar* f_vertex_shader = textFileRead((char*)vert_shader_name.c_str());

   GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
   GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
   assert(vertex_shader);
   assert(frag_shader);

   //load the source
   glShaderSource(vertex_shader, 1, &f_vertex_shader, NULL);
   glShaderSource(frag_shader, 1, &f_frag_shader, NULL);

   //compile shader and print log
   glCompileShader(vertex_shader);
   /* check shader status requires helper functions */
   printOpenGLError();

   GLint vCompiled;
   glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vCompiled);
   printShaderInfoLog(vertex_shader);

   //compile shader and print log
   glCompileShader(frag_shader);
   /* check shader status requires helper functions */
   printOpenGLError();
   GLint fCompiled;
   glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &fCompiled);
   printShaderInfoLog(frag_shader);

   if (!vCompiled || !fCompiled) {
      printf("Error compiling either shader %s or %s",
             f_vertex_shader, f_frag_shader);
      return false;
   }

   //create a program object and attach the compiled shader
   int program_handle = glCreateProgram();
   assert(program_handle);
   glAttachShader(program_handle, vertex_shader);
   glAttachShader(program_handle, frag_shader);

   glLinkProgram(program_handle);
   /* check shader status requires helper functions */
   printOpenGLError();

   GLint linked; //status of shader
   glGetProgramiv(program_handle, GL_LINK_STATUS, &linked);
   printProgramInfoLog(program_handle);

   glUseProgram(program_handle);

   /* get handles to attribute data */
   GET_ATTRIB(program_handle, "aPosition");
   //GET_ATTRIB(program_handle, "aAmbient");
   //GET_ATTRIB(program_handle, "aDiffuse");
   //GET_ATTRIB(program_handle, "aSpecular");
   GET_ATTRIB(program_handle, "aNormal");
   //GET_ATTRIB(program_handle, "aTexture");

   //GET_UNIFORM(program_handle, "uProjMatrix");
   GET_UNIFORM(program_handle, "uViewMatrix");
   GET_UNIFORM(program_handle, "uModelMatrix");
   GET_UNIFORM(program_handle, "uNormalMatrix");
   //GET_UNIFORM(program_handle, "uLights");
   //GET_UNIFORM(program_handle, "uTextureUnit");
   //GET_UNIFORM(program_handle, "uCelShaderUnit");
   //GET_UNIFORM(program_handle, "uUseTexture");
   //GET_UNIFORM(program_handle, "uCameraPosition");

   assert(program_handle > 0);
   g_shaders[shader_name] = program_handle;
   return true;
}
