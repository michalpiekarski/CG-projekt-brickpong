#include "AABB.h"
#include "Circle.h"

AABB::AABB() {
    _width = 0.0f;
    _height = 0.0f;
    _position = glm::vec2();
    _min = glm::vec2();
    _max = glm::vec2();
}

AABB::AABB(glm::vec2 min, glm::vec2 max) {
    _width = max.x - min.x;
    _height = max.y - min.y;
    _min = min;
    _max = max;
    _position = glm::vec2(_min.x+_width/2, _min.y+_height/2);
}

AABB::AABB(glm::vec2 position, float size) {
    _width = size;
    _height = size;
    _position = position;
    glm::vec2 offset(size / 2, size / 2);
    _min = _position - offset;
    _max = _position + offset;
}

AABB::AABB(glm::vec2 position, float width, float height) {
    _width = width;
    _height = height;
    _position = position;
    glm::vec2 offset(_width / 2, _height / 2);
    _min = _position - offset;
    _max = _position + offset;
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

glm::vec2 AABB::getPosition() {
    return _position;
}

void AABB::setPosition(glm::vec2 position) {
    _position = position;
    glm::vec2 offset(_width / 2, _height / 2);
    _min = _position - offset;
    _max = _position + offset;
}

glm::vec2 AABB::getMin() {
    return _min;
}

void AABB::setMin(glm::vec2 min) {
    _min = min;
    _width = _max.x - _min.x;
    _height = _max.y - _min.y;
    _position = glm::vec2(_min.x+_width/2, _min.y+_height/2);
}

glm::vec2 AABB::getMax() {
    return _max;
}

void AABB::setMax(glm::vec2 max) {
    _min = max;
    _width = _max.x - _min.x;
    _height = _max.y - _min.y;
    _position = glm::vec2(_min.x + _width / 2, _min.y + _height / 2);
}

bool AABB::checkCollision(AABB* other) {
    glm::vec2 otherMin = other->getMin();
    glm::vec2 otherMax = other->getMax();

    if (_max.x < otherMin.x || _min.x > otherMax.x) {
        return false;
    }
    if (_max.y < otherMin.y || _min.y > otherMax.y) {
        return false;
    }

    return true;
}

bool AABB::checkCollisionCrosstype(Circle* other) {
    AABB* otherAABB = new AABB(other->getPosition(), other->getRadius());
    return checkCollision(otherAABB);
}