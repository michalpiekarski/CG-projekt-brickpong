#ifndef __Brickpong__Body__
#define __Brickpong__Body__

#include <glm/glm.hpp>

#include "PhysicsMaterial.h"

class Body {
protected:
    glm::vec2 _position;
    glm::vec2 _velocity;
    PhysicsMaterial _physicsMaterial;
    float _mass;

public:
    Body();
    Body(glm::vec2 position, glm::vec2 velocity, float mass, PhysicsMaterial& physicsMaterial);
    virtual ~Body();
    virtual void setPosition(glm::vec2 position);
    virtual glm::vec2 getPosition();
    void setVelocity(glm::vec2 velocity);
    glm::vec2 getVelocity();
    PhysicsMaterial getPhysicsMaterial();
    void setPhysicsMaterial(PhysicsMaterial physicsMaterial);
    void setMass(float mass);
    float getMass();
    float getInverseMass();
};

#endif /* defined(__Brickpong__Body__) */