//
//  Enemy.cpp
//  Game-mac
//
//  Created by apple on 2/16/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Enemy.h"
#include "Game.h"
#include "Tile.h"
#include "Cannonball.h"

IMPL_ACTOR(Enemy, Actor);

Enemy::Enemy(Game& game) : Actor(game)
{
    mMeshComponentPtr = MeshComponent::Create(*this);
    auto mesh = GetGame().GetAssetCache().Load<Mesh>("Meshes/Peasant.itpmesh2");
    mMeshComponentPtr->SetMesh(mesh);
    
    mSphereCollisionPtr = SphereCollision::Create(*this);
    mSphereCollisionPtr->RadiusFromMesh(mesh);
    mSphereCollisionPtr->SetScale(0.5f);
    
    mMoveComponentPtr = MoveComponent::Create(*this);
    mMoveComponentPtr->SetLinearSpeed(60.0f);
    mMoveComponentPtr->SetLinearAxis(1.0f);
   // mNavComponent = NavComponent::Create(*this);
    //mNavComponent->SetLinearSpeed(60.0f);
    //mNavComponent->SetLinearAxis(1.0f);
    //mNavComponent->FollowPath(mGame.GetNavWorld().getStartNode(), mGame.GetNavWorld().getEndNode());
    
    SetPosition(game.GetGameMode()->GetSpawnPos());
    hitNum=0;
    mAudioComponentPtr = AudioComponent::Create(*this);
    mFreezeSoundPtr = mGame.GetAssetCache().Load<Sound>("Sounds/Freeze.wav");
    mDeathSoundPtr = mGame.GetAssetCache().Load<Sound>("Sounds/WilhelmScream.wav");
}

Enemy::~Enemy()
{
    
}

void Enemy::BeginTouch(Actor& other)
{
    //Super::BeginTouch(other);
    if (other.IsAlive() && IsA<Tile>(other)){
        SetIsAlive(false);
    }
    else if (other.IsAlive() && IsA<Cannonball>(other)){
        other.SetIsAlive(false);
        hitNum++;
        if (hitNum==3){
            SetIsAlive(false);
            mAudioComponentPtr->PlaySound(mDeathSoundPtr);
        }
    }
}

void Enemy::BeginPlay()
{
    mGame.GetWorld().AddEnemy(this);
}

void Enemy::EndPlay()
{
     mGame.GetWorld().RemoveEnemy(this);
}



void Enemy::Slow()
{
    mMoveComponentPtr->SetLinearSpeed(mMoveComponentPtr->GetLinearSpeed() * 0.5f);
    TimerHandle handle;
    mGame.getTimerManager().SetTimer(handle, this, &Enemy::Unslow, 1.0f);
    
   // mNavComponent->SetLinearSpeed(mNavComponent->GetLinearSpeed() * 0.5f);
    
    
    mAudioComponentPtr->PlaySound(mFreezeSoundPtr);
    
}

void Enemy::Unslow()
{
    if (this->IsAlive()){
        mMoveComponentPtr->SetLinearSpeed(mMoveComponentPtr->GetLinearSpeed() * 2.0f);
        //mNavComponent->SetLinearSpeed(mNavComponent->GetLinearSpeed() * 2.0f);
        mMeshComponentPtr->SetTextureIndex(0);
    }
}
