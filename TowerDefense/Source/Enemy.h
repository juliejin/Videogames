//
//  Enemy.h
//  Game-mac
//
//  Created by apple on 2/16/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "SphereCollision.h"
#include "MoveComponent.h"
#include "MeshComponent.h"
#include "AudioComponent.h"
#include "NavComponent.h"

class Enemy : public Actor
{
    DECL_ACTOR(Enemy, Actor);
public:
    Enemy(Game& game);
    ~Enemy();
    void BeginTouch(Actor& other) override;
    void BeginPlay() override;
    void EndPlay() override;
    void Slow();
    void Unslow();
    NavComponentPtr getNav(){return mNavComponent;}
private:
    int health;
    MeshComponentPtr mMeshComponentPtr;
    MoveComponentPtr mMoveComponentPtr;
    SphereCollisionPtr mSphereCollisionPtr;
    NavComponentPtr mNavComponent;
    int hitNum;
    AudioComponentPtr mAudioComponentPtr;
    SoundPtr mFreezeSoundPtr;
    SoundPtr mDeathSoundPtr;
};

DECL_PTR(Enemy);
