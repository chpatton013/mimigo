#ifndef HANDLES_H_
#define HANDLES_H_

#include <map>
#include <string>
#include <vector>
#include "../core/material.h"

class Entity;
class EntityComposite;
class EntityComponent;
class OrthoEntity;
class Animation;
class GLShader;

extern bool zoe_mode;
extern bool win_mode;

extern const int kScreenWidth;
extern const int kScreenHeight;

extern std::map<std::string, int> g_handles;

extern EntityComposite* g_scene;
extern std::map<std::string, EntityComponent*> g_entities;
extern std::map<std::string, OrthoEntity*> g_ortho_entities;
extern std::map<std::string, Material> g_materials;
extern std::map<std::string, unsigned int> g_textures;
extern std::map<std::string, Animation*> g_animations;

extern std::map<std::string, int> g_shaders;

extern glm::mat4 projection;
extern std::vector<glm::vec4> p_planes;
extern int meshesDrawn;

#define GET_ATTRIB(program, attr) \
g_handles[std::string(attr)] = safe_glGetAttribLocation(program, attr);
#define GET_UNIFORM(program, uniform) \
g_handles[std::string(uniform)] = safe_glGetUniformLocation(program, uniform);

#endif
