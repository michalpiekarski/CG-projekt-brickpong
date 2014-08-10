#ifndef __Brickpong__AABB__
#define __Brickpong__AABB__

#include <glm/glm.hpp>

class Circle;

// Axis Aligned Bounding Box
class AABB {
private:
    float _width;
    float _height;
    glm::vec2 _position;
    glm::vec2 _min;
    glm::vec2 _max;
public:
    AABB();
    AABB(glm::vec2 min, glm::vec2 max);
    AABB(glm::vec2 position, float size);
    AABB(glm::vec2 position, float width, float height);
    ~AABB();
    float getWidth();
    void setWidth(float width);
    float getHeight();
    void setHeight(float height);
    glm::vec2 getPosition();
    void setPosition(glm::vec2 position);
    glm::vec2 getMin();
    void setMin(glm::vec2 min);
    glm::vec2 getMax();
    void setMax(glm::vec2 max);
    bool checkCollision(AABB* other);
    bool checkCollisionCrosstype(Circle* other);
};

#endif /* defined(__Brickpong__AABB__) */
