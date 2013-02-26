#ifndef _VIEW_FRUSTUM_CULL_H_
#define _VIEW_FRUSTUM_CULL_H_

#include <vector>
#include <glm/glm.hpp>
#include "core/entity.h"
#include "gl/gl_mesh.h"
#include "../util/matrix_stack.h"
#include "../core/vertex.h"

void ExtractPlanesGL(glm::mat4 &comboMatrix, bool normalize);
bool InPlane(std::vector<Vertex> vertices, MatrixStack* transform);

#endif
