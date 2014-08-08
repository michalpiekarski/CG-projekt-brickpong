#include "Collision.h"
#include "Body.h"

Collision::Collision() {
    _penetration = 0.0f;
    _normal = glm::vec2();
    _tangent = glm::vec2();
}
Collision::Collision(Body* A, Body* B) : Collision() {
    _A = A;
    _B = B;
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
glm::vec2 Collision::getTangent() {
    return _tangent;
}
void Collision::setTangent(glm::vec2 tangent) {
    _tangent = tangent;
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

    float A_inverseMass = _A->getInverseMass();
    float B_inverseMass = _B->getInverseMass();
    float j = -(1 + e) * velocityAlongNormal;
    float inverseMassSum = A_inverseMass + B_inverseMass;
    if (inverseMassSum != 0.0f) {
        j /= inverseMassSum;
    }

    glm::vec2 impulse = j*_normal;

    float A_mass = _A->getMass();
    float B_mass = _B->getMass();
    float mass_sum = A_mass + B_mass;

    float ratio;
    if (mass_sum != 0.0f) {
        ratio = A_mass / mass_sum;
    }
    else {
        ratio = 0.0f;
    }
    _A->setVelocity(A_velocity - (ratio * impulse));
    if (mass_sum != 0.0f) {
        ratio = B_mass / mass_sum;
    }
    _B->setVelocity(B_velocity + (ratio * impulse));

    A_velocity = _A->getVelocity();
    B_velocity = _B->getVelocity();
    relativeVelocity = B_velocity - A_velocity;

    _tangent = relativeVelocity - glm::dot(relativeVelocity, _normal) * _normal;
    _tangent = glm::normalize(_tangent);

    float jt = -glm::dot(relativeVelocity, _tangent);
    if (inverseMassSum != 0.0f) {
        jt /= inverseMassSum;
    }

    float A_staticFriction = _A->getPhysicsMaterial().getStaticFriction();
    float B_staticFriction = _B->getPhysicsMaterial().getStaticFriction();
    float mu = glm::sqrt(glm::pow(A_staticFriction, 2.0f) + glm::pow(B_staticFriction, 2.0f));
    glm::vec2 frictionImpulse;

    if (glm::abs(jt) < j * mu) {
        frictionImpulse = jt * _tangent;
    }
    else {
        float A_dynamicFriction = _A->getPhysicsMaterial().getDynamicFriction();
        float B_dynamicFriction = _B->getPhysicsMaterial().getDynamicFriction();
        float dynamicFriction = glm::sqrt(glm::pow(A_dynamicFriction, 2.0f) + glm::pow(B_dynamicFriction, 2.0f));
        frictionImpulse = -j * _tangent * dynamicFriction;
    }

    _A->setVelocity(A_velocity-(A_inverseMass*frictionImpulse));
    _B->setVelocity(B_velocity-(B_inverseMass*frictionImpulse));
}