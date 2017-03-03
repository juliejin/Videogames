//
//  FrostTower.cpp
//  Game-mac
//
//  Created by apple on 2/16/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "FrostTower.h"
#include "Game.h"
#include "MeshComponent.h"

IMPL_ACTOR(FrostTower,Tower);

FrostTower::FrostTower(Game& game) : Tower(game){
     auto tower = Actor::SpawnAttached(*this);
    
    MeshComponentPtr mMeshComponentPtr = MeshComponent::Create(*tower);
    auto mesh = GetGame().GetAssetCache().Load<Mesh>("Meshes/Frost.itpmesh2");
    mMeshComponentPtr->SetMesh(mesh);
    
    TimerHandle handle;
    mGame.getTimerManager().SetTimer(handle, this, &FrostTower::SlowerEnemies, 2.0f, true);
    
}

FrostTower::~FrostTower(){
    
}

void FrostTower::SlowerEnemies(){
    std::vector<Enemy*> enemies = mGame.GetWorld().GetEnemiesInRange(GetWorldTransform().GetTranslation(), 150.0f);
    for (Enemy* enemy : enemies){
        enemy->Slow();
    }
}