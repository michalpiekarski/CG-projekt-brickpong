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
    bool _isStatic;
    float _gravityScale;

public:
    Body();
    Body(glm::vec2 position, glm::vec2 velocity, PhysicsMaterial& physicsMaterial, float mass, bool isStatic, float gravityScale);
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
    bool getIsStatic();
    void setIsStatic(bool isStatic);
    float getGravityScale();
    void setGravityScale(float gravityScale);
    void move(glm::vec2 gravity);
};

#endif /* defined(__Brickpong__Body__) */