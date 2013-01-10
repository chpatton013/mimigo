#include "global/handles.h"

const int kScreenWidth = 800;
const int kScreenHeight = 800;

std::map<std::string, GLint> g_handles;
EntityComposite* g_scene;
std::map<std::string, EntityComponent*> g_entities;
std::map<std::string, OrthoEntity*> g_ortho_entities;
std::map<std::string, Material> g_materials;
std::map<std::string, unsigned int> g_textures;
std::map<std::string, Ornament*> g_ornaments;
std::map<std::string, Animation*> g_animations;
int g_shader_program;
