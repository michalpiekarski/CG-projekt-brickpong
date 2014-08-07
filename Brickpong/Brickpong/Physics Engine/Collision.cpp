#include "Collision.h"
#include "Body.h"

Collision::Collision(Body* A, Body* B) {
    _A = A;
    _B = B;
    _penetration = 0.0f;
    _normal = glm::vec2();
}

Collision::~Collision() {
}

Body* Collision::getA() {
    return _A;
}
void Collision::setA(Body* A) {
    _A = A;
}
Body* Collision::getB() {
    return _B;
}
void Collision::setB(Body* B) {
    _B = B;
}
float Collision::getPenetration() {
    return _penetration;
}
void Collision::setPenetration(float penetration) {
    _penetration = penetration;
}
glm::vec2 Collision::getNormal() {
    return _normal;
}
void Collision::setNormal(glm::vec2 normal) {
    _normal = normal;
}
void Collision::resolve() {
    glm::vec2 A_velocity = _A->getVelocity();
    glm::vec2 B_velocity = _B->getVelocity();
    glm::vec2 relativeVelocity = B_velocity - A_velocity;

    float velocityAlongNormal = glm::dot(relativeVelocity, _normal);

    if (velocityAlongNormal > 0.0f) {
        return;
    }

    float e = glm::min(_B->getPhysicsMaterial().getBounciness(), _A->getPhysicsMaterial().getBounciness());

    float j = -(1 + e) * velocityAlongNormal;
    j /= _A->getInverseMass() + _B->getInverseMass();

    glm::vec2 impulse = j*_normal;

    float A_mass = _A->getMass();
    float B_mass = _B->getMass();
    float mass_sum = A_mass + B_mass;

    float ratio = A_mass / mass_sum;
    _A->setVelocity(A_velocity - (ratio * impulse));
    ratio = B_mass / mass_sum;
    _B->setVelocity(B_velocity + (ratio * impulse));
}