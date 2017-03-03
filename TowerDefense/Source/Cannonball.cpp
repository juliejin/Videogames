//
//  Cannonball.cpp
//  Game-mac
//
//  Created by apple on 2/19/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//
#include "CannonBall.h"
#include "Game.h"

IMPL_ACTOR(Cannonball, Actor);

Cannonball::Cannonball(Game & game) : Actor(game){
 
    mMeshComponentPtr = MeshComponent::Create(*this);
    auto& assetCache = game.GetAssetCache();
    auto mesh = assetCache.Load<Mesh>("Meshes/Cannonball.itpmesh2");
    mMeshComponentPtr->SetMesh(mesh);

    mMoveComponentPtr = MoveComponent::Create(*this, Component::PreTick);
    mMoveComponentPtr->SetLinearSpeed(300.0f);
    mMoveComponentPtr->SetLinearAxis(1.0f);
    
 
    mCollisionPtr = SphereCollision::Create(*this);
    mCollisionPtr->RadiusFromMesh(mesh);

    TimerHandle handle;
    mGame.getTimerManager().SetTimer(handle, this, &Cannonball::Despawn, 3.0f);
}

void Cannonball::Despawn(){
    SetIsAlive(false);
}
