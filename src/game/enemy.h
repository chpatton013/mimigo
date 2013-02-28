#ifndef ENEMY_H_
#define ENEMY_H_

#include <assert.h>
#include <string.h>
#include <glm/glm.hpp>
#include "../spatial_hierarchy/collidable_entity.h"

class Planet;
class SceneNode;

class Enemy : public CollidableEntity {
   public:
    Enemy() {}
    Enemy(Planet *planet, float theta, const std::string& id);
    virtual ~Enemy();
    virtual bool Update() {return false;}
    glm::vec3 position();

   private:
    void UpdateMeshPosition();

    Planet* planet_;
    float theta_;
    float radius_;
    SceneNode *mesh_;
};

#endif
