#ifndef GL_MESH_H
#define GL_MESH_H

#include <stdlib.h>
#include <vector>
#include <map>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../core/vertex.h"
#include "../global/handles.h"
#include "../util/matrix_stack.h"

/**
 * A GLMesh contains a single mesh, a texture, a material and optionally has a
 * bump map.
 */
class GLMesh {
  public:
   struct Face {
     // Indices into |vertices_|.
     Face(size_t v1=0, size_t v2=0, size_t v3=0) :
        v1(v1),
        v2(v2),
        v3(v3)
     {}

     size_t v1;
     size_t v2;
     size_t v3;
   };

   typedef std::vector<Face> FaceList;
   typedef std::vector<Vertex> VertexList;

   GLMesh() {}
   GLMesh(const GLMesh& other) :
      vertex_buffer_object_(other.vertex_buffer_object_),
      index_buffer_object_(other.index_buffer_object_),
      normal_buffer_object_(other.normal_buffer_object_),
      texture_buffer_object_(other.texture_buffer_object_),
      diffuse_buffer_object_(other.diffuse_buffer_object_),
      ambient_buffer_object_(other.ambient_buffer_object_),
      specular_buffer_object_(other.specular_buffer_object_),
      verts_(other.verts_),
      faces_(other.faces_),
      vert_normals_(other.vert_normals_),
      vert_textures_(other.vert_textures_)
   {}
   GLMesh(const VertexList& verts, const FaceList& faces,
          const std::vector<glm::vec3>& normals,
          const std::vector<glm::vec2>& textures) :
      verts_(verts),
      faces_(faces),
      vert_normals_(normals), // TODO: right now this is a duplication.
                              // Instead, verts should hold an index
                              // into this array.
      vert_textures_(textures)
   {Initialize();}

   void SetupDraw();
   void Draw(MatrixStack* transform);
   void transform(const glm::mat4& trans) { trans_ = trans; }
   void move(const glm::vec3& move) { trans_ = glm::translate(trans_, move); }

   void GetExtents(glm::vec4* min, glm::vec4* max);
   void GetExtentAverages(glm::vec4& min, glm::vec4& max, glm::vec3* avg);
   void GetExtentAverages(glm::vec3* avg);
   float GetCircumscribingRadius();
   float GetInscribingRadius();
   float GetWeightedAverageRadius();
   float GetAverageRadius();

   static std::map<std::string, GLMesh*> meshes_;

  private:
   void Initialize();
   void CenterMesh();
   void ScaleMesh();
   void CalculateNormals();

   GLuint vertex_buffer_object_;
   GLuint index_buffer_object_;
   GLuint normal_buffer_object_;
   GLuint texture_buffer_object_;

   GLuint diffuse_buffer_object_;
   GLuint ambient_buffer_object_;
   GLuint specular_buffer_object_;
   
   GLuint FramebufferName; 
   GLuint depthTexture;
   
   VertexList verts_;
   FaceList faces_;
   std::vector<glm::vec3> vert_normals_;
   std::vector<glm::vec2> vert_textures_;
   std::vector<std::string> materials_;
   glm::mat4 trans_;
};

#endif
