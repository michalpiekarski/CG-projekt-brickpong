#include "BrickpongBrickLayout.h"

BrickpongBrickLayout::BrickpongBrickLayout(b2Vec2 aposition, b2Vec2 asize){
    _position = aposition;
    _size = asize;
}
BrickpongBrickLayout::~BrickpongBrickLayout(){

}

b2Vec2 BrickpongBrickLayout::GetPosition(){
    return _position;
}

b2Vec2 BrickpongBrickLayout::GetSize(){
    return _size;
}