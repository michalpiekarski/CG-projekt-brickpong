#include "Body.h"

Body::Body() {
    _position = glm::vec2();
    _velocity = glm::vec2();
    _physicsMaterial = PhysicsMaterial();
    _mass = 1.0f;
    _isStatic = true;
    _gravityScale = 0.0f;
}

Body::Body(glm::vec2 position, glm::vec2 velocity, PhysicsMaterial& physicsMaterial, float mass, bool isStatic = true, float gravityScale = 0.0f) {
    _position = position;
    _velocity = velocity;
    _physicsMaterial = physicsMaterial;
    _mass = mass;
    _isStatic = isStatic;
    _gravityScale = gravityScale;
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
bool Body::getIsStatic() {
    return _isStatic;
}
void Body::setIsStatic(bool isStatic) {
    _isStatic = isStatic;
    if (isStatic) {
        _gravityScale = 0.0f;
        _velocity = glm::vec2();
    }
    else {

    }
}
float Body::getGravityScale() {
    return _gravityScale;
}
void Body::setGravityScale(float gravityScale) {
    _gravityScale = gravityScale;
}
 void Body::move(glm::vec2 gravity) {
     if (_isStatic == false) {
         _velocity += gravity * _gravityScale;
         _position += _velocity;
     }
 }