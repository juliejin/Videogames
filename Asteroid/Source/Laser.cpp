//
//  Laser.cpp
//  Game-mac
//
//  Created by apple on 1/18/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Laser.h"
#include "Asteroid.h"
#include "Game.h"

IMPL_ACTOR(Laser, Actor);
Laser::Laser(Game& game):Actor(game){
    spriteComp = SpriteComponent::Create(*this);
     auto texture = game.GetAssetCache().Load<Texture>("Textures/Laser.png");
    spriteComp->SetTexture(texture);
    
    moveComp = MoveComponent::Create(*this, Component::PreTick);
    moveComp->SetLinearSpeed(600.0f);
    moveComp->SetLinearAxis(1.0f);
    
    //lifeSpan=1.0f;
    
    auto coll = SphereCollision::Create(*this);
    coll->RadiusFromTexture(texture);
    coll->SetScale(0.9f);
    
    audioComponent = AudioComponent::Create(*this);
    soundPtr = game.GetAssetCache().Load<Sound>("Sounds/AsteroidDie.wav");
    
}

void Laser::OnDieTimer(){
    SetIsAlive(false);
}

/*void Laser::Tick(float deltaTime) {
    if(lifeSpan<=0.0f){
        SetIsAlive(false);
    }
    else{
       lifeSpan-=deltaTime;
    }
    
}*/

void Laser::BeginPlay(){
    TimerHandle handle;
    mGame.getTimerManager().SetTimer(handle, this, &Laser::OnDieTimer, 1.0f);
}

void Laser::BeginTouch(Actor& other){
    Super::BeginTouch(other);
    if(IsAlive() && IsA<Asteroid>(other)){
        audioComponent->PlaySound(soundPtr);
        SetIsAlive(false);
        other.SetIsAlive(false);
        if(other.GetScale()==0.75f){
            for (int i=0; i<4; i++) {
                auto ast = Asteroid::Spawn(GetGame());
                ast->SetPosition(other.GetPosition());
                ast->SetScale(0.25f);
            }
        }
    }
}


