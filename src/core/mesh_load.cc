#include "mesh_load.h"

#include "rotation.h"
#include "gl/gl_mesh.h"
#include "global/handles.h"
#include "util/stl_util.h"
#include "util/glm_util.h"

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <fstream>

double average(double a, double b) {
   return (a + b) / 2.0;
}

// Strips until |delim| is encountered. Returns what has been stripped.
std::string LeftStrip(std::istream& in, char delim=' ') {
   std::string stripped_text;
   getline(in, stripped_text, delim);
   return stripped_text;
}

// Parse functions //
double ParseSingleColorValue(std::istream& in) {
   double value = 0;
   in >> value;
   LeftStrip(in); // Strip the ', '
   return value;
}

int ParseVertexIndex(std::istream& in) {
   int index;
   in >> index;
   return index - 1; // Indices in the .m file are 1-based.
}

GLMesh::Face ParseFace(std::istream& line) {
   GLMesh::Face face;
   face.v1 = ParseVertexIndex(line);
   face.v2 = ParseVertexIndex(line);
   face.v3 = ParseVertexIndex(line);
   return face;
}

glm::vec4 ParsePosition(std::istream& line) {
   glm::vec4 vertex;
   line >> vertex.x;
   line >> vertex.y;
   line >> vertex.z;
   vertex.w = 1.0;
   return vertex;
}

glm::vec2 ParseTextureCoord(std::istream& line) {
   glm::vec2 tc;
   line >> tc.x;
   line >> tc.y;
   return tc;
}

glm::vec3 ParseNormal(std::istream& line) {
   glm::vec3 normal;
   line >> normal.x;
   line >> normal.y;
   line >> normal.z;
   return normal;
}

GLMesh::Face ParseOBJFace(const std::string& line,
      std::vector<Vertex>& verts,
      std::vector<glm::vec2>& textures,
      std::vector<glm::vec3>& normals,
      const std::string& material) {
   GLMesh::Face f;
   int t1, t2, t3, n1, n2, n3;
   sscanf(line.c_str(), "f %lu/%d/%d %lu/%d/%d %lu/%d/%d ",
    &f.v1, &t1, &n1, &f.v2, &t2, &n2, &f.v3, &t3, &n3);

   f.v1--; f.v2--; f.v3--;
   t1--; t2--; t3--;
   n1--; n2--; n3--;

   verts[f.v1].texture = textures[t1];
   verts[f.v2].texture = textures[t2];
   verts[f.v3].texture = textures[t3];

   verts[f.v1].normal = normals[n1];
   verts[f.v2].normal = normals[n2];
   verts[f.v3].normal = normals[n3];

   verts[f.v1].set_material(g_materials[material]);
   verts[f.v2].set_material(g_materials[material]);
   verts[f.v3].set_material(g_materials[material]);

   return f;
}

void ParseMaterials(const std::string& fname) {
   std::ifstream file;
   file.open(fname.c_str());
   Material m;
   const std::string kNewHeader("newmtl");

   while (file.good()) {
      std::string line;
      getline(file, line);
      std::istringstream line_stream(line);

      std::string header(LeftStrip(line_stream));
      if (header == kNewHeader) {
         if (!m.name.empty()) {
            g_materials[m.name] = m;
         }
         line_stream >> m.name;
      } else if (header == "Kd") {
         m.kDiffuse = ParseNormal(line_stream);
      } else if (header == "Ks") {
         m.kSpecular = ParseNormal(line_stream);
      } else if (header == "Ka") {
         m.kAmbient = ParseNormal(line_stream);
      } else {
      }
   }
   g_materials[m.name] = m;
}

// Parse functions //

std::vector<GLMesh*> LoadMeshesFromOBJFile(const std::string& filename) {
   std::vector<GLMesh*> meshes;
   const std::string kCommentHeader("#");
   const std::string kTextureHeader("vt");
   const std::string kNormalHeader("vn");
   const std::string kVertexHeader("v");
   const std::string kFaceHeader("f");
   const std::string kMTLLibHeader("mtllib");
   const std::string kMTLNameHeader("usemtl");

   std::ifstream file;
   file.open(filename.c_str());
   if (!file.is_open()) {
      fprintf(stderr, "failed to open mesh file %s\n", filename.c_str());
      return std::vector<GLMesh*>();
   }

   std::vector<Vertex> verts;
   std::vector<GLMesh::Face> faces;
   std::vector<glm::vec3> normals;
   std::vector<glm::vec2> texture_coords;
   std::string material;
   bool parsing_faces = false;
   while (file.good()) {
      std::string line;
      getline(file, line);
      std::istringstream line_stream(line);

      std::string header(LeftStrip(line_stream));
      if (header == kCommentHeader) {
      } else if (header == kVertexHeader) {
         if (parsing_faces) {
            meshes.push_back(new GLMesh(verts, faces, normals,
             texture_coords));
            verts.clear();
            faces.clear();
            normals.clear();
            texture_coords.clear();
            parsing_faces = false;
         }
         verts.push_back(ParsePosition(line_stream));
      } else if (header == kFaceHeader) {
         faces.push_back(ParseOBJFace(line, verts, texture_coords,
                  normals, material));
      } else if (header == kNormalHeader) {
         normals.push_back(ParseNormal(line_stream));
      } else if (header == kTextureHeader) {
         texture_coords.push_back(ParseTextureCoord(line_stream));
         parsing_faces = true;
      } else if (header == kMTLLibHeader) {
         std::string fname;
         line_stream >> fname;
         ParseMaterials(fname);
      } else if (header == kMTLNameHeader) {
         line_stream >> material;
      } else {
      }
   }
   meshes.push_back(new GLMesh(verts, faces, normals, texture_coords));
   return meshes;
}

GLMesh* LoadMeshFromFile(const std::string& filename) {
   const std::string kCommentHeader("#");
   const std::string kVertexHeader("Vertex");
   const std::string kFaceHeader("Face");

   std::ifstream file;
   file.open(filename.c_str());
   if (!file.is_open()) {
      fprintf(stderr, "failed to open mesh file %s\n", filename.c_str());
      return NULL;
   }

   GLMesh::VertexList verts;
   GLMesh::FaceList faces;
   while (file.good()) {
      std::string line;
      getline(file, line);
      std::istringstream line_stream(line);

      std::string header(LeftStrip(line_stream));
      if (header == kCommentHeader) {
      } else if (header == kVertexHeader) {
         LeftStrip(line_stream);
         verts.push_back(ParsePosition(line_stream));
      } else if (header == kFaceHeader) {
         LeftStrip(line_stream); // Strips the index.
         faces.push_back(ParseFace(line_stream));
      } else {
      }
   }

   file.close();
   return new GLMesh(verts, faces,
    std::vector<glm::vec3>(), std::vector<glm::vec2>());
}

static GLMesh* square = NULL;
GLMesh* MakeSquare() {
   if (square)
      return square;

   GLMesh::VertexList verts;
   GLMesh::FaceList faces;
   verts.push_back(glm::vec4(-0.5, -0.5, 0.0, 1.0)); //0
   verts.push_back(glm::vec4(0.5, -0.5, 0.0, 1.0));  //1
   verts.push_back(glm::vec4(-0.5, 0.5, 0.0, 1.0));  //2
   verts.push_back(glm::vec4(0.5, 0.5, 0.0, 1.0));   //3

   verts[0].texture = glm::vec2(0.0, 0.0);
   verts[1].texture = glm::vec2(1.0, 0.0);
   verts[2].texture = glm::vec2(0.0, 1.0);
   verts[3].texture = glm::vec2(1.0, 1.0);

   verts[0].normal = glm::vec3(0.0, 0.0, 1.0);
   verts[1].normal = glm::vec3(0.0, 0.0, 1.0);
   verts[2].normal = glm::vec3(0.0, 0.0, 1.0);
   verts[3].normal = glm::vec3(0.0, 0.0, 1.0);

   faces.push_back(GLMesh::Face(0, 1, 2));
   faces.push_back(GLMesh::Face(2, 1, 3));

   square = new GLMesh(verts, faces,
    std::vector<glm::vec3>(), std::vector<glm::vec2>());
   return square;
}

/*
EntityComponent* MakeCube(const std::string& name, const std::string& texture) {
   if (stl_util::ContainsKey(g_entities, name))
      return g_entities[name];
   GLMesh* square = MakeSquare();
   std::vector<GLMesh*> meshes;
   glm::mat4 trans;

   meshes.push_back(new GLMesh(*square));
   trans = glm::translate(trans, glm::vec3(0.0, 0.0, -0.5));
   trans = glm::rotate(trans, 180.0f, glm::vec3(1.0, 0.0, 0.0));
   meshes.back()->transform(trans);

   meshes.push_back(new GLMesh(*square));
   trans = glm::translate(glm::mat4(), glm::vec3(0.0, 0.0, 0.5));
   trans = glm::rotate(trans, 0.0f, glm::vec3(1.0, 0.0, 0.0));
   meshes.back()->transform(trans);

   meshes.push_back(new GLMesh(*square));
   trans = glm::mat4();
   trans = glm::translate(trans, glm::vec3(0.0, -0.5, 0.0));
   trans = glm::rotate(trans, 90.0f, glm::vec3(1.0, 0.0, 0.0));
   meshes.back()->transform(trans);

   meshes.push_back(new GLMesh(*square));
   trans = glm::mat4();
   trans = glm::translate(trans, glm::vec3(0.0, 0.5, 0.0));
   trans = glm::rotate(trans, -90.0f, glm::vec3(1.0, 0.0, 0.0));
   meshes.back()->transform(trans);

   meshes.push_back(new GLMesh(*square));
   trans = glm::mat4();
   trans = glm::translate(trans, glm::vec3(0.5, 0.0, 0.0));
   trans = glm::rotate(trans, 90.0f, glm::vec3(0.0, 1.0, 0.0));
   meshes.back()->transform(trans);

   meshes.push_back(new GLMesh(*square));
   trans = glm::mat4();
   trans = glm::translate(trans, glm::vec3(-0.5, 0.0, 0.0));
   trans = glm::rotate(trans, -90.0f, glm::vec3(0.0, 1.0, 0.0));
   meshes.back()->transform(trans);

   g_entities[name] = new Entity(meshes, glm::vec3(0.0), Rotation(), glm::vec3(1.0), name);
   g_entities[name]->set_texture(texture);
   assert(stl_util::ContainsKey(g_entities, name));
   g_scene->Add(g_entities[name]);
   return g_entities[name];
}*/
