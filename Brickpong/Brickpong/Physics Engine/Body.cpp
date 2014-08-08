#include "Body.h"

Body::Body() {
    _position = glm::vec2();
    _velocity = glm::vec2();
    _physicsMaterial = PhysicsMaterial();
    _mass = 1.0f;
}

Body::Body(glm::vec2 position, glm::vec2 velocity, float mass, PhysicsMaterial& physicsMaterial) {
    _position = position;
    _velocity = velocity;
    _physicsMaterial = physicsMaterial;
    _mass = mass;
}

Body::~Body() {

}

void Body::setPosition(glm::vec2 position) {
    _position = position;
}
glm::vec2 Body::getPosition() {
    return _position;
}
void Body::setVelocity(glm::vec2 velocity) {
    _velocity = velocity;
}
glm::vec2 Body::getVelocity() {
    return _velocity;
}
PhysicsMaterial Body::getPhysicsMaterial() {
    return _physicsMaterial;
}

void Body::setPhysicsMaterial(PhysicsMaterial physicsMaterial) {
    _physicsMaterial = physicsMaterial;
}
void Body::setMass(float mass) {
    _mass = mass;
}
float Body::getMass() {
    return _mass;
}
float Body::getInverseMass() {
    if (_mass == 0.0f) {
        return 0.0f;
    }
    else {
        return 1.0f / _mass;
    }
}

 }