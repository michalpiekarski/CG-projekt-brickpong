#include "BodyAABB.h"
#include "BodyCircle.h"

BodyAABB::BodyAABB() : Body() {
    _collider = AABB();
}

BodyAABB::BodyAABB(glm::vec2 position, glm::vec2 velocity, float mass, PhysicsMaterial physicsMaterial, AABB collider) : Body::Body(position, velocity, mass, physicsMaterial) {
    _collider = collider;
}

BodyAABB::~BodyAABB() {
}

AABB BodyAABB::getCollider() {
    return _collider;
}

void BodyAABB::setCollider(AABB collider) {
    _collider = collider;
}

