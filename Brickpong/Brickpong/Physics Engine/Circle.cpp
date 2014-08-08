#include "Circle.h"
#include "AABB.h"

Circle::Circle() {
    _radius = 0.0f;
    _position = glm::vec2();
}

Circle::Circle(float radius, glm::vec2 position) {
    _radius = radius;
    _position = position;
}

Circle::~Circle() {
}

float Circle::getRadius() {
    return _radius;
}

void Circle::setRadius(float radius) {
    _radius = radius;
}

glm::vec2 Circle::getPosition() {
    return _position;
}

void Circle::setPosition(glm::vec2 position) {
    _position = position;
}

bool Circle::checkCollision(Circle* other) {
    float r = _radius + other->getRadius();
    float distance = glm::distance(_position, other->getPosition());
    return r < distance;
}

bool Circle::checkCollisionCrosstype(AABB* other) {
    AABB* thisAABB = new AABB(getPosition(), getRadius());
    return thisAABB->checkCollision(other);
}