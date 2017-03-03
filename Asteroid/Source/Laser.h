//
//  Laser.h
//  Game-mac
//
//  Created by apple on 1/18/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//
#pragma once
#include "Actor.h"
#include "MoveComponent.h"
#include "Texture.h"
#include "SpriteComponent.h"
#include "SphereCollision.h"
#include "AudioComponent.h"

class Laser: public Actor
{
    DECL_ACTOR(Laser, Actor);
public:
   Laser(Game& game);
    //void Tick(float deltaTime) override;
    void BeginTouch(Actor& other) override;
     void OnDieTimer();
    void BeginPlay()override;
private:
    MoveComponentPtr moveComp;
    SpriteComponentPtr spriteComp;
    //float lifeSpan;
    AudioComponentPtr audioComponent;
    SoundPtr soundPtr;
};
DECL_PTR(Laser);