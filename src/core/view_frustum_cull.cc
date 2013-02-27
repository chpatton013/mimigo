#include "view_frustum_cull.h"

void ExtractPlanesGL(const glm::mat4& comboMatrix, bool normalize) {
   //left clipping space
   p_planes[0][0] = comboMatrix[0][3] + comboMatrix[0][0];
   p_planes[0][1] = comboMatrix[1][3] + comboMatrix[1][0];
   p_planes[0][2] = comboMatrix[2][3] + comboMatrix[2][0];
   p_planes[0][3] = comboMatrix[3][3] + comboMatrix[3][0];

   //right clip space
   p_planes[1][0] = comboMatrix[0][3] - comboMatrix[0][0];
   p_planes[1][1] = comboMatrix[1][3] - comboMatrix[1][0];
   p_planes[1][2] = comboMatrix[2][3] - comboMatrix[2][0];
   p_planes[1][3] = comboMatrix[3][3] - comboMatrix[3][0];

   //top clip space
   p_planes[2][0] = comboMatrix[0][3] - comboMatrix[0][1];
   p_planes[2][1] = comboMatrix[1][3] - comboMatrix[1][1];
   p_planes[2][2] = comboMatrix[2][3] - comboMatrix[2][1];
   p_planes[2][3] = comboMatrix[3][3] - comboMatrix[3][1];

   //bottom clip space
   p_planes[3][0] = comboMatrix[0][3] + comboMatrix[0][1];
   p_planes[3][1] = comboMatrix[1][3] + comboMatrix[1][1];
   p_planes[3][2] = comboMatrix[2][3] + comboMatrix[2][1];
   p_planes[3][3] = comboMatrix[3][3] + comboMatrix[3][1];

   //near clip space
   p_planes[4][0] = comboMatrix[0][3] + comboMatrix[0][2];
   p_planes[4][1] = comboMatrix[1][3] + comboMatrix[1][2];
   p_planes[4][2] = comboMatrix[2][3] + comboMatrix[2][2];
   p_planes[4][3] = comboMatrix[3][3] + comboMatrix[3][2];

   //far clip space
   p_planes[5][0] = comboMatrix[0][3] - comboMatrix[0][2];
   p_planes[5][1] = comboMatrix[1][3] - comboMatrix[1][2];
   p_planes[5][2] = comboMatrix[2][3] - comboMatrix[2][2];
   p_planes[5][3] = comboMatrix[3][3] - comboMatrix[3][2];

   if (normalize == true) {
      for (int i = 0; i < 6; i++) {
         p_planes[i] = glm::normalize(p_planes[i]);
      }
   }
}

bool InPlane(const std::vector<Vertex>& vertices, MatrixStack *matrixStack){
		for(size_t i = 0; i < vertices.size(); ++i){
      glm::vec4 vertify = matrixStack->top() * vertices[i].position;


			if(0 <= (p_planes[0][0] * vertify[0] + p_planes[0][1] * vertify[1] + 
				p_planes[0][2] * vertify[2] + p_planes[0][3])){
				if(0 <= (p_planes[1][0] * vertify[0] + p_planes[1][1] * vertify[1] + 
					p_planes[1][2] * vertify[2] + p_planes[1][3])){
					if(0 <= (p_planes[2][0] * vertify[0] + p_planes[2][1] * vertify[1] + 
					p_planes[2][2] * vertify[2] + p_planes[2][3])){
						if(0 <= (p_planes[3][0] * vertify[0] + p_planes[3][1] * vertify[1] + 
						p_planes[3][2] * vertify[2] + p_planes[3][3])){
							if(0 <= (p_planes[4][0] * vertify[0] + p_planes[4][1] * vertify[1] + 
								p_planes[4][2] * vertify[2] + p_planes[4][3])){
								if(0 <= (p_planes[5][0] * vertify[0] + p_planes[5][1] * vertify[1] + 
									p_planes[5][2] * vertify[2] + p_planes[5][3])){
										return true;
								}
							}
						}
					}
				}
			}
		}
	return false;
}

