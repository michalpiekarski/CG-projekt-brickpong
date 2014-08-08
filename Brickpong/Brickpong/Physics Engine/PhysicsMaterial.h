#ifndef __Brickpong__PhysicsMaterial__
#define __Brickpong__PhysicsMaterial__

class PhysicsMaterial {
private:
    float _bounciness;
    float _staticFriction;
    float _dynamicFriction;
public:
    PhysicsMaterial();
    PhysicsMaterial(float bounciness, float staticFriction, float dynamicFriction);
    virtual ~PhysicsMaterial();
    void setBounciness(float bounciness);
    float getBounciness();
    void setStaticFriction(float staticFriction);
    float getStaticFriction();
    void setDynamicFriction(float dynamicFriction);
    float getDynamicFriction();
};

#endif /* defined(__Brickpong__PhysicsMaterial__) */
