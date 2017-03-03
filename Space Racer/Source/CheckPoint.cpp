//
//  CheckPoint.cpp
//  Game-mac
//
//  Created by apple on 3/3/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Checkpoint.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"

IMPL_ACTOR(CheckPoint, Actor);

CheckPoint::CheckPoint(Game& game) : Actor(game)
{
    auto mesh = mGame.GetAssetCache().Load<Mesh>("Meshes/Checkpoint.itpmesh2");
    auto meshcomp = MeshComponent::Create(*this);
    meshcomp->SetMesh(mesh);
    
    mSphereCollision = SphereCollision::Create(*this);
    mSphereCollision->RadiusFromMesh(mesh);
    mSphereCollision->SetScale(0.75f);
}

