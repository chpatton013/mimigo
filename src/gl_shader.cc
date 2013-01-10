#include "gl_shader.h"
#include <stdio.h>
#include <GL/gl.h>
#include "GLSL_helper.h"

GLShader::GLShader(const std::string& vert_shader_name,
                   const std::string& frag_shader_name) {
   Install(vert_shader_name, frag_shader_name);
}

bool GLShader::Install(const std::string& vert_shader_name,
                       const std::string& frag_shader_name) {
   GLchar* f_frag_shader = textFileRead((char*)frag_shader_name.c_str());
   GLchar* f_vertex_shader = textFileRead((char*)vert_shader_name.c_str());

   GLuint h_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
   GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

   //load the source
   glShaderSource(h_vertex_shader, 1, &f_vertex_shader, NULL);
   glShaderSource(frag_shader, 1, &f_frag_shader, NULL);

   //compile shader and print log
   glCompileShader(h_vertex_shader);
   /* check shader status requires helper functions */
   printOpenGLError();

   GLint vCompiled;
   glGetShaderiv(h_vertex_shader, GL_COMPILE_STATUS, &vCompiled);
   printShaderInfoLog(h_vertex_shader);

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
   program_handle_ = glCreateProgram();
   glAttachShader(program_handle_, h_vertex_shader);
   glAttachShader(program_handle_, frag_shader);

   glLinkProgram(program_handle_);
   /* check shader status requires helper functions */
   printOpenGLError();

   GLint linked; //status of shader
   glGetProgramiv(program_handle_, GL_LINK_STATUS, &linked);
   printProgramInfoLog(program_handle_);

   glUseProgram(program_handle_);

   /* get handles to attribute data */
   GET_ATTRIB(program_handle_, "aPosition");
   GET_ATTRIB(program_handle_, "aAmbient");
   GET_ATTRIB(program_handle_, "aDiffuse");
   //GET_ATTRIB(program_handle_, "aSpecular");
   GET_ATTRIB(program_handle_, "aNormal");
   GET_ATTRIB(program_handle_, "aTexture");

   GET_UNIFORM(program_handle_, "uProjMatrix");
   GET_UNIFORM(program_handle_, "uViewMatrix");
   GET_UNIFORM(program_handle_, "uModelMatrix");
   GET_UNIFORM(program_handle_, "uNormalMatrix");
   GET_UNIFORM(program_handle_, "uLights");
   GET_UNIFORM(program_handle_, "uTextureUnit");
   GET_UNIFORM(program_handle_, "uCelShaderUnit");
   GET_UNIFORM(program_handle_, "uUseTexture");
   //GET_UNIFORM(program_handle_, "uCameraPosition");

   printf("%s and %s loaded and using: %d\n",
      frag_shader_name.c_str(), vert_shader_name.c_str(), program_handle_);
   return true;
}
