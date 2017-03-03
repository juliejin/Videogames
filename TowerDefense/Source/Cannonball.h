//
//  Cannonball.h
//  Game-mac
//
//  Created by apple on 2/19/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "SphereCollision.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
class Cannonball : public Actor{
    DECL_ACTOR(Cannonball, Actor);
public:
    Cannonball(Game & game);
    MoveComponentPtr GetMoveComponent(){ return mMoveComponentPtr; }
    MeshComponentPtr GetMeshComponent(){ return mMeshComponentPtr; }
    void Despawn();
private:
    MoveComponentPtr mMoveComponentPtr;
    SphereCollisionPtr mCollisionPtr;
    MeshComponentPtr mMeshComponentPtr;
};
