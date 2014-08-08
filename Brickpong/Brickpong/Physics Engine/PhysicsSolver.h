#ifndef __Brickpong__PhysicsSolver__
#define __Brickpong__PhysicsSolver__

#include <glm/glm.hpp>

class PhysicsSolver {
private:
    float _dt; // Delta time
    glm::vec2 _gravity;
public:
    PhysicsSolver();
    PhysicsSolver(glm::vec2 gravity, float dt);
    virtual ~PhysicsSolver();
    float getDeltaTime();
    void setDeltaTime(float dt);
    glm::vec2 getGravity();
    void setGravity(glm::vec2 gravity);
    void step();
};

#endif /* defined(__Brickpong__PhysicsSolver__) */
