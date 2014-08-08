#include "PhysicsMaterial.h"

PhysicsMaterial::PhysicsMaterial() {
    _bounciness = 0.0f;
    _staticFriction = 0.0f;
    _dynamicFriction = 0.0f;
}
PhysicsMaterial::PhysicsMaterial(float bounciness, float staticFriction, float dynamicFriction) {
    _bounciness = bounciness;
    _staticFriction = staticFriction;
    _dynamicFriction = dynamicFriction;
}
PhysicsMaterial::~PhysicsMaterial() {

}
void PhysicsMaterial::setBounciness(float bounciness) {
    _bounciness = bounciness;
}
float PhysicsMaterial::getBounciness() {
    return _bounciness;
}
void PhysicsMaterial::setStaticFriction(float staticFriction) {
    _staticFriction = staticFriction;
}
float PhysicsMaterial::getStaticFriction() {
    return _staticFriction;
}
void PhysicsMaterial::setDynamicFriction(float dynamicFriction) {
    _dynamicFriction = dynamicFriction;
}
float PhysicsMaterial::getDynamicFriction() {
    return _dynamicFriction;
}
