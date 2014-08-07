#include "BodyCircle.h"
#include "BodyAABB.h"
#include "Collision.h"

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

bool BodyCircle::checkCollision(BodyCircle& other, Collision* collision) {
    if (_collider.checkCollision(other.getCollider())) {
        collision = new Collision(this, &other);

        glm::vec2 n = other.getPosition() - _position;

        float r = _collider.getRadius() + other.getCollider().getRadius();
        float d = glm::length(n);

        if (d > r) {
            return false;
        }

        if (d != 0) {
            collision->setPenetration(r - d);
            collision->setNormal(n / d);
        }
        else {
            collision->setPenetration(getCollider().getRadius());
            collision->setNormal(glm::vec2(1.0f, 0.0f));
        }
        return true;
    }
    return false;
}

bool BodyCircle::checkCollisionCrosstype(BodyAABB& other, Collision* collision) {
    if (_collider.checkCollisionCrosstype(other.getCollider())) {
        // TODO: Genereate CircleAABB collision object
    }
}
