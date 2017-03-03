//
//  Tower.cpp
//  Game-mac
//
//  Created by apple on 2/16/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Tower.h"
#include "Game.h"
#include "MeshComponent.h"

IMPL_ACTOR(Tower,Actor);

Tower::Tower(Game& game) : Actor(game){
    MeshComponentPtr mMeshComponentPtr = MeshComponent::Create(*this);
    auto mesh = GetGame().GetAssetCache().Load<Mesh>("Meshes/TowerBase.itpmesh2");
    mMeshComponentPtr->SetMesh(mesh);
}

Tower::~Tower(){
    
}
