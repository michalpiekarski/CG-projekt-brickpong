#ifndef __Brickpong__Game_Engines__Brickpong__BrickpongWorldBounds__
#define __Brickpong__Game_Engines__Brickpong__BrickpongWorldBounds__

#include <Box2D/Box2D.h>

class BrickpongWorldBounds {
private:
    b2Body* _body;
public:
    BrickpongWorldBounds(b2World* aworld, float awidth, float aheight, b2Vec2 acenterOffset);
    virtual ~BrickpongWorldBounds();
};

#endif /* defined(__Brickpong__Game_Engines__Brickpong__BrickpongWorldBounds__) */
