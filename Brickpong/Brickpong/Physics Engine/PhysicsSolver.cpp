#include "PhysicsSolver.h"
#include "Body.h"
#include "Collision.h"

PhysicsSolver::PhysicsSolver() {
    _dt = 1.0f / 60.0f;
    _frameStartTime = 0.0f;
    _accumulator = 0.0f;
    _gravity = glm::vec2(1.0f,0.0f);
    _bodyCount = 0;
}
PhysicsSolver::PhysicsSolver(glm::vec2 gravity, float dt) {
    _dt = dt;
    _frameStartTime = 0.0f;
    _accumulator = 0.0f;
    _gravity = gravity;
    _bodyCount = 0;
}
PhysicsSolver::PhysicsSolver(glm::vec2 gravity, float dt, int bodyCount, std::list<Body*> bodyList) {
    _dt = dt;
    _frameStartTime = 0.0f;
    _accumulator = 0.0f;
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
bool PhysicsSolver::colideBodies(Body* A, int A_colliderType, Body* B, int B_colliderType, Collision* collision) {
    if (A_colliderType + B_colliderType == 2 || A_colliderType + B_colliderType == 4) {
        return A->checkCollision(B, collision);
    }
    else {
        return A->checkCollisionCrosstype(B, collision);
    }
}
void PhysicsSolver::step() {
    if (_bodyCount > 1) {
        for (std::list<Body*>::iterator A = _bodyList.begin(); A != _bodyList.end(); ++A) {
            if ((*A)->getIsStatic()) {
                continue;
            }
            else {
                int A_colliderType = (*A)->getColliderType();

                for (std::list<Body*>::iterator B = _bodyList.begin(); B != _bodyList.end(); ++B) {
                    if ((*A) == (*B)) {
                        continue;
                    }
                    else {
                        int B_colliderType = (*B)->getColliderType();
                        Collision* c = new Collision();
                        if (colideBodies((*A), A_colliderType, (*B), B_colliderType, c)) {
                            c->resolve(_gravity);
                        }
                    }
                }
                (*A)->move();
            }
        }
    }
}

void PhysicsSolver::run() {
    // TODO: implement main physics loop
}
