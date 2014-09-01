#ifndef __Brickpong__Game_Engines__Brickpong__BrickpongPad__
#define __Brickpong__Game_Engines__Brickpong__BrickpongPad__

#include <Box2D/Box2D.h>

class BrickpongPad {
private:
    float _width;
    float _height;
    b2Body* _body;
public:
    BrickpongPad(b2World* aworld, float awidth, float aheight, float acursorPositionX);
    virtual ~BrickpongPad();
    b2Vec2 GetPosition();
    float GetAngle();
    void SetTransform(b2Vec2 aposition, float aangle);
};

#endif /* defined(__Brickpong__Game_Engines__Brickpong__BrickpongPad__) */
