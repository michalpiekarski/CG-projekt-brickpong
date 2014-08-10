#ifndef __Brickpong__BodyAABB__
#define __Brickpong__BodyAABB__

#include "Body.h"
#include "AABB.h"

class BodyCircle;
class Collision;

class BodyAABB : public Body {
private:
    AABB* _collider;
public:
    BodyAABB();
    BodyAABB(glm::vec2 position, glm::vec2 velocity, PhysicsMaterial* physicsMaterial, float mass, bool isStatic, float gravityScale, AABB* collider);
    virtual ~BodyAABB();
    virtual void setPosition(glm::vec2 position);
    virtual glm::vec2 getPosition();
    AABB* getCollider();
    void setCollider(AABB* collider);
    virtual bool checkCollision(Body* other, Collision* collision);
    virtual bool checkCollisionCrosstype(Body* other, Collision* collision);
    bool checkCollision(BodyAABB* other, Collision* collision);
    bool checkCollisionCrosstype(BodyCircle* other, Collision* collision);
    virtual void move();
};

#endif /* defined(__Brickpong__Body__AABB__) */
