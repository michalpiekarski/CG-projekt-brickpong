#include "PhysicsMaterial.h"

PhysicsMaterial::PhysicsMaterial() {
    _bounciness = 0.0f;
    _friction = -1.0f;
}
PhysicsMaterial::PhysicsMaterial(float bounciness, float friction) {
    _bounciness = bounciness;
    _friction = friction;
}
PhysicsMaterial::~PhysicsMaterial() {

}
void PhysicsMaterial::setBounciness(float bounciness) {
    _bounciness = bounciness;
}
float PhysicsMaterial::getBounciness() {
    return _bounciness;
}
void PhysicsMaterial::setFriction(float friction) {
    _friction = friction;
}
float PhysicsMaterial::getFriction() {
    return _friction;
}
