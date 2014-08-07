#ifndef __Brickpong__Body__
#define __Brick__Body__

#include <glm/glm.hpp>

#include "PhysicsMaterial.h"

class Body {
protected:
    glm::vec2 _position;
    glm::vec2 _velocity;
    float _mass;
    PhysicsMaterial _physicsMaterial;

public:
    Body();
    Body(glm::vec2 position, glm::vec2 velocity, float mass, PhysicsMaterial physicsMaterial);
    virtual ~Body();
    virtual void setPosition(glm::vec2 position);
    virtual glm::vec2 getPosition();
    void setVelocity(glm::vec2 velocity);
    glm::vec2 getVelocity();
    void setMass(float mass);
    float getMass();
    float getInverseMass();
    PhysicsMaterial getPhysicsMaterial();
    void setPhysicsMaterial(PhysicsMaterial physicsMaterial);
};

#endif /* defined(__Brickpong__Boby__) */