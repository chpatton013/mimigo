#include "gl_mesh.h"
#include "GLSL_helper.h"
#include <glm/gtc/type_ptr.hpp>
#include "../util/glm_util.h"
#include "../util/stl_util.h"
#include "../core/view_frustum_cull.h"

#define MAKE_GL_BUFFER(handle, buffer) \
   glGenBuffers(1, &(handle)); \
   glBindBuffer(GL_ARRAY_BUFFER, (handle)); \
   glBufferData(GL_ARRAY_BUFFER, sizeof((buffer)), \
                (buffer), GL_STATIC_DRAW);

#define GL_BIND_ARRAY(handle, name, num) \
   glBindBuffer(GL_ARRAY_BUFFER, handle); \
   safe_glVertexAttribPointer(g_handles[name], num, GL_FLOAT, GL_FALSE, 0, 0); \
   safe_glEnableVertexAttribArray(g_handles[name]); \

float average(float a, float b) { return (a + b) / 2.0; }

//static
std::map<std::string, GLMesh*> GLMesh::meshes_;

void GLMesh::SetupDraw() {
   // bind vbo
   GL_BIND_ARRAY(vertex_buffer_object_, "aPosition", 3);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object_);
   GL_BIND_ARRAY(normal_buffer_object_, "aNormal", 3);
   GL_BIND_ARRAY(diffuse_buffer_object_, "aDiffuse", 3);
   GL_BIND_ARRAY(ambient_buffer_object_, "aAmbient", 3);
   GL_BIND_ARRAY(specular_buffer_object_, "aSpecular", 3);
   GL_BIND_ARRAY(texture_buffer_object_, "aTexture", 2);
}

void GLMesh::Draw(MatrixStack* transform) {
   SetupDraw();
   transform->push();
   transform->multiply(trans_);
   		glBindFramebuffer(GL_FRAMEBUFFER, 0);
   //if (InPlane(verts_, transform)){
      safe_glUniformMatrix4fv(
         g_handles["uModelMatrix"], glm::value_ptr(transform->top())
      );
      safe_glUniformMatrix4fv(
         g_handles["uNormalMatrix"],
         glm::value_ptr(glm::transpose(glm::inverse(transform->top())))
      );

      
      const int ibo_length = faces_.size() * 3;
      //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      //glLineWidth(1.0);
      glDrawElements(GL_TRIANGLES, ibo_length, GL_UNSIGNED_SHORT, 0);
  // }

   transform->pop();
}

void GLMesh::CalculateNormals() {
   vert_normals_ = std::vector<glm::vec3>(verts_.size(),
         glm::vec3(0, 0, 0));
   for (size_t i = 0; i < faces_.size(); ++i) {
      glm::vec4 a = verts_[faces_[i].v1].position;
      glm::vec4 b = verts_[faces_[i].v2].position;
      glm::vec4 c = verts_[faces_[i].v3].position;
      glm::vec3 ab(b.x - a.x, b.y - a.y, b.z - a.z);
      glm::vec3 ac(c.x - a.x, c.y - a.y, c.z - a.z);
      glm::vec3 normal = glm::cross(ab, ac);
      vert_normals_[faces_[i].v1] += normal;
      vert_normals_[faces_[i].v2] += normal;
      vert_normals_[faces_[i].v3] += normal;
   }
}

void GLMesh::Initialize() {
   CenterMesh();
   ScaleMesh();
   CalculateNormals();
   int ndx = 0;
   //FramebufferName; 
    glGenFramebuffers(1, &FramebufferName);

    glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT, 1024, 1024, 0,GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	
	    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FramebufferName);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
	
		glDrawBuffer(GL_NONE);
   //TODO: clean this up with macros once it is working.
   unsigned short index_buffer[faces_.size()*3];
   ndx = 0;
   for (size_t i = 0; i < faces_.size(); ++i) {
      index_buffer[ndx++] = faces_[i].v1;
      index_buffer[ndx++] = faces_[i].v2;
      index_buffer[ndx++] = faces_[i].v3;
   }
   MAKE_GL_BUFFER(index_buffer_object_, index_buffer);

   GLfloat texture_buffer[verts_.size()*2];
   ndx = 0;
   for (size_t i = 0; i < verts_.size(); ++i) {
      texture_buffer[ndx++] = verts_[i].texture.x;
      texture_buffer[ndx++] = verts_[i].texture.y;
   }
   MAKE_GL_BUFFER(texture_buffer_object_, texture_buffer);

   float vertex_buffer[verts_.size()*3];
   ndx = 0;
   for (size_t i = 0; i < verts_.size(); ++i) {
      vertex_buffer[ndx++] = verts_[i].x();
      vertex_buffer[ndx++] = verts_[i].y();
      vertex_buffer[ndx++] = verts_[i].z();
   }
   MAKE_GL_BUFFER(vertex_buffer_object_, vertex_buffer);

   float normal_buffer[verts_.size()*3];
   ndx = 0;
   for (size_t i = 0; i < verts_.size(); ++i) {
      normal_buffer[ndx++] = verts_[i].normal.x;
      normal_buffer[ndx++] = verts_[i].normal.y;
      normal_buffer[ndx++] = verts_[i].normal.z;
   }
   MAKE_GL_BUFFER(normal_buffer_object_, normal_buffer);

   float diffuse_buffer[verts_.size()*3];
   ndx = 0;
   for (size_t i = 0; i < verts_.size(); ++i) {
      diffuse_buffer[ndx++] = verts_[i].diffuse.x;
      diffuse_buffer[ndx++] = verts_[i].diffuse.y;
      diffuse_buffer[ndx++] = verts_[i].diffuse.z;
   }
   MAKE_GL_BUFFER(diffuse_buffer_object_, diffuse_buffer);

   float ambient_buffer[verts_.size()*3];
   ndx = 0;
   for (size_t i = 0; i < verts_.size(); ++i) {
      ambient_buffer[ndx++] = verts_[i].ambient.x;
      ambient_buffer[ndx++] = verts_[i].ambient.y;
      ambient_buffer[ndx++] = verts_[i].ambient.z;
   }
   MAKE_GL_BUFFER(ambient_buffer_object_, ambient_buffer);

   float specular_buffer[verts_.size()*3];
   ndx = 0;
   for (size_t i = 0; i < verts_.size(); ++i) {
      specular_buffer[ndx++] = verts_[i].specular.x;
      specular_buffer[ndx++] = verts_[i].specular.y;
      specular_buffer[ndx++] = verts_[i].specular.z;
   }
   MAKE_GL_BUFFER(specular_buffer_object_, specular_buffer);
}

void GLMesh::GetExtents(glm::vec4* min, glm::vec4* max) {
   *min = verts_.front().position;
   *max = verts_.front().position;
   for (size_t i = 1; i < verts_.size(); ++i) {
      min->x = std::min(verts_[i].x(), min->x);
      min->y = std::min(verts_[i].y(), min->y);
      min->z = std::min(verts_[i].z(), min->z);

      max->x = std::max(verts_[i].x(), max->x);
      max->y = std::max(verts_[i].y(), max->y);
      max->z = std::max(verts_[i].z(), max->z);
   }
}

void GLMesh::GetExtentAverages(glm::vec4& min, glm::vec4& max, glm::vec3* avg) {
   avg->x = (max.x - min.x) * 0.5f;
   avg->y = (max.y - min.y) * 0.5f;
   avg->z = (max.z - min.z) * 0.5f;
}
void GLMesh::GetExtentAverages(glm::vec3* avg) {
   glm::vec4 min, max;
   GetExtents(&min, &max);
   GetExtentAverages(min, max, avg);
}

float GLMesh::GetCircumscribingRadius() {
   glm::vec3 avgs;
   GetExtentAverages(&avgs);

   return std::max(std::max(avgs.x, avgs.y), avgs.z);
}

float GLMesh::GetInscribingRadius() {
   glm::vec3 avgs;
   GetExtentAverages(&avgs);

   return std::min(std::min(avgs.x, avgs.y), avgs.z);
}

float GLMesh::GetWeightedAverageRadius() {
   glm::vec4 min, max;
   glm::vec3 avgs;

   GetExtents(&min, &max);
   GetExtentAverages(min, max, &avgs);

   return glm::dot(avgs, avgs) / (avgs.x + avgs.y + avgs.z);
}

float GLMesh::GetAverageRadius() {
   float max = GetCircumscribingRadius(),
         min = GetInscribingRadius();
   return (max - min) * 0.5f + min;
}

void GLMesh::CenterMesh() {
   if (verts_.size() < 2u)
      return;

   glm::vec4 min, max;
   GetExtents(&min, &max);
   glm::vec3 offset(average(min.x, max.x),
                    average(min.y, max.y),
                    average(min.z, max.z));

   for (size_t i = 0; i < verts_.size(); ++i) {
      verts_[i].position.x -= offset.x;
      verts_[i].position.y -= offset.y;
      verts_[i].position.z -= offset.z;
   }
}

void GLMesh::ScaleMesh() {
   if (verts_.size() < 2u)
      return;

   glm::vec4 min, max;
   GetExtents(&min, &max);
   float scale = std::max(max.x - min.x, std::max(max.y - min.y,
                                                  max.z - min.z));
   for (size_t i = 0; i < verts_.size(); ++i) {
      verts_[i].position.x /= scale;
      verts_[i].position.y /= scale;
      verts_[i].position.z /= scale;
   }
}
