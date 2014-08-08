#include "PhysicsSolver.h"

PhysicsSolver::PhysicsSolver() {
    _dt = 1.0f / 60.0f;
    _gravity = glm::vec2(1.0f,0.0f);
}
PhysicsSolver::PhysicsSolver(glm::vec2 gravity, float dt) {
    _dt = dt;
    _gravity = gravity;

}
PhysicsSolver::~PhysicsSolver() {

}
float PhysicsSolver::getDeltaTime() {
    return _dt;
}
void PhysicsSolver::setDeltaTime(float dt) {
    _dt = dt;
}
glm::vec2 PhysicsSolver::getGravity() {
    return _gravity;
}
void PhysicsSolver::setGravity(glm::vec2 gravity) {
    _gravity = gravity;
}
void PhysicsSolver::step() {
    //collide
    //resolve
    //apply gravity and move
}
