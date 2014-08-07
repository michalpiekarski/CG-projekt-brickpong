#include "AABB.h"
#include "Circle.h"

AABB::AABB() {
    _min = glm::vec2();
    _max = glm::vec2();
}

AABB::AABB(glm::vec2 min, glm::vec2 max) {
    _width = max.x - min.x;
    _height = max.y - min.y;
    _min = min;
    _max = max;
}

AABB::AABB(glm::vec2 position, float size) {
    _width = size;
    _height = size;
    glm::vec2 offset(size / 2, size / 2);
    _min = position - offset;
    _max = position + offset;
}

AABB::AABB(glm::vec2 position, float width, float height) {
    _width = width;
    _height = height;
    glm::vec2 offset(width / 2, height / 2);
    _min = position - offset;
    _max = position + offset;
}

AABB::~AABB() {
}

float AABB::getWidth() {
    return _width;
}

void AABB::setWidth(float width) {
    _width = width;
}

float AABB::getHeight() {
    return _height;
}

void AABB::setHeight(float height) {
    _height = height;
}

glm::vec2 AABB::getMin() {
    return _min;
}

void AABB::setMin(glm::vec2 min) {
    _min = min;
}

glm::vec2 AABB::getMax() {
    return _max;
}

void AABB::setMax(glm::vec2 max) {
    _min = max;
}

bool AABB::checkCollision(AABB& other) {
    glm::vec2 otherMin = other.getMin();
    glm::vec2 otherMax = other.getMax();

    if (_max.x < otherMin.x || _min.x > otherMax.x) {
        return false;
    }
    if (_max.y < otherMin.y || _min.y > otherMax.y) {
        return false;
    }

    return true;
}

bool AABB::checkCollisionCrosstype(Circle& other) {
    AABB otherAABB(other.getPosition(), other.getRadius());
    return checkCollision(otherAABB);
}