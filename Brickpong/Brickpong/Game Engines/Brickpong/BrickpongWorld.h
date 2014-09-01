#ifndef __Brickpong__Game_Engines__Brickpong__BrickpongWorld__
#define __Brickpong__Game_Engines__Brickpong__BrickpongWorld__

#include <Box2D/Box2D.h>

class BrickpongWorld {
private:
    b2World* _world;
    float _timeStep;
    int _velocityIterations;
    int _positionIterations;
public:
    BrickpongWorld(b2Vec2 agravity);
    virtual ~BrickpongWorld();
    b2Body* CreateBody(b2BodyDef* abodyDef);
    b2World* GetWorld();
    void SetContactListener(b2ContactListener* contactListener);
    void SetTimeStep(float atimeStep);
    void SetVelocityIterations(int avelocityIterations);
    void SetPositionIterations(int apositionIterations);
    void SetStepParameters(float atimeStep, int avelocityIterations, int apositionIterations);
    void Step();
};

#endif /* defined (__Brickpong__Game_Engines__Brickpong__BrickpongWorld__) */
