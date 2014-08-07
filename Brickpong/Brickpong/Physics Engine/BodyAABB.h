#ifndef __Brickpong__BodyAABB__
#define __Brickpong__BodyAABB__

#include "Body.h"
#include "AABB.h"

class BodyCircle;
class Collision;

class BodyAABB : public Body {
private:
    AABB _collider;
public:
    BodyAABB();
    BodyAABB(glm::vec2 position, glm::vec2 velocity, float mass, PhysicsMaterial physicsMaterial, AABB collider);
    virtual ~BodyAABB();
    AABB getCollider();
    void setCollider(AABB collider);
    bool checkCollision(BodyAABB& other, Collision* collision);
    bool checkCollisionCrosstype(BodyCircle& other, Collision* collision);
};

#endif /* defined(__Brickpong__Body__AABB__) */
