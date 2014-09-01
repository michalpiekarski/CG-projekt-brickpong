#include "BrickpongWorld.h"


BrickpongWorld::BrickpongWorld(b2Vec2 agravity) {
    _world = new b2World(agravity);
    SetStepParameters(1.0f/60.0f, 6, 3);
}


BrickpongWorld::~BrickpongWorld() {
    delete _world;
}

b2Body* BrickpongWorld::CreateBody(b2BodyDef* abodyDef) {
    return _world->CreateBody(abodyDef);
}

b2World* BrickpongWorld::GetWorld() {
    return _world;
}

void BrickpongWorld::SetContactListener(b2ContactListener* contactListener) {
    _world->SetContactListener(contactListener);
}

void BrickpongWorld::SetTimeStep(float atimeStep) {
    _timeStep = atimeStep;
}
void BrickpongWorld::SetVelocityIterations(int avelocityIterations) {
    _velocityIterations = avelocityIterations;
}
void BrickpongWorld::SetPositionIterations(int apositionIterations) {
    _positionIterations = apositionIterations;
}

void BrickpongWorld::SetStepParameters(float atimeStep, int avelocityIterations, int apositionIterations) {
    SetTimeStep(atimeStep);
    SetVelocityIterations(avelocityIterations);
    SetPositionIterations(apositionIterations);
}

void BrickpongWorld::Step() {
    _world->Step(_timeStep, _velocityIterations, _positionIterations);
}
