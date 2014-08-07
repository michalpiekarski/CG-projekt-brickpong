#include "Body.h"

Body::Body() {
    _position = glm::vec2();
    _velocity = glm::vec2();
    _mass = 1.0f;
    _physicsMaterial = PhysicsMaterial();
}

Body::Body(glm::vec2 position, glm::vec2 velocity, float mass, PhysicsMaterial physicsMaterial) {
    _position = position;
    _velocity = velocity;
    _mass = mass;
    _physicsMaterial = physicsMaterial;
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
 PhysicsMaterial Body::getPhysicsMaterial() {
     return _physicsMaterial;
 }

 void Body::setPhysicsMaterial(PhysicsMaterial physicsMaterial) {
     _physicsMaterial = physicsMaterial;
 }