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

bool Circle::checkCollision(Circle& other) {
    float r = _radius + other.getRadius();
    r *= r;
    glm::vec2 otherPosition = other.getPosition();
    float distanceSquare = glm::pow((_position.x + otherPosition.x), 2.0f) + glm::pow((_position.y + otherPosition.y), 2.0f);
    return r < distanceSquare;
}

bool Circle::checkCollisionCrosstype(AABB& other) {
    AABB thisAABB(getPosition(), getRadius());
    return thisAABB.checkCollision(other);
}