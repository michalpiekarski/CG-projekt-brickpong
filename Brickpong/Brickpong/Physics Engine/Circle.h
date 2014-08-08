#ifndef __Brickpong__Circle__
#define __Brickpong__Circle__

#include <glm/glm.hpp>

class AABB;

class Circle {
private:
    float _radius;
    glm::vec2 _position;
public:
    Circle();
    Circle(float radius, glm::vec2 position);
    virtual ~Circle();
    float getRadius();
    void setRadius(float radius);
    glm::vec2 getPosition();
    void setPosition(glm::vec2 position);
    bool checkCollision(Circle* other);
    bool checkCollisionCrosstype(AABB* other);
};

#endif /* define(__Brickpong__Circle__) */
