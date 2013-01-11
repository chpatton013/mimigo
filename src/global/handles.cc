#include "handles.h"

const int kScreenWidth = 800;
const int kScreenHeight = 800;

std::map<std::string, int> g_handles;
EntityComposite* g_scene;
std::map<std::string, EntityComponent*> g_entities;
std::map<std::string, OrthoEntity*> g_ortho_entities;
std::map<std::string, Material> g_materials;
std::map<std::string, unsigned int> g_textures;
std::map<std::string, Animation*> g_animations;
std::map<std::string, int> g_shaders;
