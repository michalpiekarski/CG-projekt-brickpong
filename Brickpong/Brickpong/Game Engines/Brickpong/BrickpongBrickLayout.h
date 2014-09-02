#ifndef __Brickpong__Game_Engines__Brickpong__BrickpongBrickLayout__
#define __Brickpong__Game_Engines__Brickpong__BrickpongBrickLayout__

#include <Box2D/Box2D.h>

class BrickpongBrickLayout {
private:
    b2Vec2 _position;
    b2Vec2 _size;
public:
    BrickpongBrickLayout(b2Vec2 aposition, b2Vec2 asize);
    virtual ~BrickpongBrickLayout();
    b2Vec2 GetPosition();
    b2Vec2 GetSize();
};

#endif /* defined(__Brickpong__Game_Engines__Brickpong__BrickpongBrickLayout__) */
