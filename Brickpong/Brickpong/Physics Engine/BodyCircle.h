#ifndef __Brickpong__BodyCircle__
#define __Brickpong__BodyCircle__

#include "Body.h"
#include "Circle.h"

class BodyAABB;

class BodyCircle : public Body {
private:
    Circle _collider;
public:
    BodyCircle();
    BodyCircle(glm::vec2 position, glm::vec2 velocity, float mass, PhysicsMaterial physicsMaterial, Circle collider);
    virtual ~BodyCircle();
    virtual void setPosition(glm::vec2 position);
    virtual glm::vec2 getPosition();
    Circle getCollider();
    void setCollider(Circle collider);
};

#endif /* defined(__Brickpong__BodyCircle__) */
