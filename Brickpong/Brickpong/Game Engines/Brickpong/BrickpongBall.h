#ifndef __Brickpong__Game_engines__Brickpong__BrickpongBall__
#define __Brickpong__Game_engines__Brickpong__BrickpongBall__

#include <Box2D/Box2D.h>

class BrickpongBall {
private:
    b2Body* _body;
    float _density;
public:
    BrickpongBall(b2World* aworld, float aradius, b2Vec2 alinearVelocity, float adensity);
    virtual ~BrickpongBall();
    b2Body* GetBody();
    b2Vec2 GetLinearVelocity();
    void SetLinearVelocity(b2Vec2 alinearVelocity);
    b2Vec2 GetPosition();
    void SetTransform(b2Vec2 aposition, float aangle);
};

#endif /* defined(__Brickpong__Game_engines__Brickpong__BrickpongBall__) */
