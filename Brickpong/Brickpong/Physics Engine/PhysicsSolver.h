#ifndef __Brickpong__PhysicsSolver__
#define __Brickpong__PhysicsSolver__

#include <list>

#include <glm/glm.hpp>

class Body;
class Collision;

class PhysicsSolver {
private:
    float _dt; // Delta time
    float _frameStartTime;
    float _accumulator;
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
    bool colideBodies(Body* A, int A_colliderType, Body* B, int B_colliderType, Collision* collision);
    void step();
    void run();
};

#endif /* defined(__Brickpong__PhysicsSolver__) */
