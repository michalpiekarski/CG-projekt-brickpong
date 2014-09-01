#ifndef __Brickpong__Game_Engines__Brickpong__BrickpongBrick__
#define __Brickpong__Game_Engines__Brickpong__BrickpongBrick__

#include <Box2D/Box2D.h>

class BrickpongBrick {
private:
    b2Body* _body;
public:
    BrickpongBrick(b2World* aworld, b2Vec2 position, float awidth, float aheight);
    virtual ~BrickpongBrick();
    b2Vec2 GetPosition();
    bool IsActive();
    void SetActive(bool aactive);
};

#endif /* defined(__Brickpong__Game_Engines__Brickpong__BrickpongBrick__) */
