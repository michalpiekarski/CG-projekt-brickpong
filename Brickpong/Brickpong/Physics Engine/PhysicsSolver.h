#ifndef __Brickpong__PhysicsSolver__
#define __Brickpong__PhysicsSolver__

#include <glm/glm.hpp>

class Body;

class PhysicsSolver {
private:
    float _dt; // Delta time
    float _frameStartTime;
    glm::vec2 _gravity;
    int _bodyCount;
    std::list<Body*> _bodyList;
public:
    PhysicsSolver();
    PhysicsSolver(glm::vec2 gravity, float dt);
    PhysicsSolver(glm::vec2 gravity, float dt, int bodyCount, std::list<Body*> bodyList);
    virtual ~PhysicsSolver();
    float getDeltaTime();
    void setDeltaTime(float dt);
    glm::vec2 getGravity();
    void setGravity(glm::vec2 gravity);
    float getFrameStartTime();
    void setFrameStartTime(float frameStartTime);
    int getBodyCount();
    void setBodyList(int bodyCount, std::list<Body*> bodyList);
    void step();
};

#endif /* defined(__Brickpong__PhysicsSolver__) */
