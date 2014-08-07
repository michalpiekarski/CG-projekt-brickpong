#ifndef __Brickpong__Collision__
#define __Brickpong__Collision__

#include <glm/glm.hpp>

class Body;

class Collision {
private:
    Body* _A;
    Body* _B;
    float _penetration;
    glm::vec2 _normal;
public:
    Collision(Body* A, Body* B);
    virtual ~Collision();
    Body* getA();
    void setA(Body* A);
    Body* getB();
    void setB(Body* B);
    float getPenetration();
    void setPenetration(float penetration);
    glm::vec2 getNormal();
    void setNormal(glm::vec2 normal);
    void resolve();
};

#endif /* defined(__Brickpong__Collision__) */
