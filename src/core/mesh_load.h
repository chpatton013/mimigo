#ifndef MESH_LOAD_H
#define MESH_LOAD_H

#include <string>
#include <vector>

class GLMesh;
class EntityComponent;

GLMesh* LoadMeshFromFile(const std::string& filename);
EntityComponent* LoadEntityComponentFromOBJ(const std::string& filename, const std::string& texture);
GLMesh* MakeSquare();
EntityComponent* MakeCube(const std::string& name, const std::string& texture);

#endif
