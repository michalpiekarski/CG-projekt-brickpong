#ifndef __Brickpong__PhysicsMaterial__
#define __Brickpong__PhysicsMaterial__

class PhysicsMaterial {
private:
    float _bounciness;
    float _friction;
public:
    PhysicsMaterial();
    PhysicsMaterial(float bounciness, float friction);
    virtual ~PhysicsMaterial();
    void setBounciness(float bounciness);
    float getBounciness();
    void setFriction(float friction);
    float getFriction();
};

#endif /* defined(__Brickpong__PhysicsMaterial__) */
