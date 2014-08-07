#include "BodyCircle.h"
#include "BodyAABB.h"

BodyCircle::BodyCircle() : Body() {
    _collider = Circle();
}

BodyCircle::BodyCircle(glm::vec2 position, glm::vec2 velocity, float mass, PhysicsMaterial physicsMaterial, Circle collider) : Body::Body(position, velocity, mass, physicsMaterial) {
    _collider = collider;
}

BodyCircle::~BodyCircle() {
}

void BodyCircle::setPosition(glm::vec2 position) {
    _collider.setPosition(position);
    _position = _collider.getPosition();
}

glm::vec2 BodyCircle::getPosition() {
    return _collider.getPosition();
}

Circle BodyCircle::getCollider() {
    return _collider;
}

void BodyCircle::setCollider(Circle collider) {
    _collider = collider;
}

