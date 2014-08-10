#ifndef __Brickpong__BodyCircle__
#define __Brickpong__BodyCircle__

#include "Body.h"
#include "Circle.h"

class BodyAABB;
class Collision;

class BodyCircle : public Body {
private:
    Circle* _collider;
public:
    BodyCircle();
    BodyCircle(glm::vec2 position, glm::vec2 velocity, PhysicsMaterial* physicsMaterial, float mass, bool isStatic, float gravityScale, Circle* collider);
    virtual ~BodyCircle();
    virtual void setPosition(glm::vec2 position);
    virtual glm::vec2 getPosition();
    Circle* getCollider();
    void setCollider(Circle* collider);
    virtual bool checkCollision(Body* other, Collision* collision);
    virtual bool checkCollisionCrosstype(Body* other, Collision* collision);
    bool checkCollision(BodyCircle* other, Collision* collision);
    bool checkCollisionCrosstype(BodyAABB* other, Collision* collision);
    virtual void move();
};

#endif /* defined(__Brickpong__BodyCircle__) */
