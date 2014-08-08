#include "PhysicsSolver.h"
#include "Body.h"

PhysicsSolver::PhysicsSolver() {
    _dt = 1.0f / 60.0f;
    _frameStartTime = 0.0f;
    _gravity = glm::vec2(1.0f,0.0f);
    _bodyCount = 0;
}
PhysicsSolver::PhysicsSolver(glm::vec2 gravity, float dt) {
    _dt = dt;
    _frameStartTime = 0.0f;
    _gravity = gravity;
}
PhysicsSolver::PhysicsSolver(glm::vec2 gravity, float dt, int bodyCount, std::list<Body*> bodyList) {
    _dt = dt;
    _frameStartTime = 0.0f;
    _gravity = gravity;
    _bodyCount = bodyCount;
    _bodyList = bodyList;
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
float PhysicsSolver::getFrameStartTime() {
    return _frameStartTime;
}
void PhysicsSolver::setFrameStartTime(float frameStartTime) {
    _frameStartTime = frameStartTime;
}
int PhysicsSolver::getBodyCount() {
    return _bodyCount;
}
void PhysicsSolver::setBodyList(int bodyCount, std::list<Body*> bodyList) {
    _bodyCount = bodyCount;
    _bodyList = bodyList;
}
void PhysicsSolver::step() {
    //collide
    //resolve
    //apply gravity and move
}
