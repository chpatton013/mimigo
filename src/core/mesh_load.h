#ifndef MESH_LOAD_H
#define MESH_LOAD_H

#include <string>

class GLMesh;
class EntityComponent;

GLMesh* LoadMeshFromFile(const std::string& filename);
EntityComponent* LoadEntityFromOBJFile(const std::string& filename);
GLMesh* MakeSquare();
EntityComponent* MakeCube(const std::string& name, const std::string& texture);

#endif
