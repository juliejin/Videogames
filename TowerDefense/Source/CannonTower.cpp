//
//  CannonTower.cpp
//  Game-mac
//
//  Created by apple on 2/16/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "CannonTower.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Cannonball.h"

IMPL_ACTOR(CannonTower,Tower);

CannonTower::CannonTower(Game& game) : Tower(game){
    MeshComponentPtr mMeshComponentPtr = MeshComponent::Create(*this);
    auto mesh = GetGame().GetAssetCache().Load<Mesh>("Meshes/Cannon.itpmesh2");
    mMeshComponentPtr->SetMesh(mesh);
    
    TimerHandle handle;
    mGame.getTimerManager().SetTimer(handle, this, &CannonTower::CannonBallAttack, 1.0f, true);

}

CannonTower::~CannonTower(){
    
}

void CannonTower::CannonBallAttack(){
    Enemy * enemy = mGame.GetWorld().GetClosestEnemy(GetWorldTransform().GetTranslation(),150.0f);
    if (enemy == nullptr)
        return;
    SetRotation(0);
    Vector3 enemyDirection = enemy->GetPosition() - GetWorldTransform().GetTranslation();
    enemyDirection.Normalize();
    float angle = Math::Acos(Dot(enemyDirection, Vector3::UnitX));
    float crossZ = Cross(Vector3::UnitX, enemyDirection).z;
    if (crossZ < 0.0f){
        angle *= -1.0f;
    }
    SetRotation(angle);
    auto ball = Cannonball::Spawn(mGame);
    ball->SetPosition(GetWorldTransform().GetTranslation());
    ball->SetRotation(angle);
}