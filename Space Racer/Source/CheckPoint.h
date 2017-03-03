#pragma once
#include "Actor.h"
#include "SphereCollision.h"

class CheckPoint : public Actor{
    DECL_ACTOR(CheckPoint, Actor);
public:
    CheckPoint(Game& game);
private:
    SphereCollisionPtr mSphereCollision;
};
DECL_PTR(CheckPoint);