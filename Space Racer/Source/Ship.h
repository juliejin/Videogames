//
//  Ship.h
//  Game-mac
//
//  Created by apple on 1/17/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "InputComponent.h"
#include "Texture.h"
#include "SpriteComponent.h"
//#include "Laser.h"
#include "AudioComponent.h"
#include "MeshComponent.h"
#include "SphereCollision.h"
#include "CameraComponent.h"


class Ship : public Actor
{
    DECL_ACTOR(Ship, Actor);
public:
    Ship(Game& game);
    MoveComponentPtr GetInputComponent();
    void Tick(float deltaTime) override;
    void BeginPlay() override;
    void FireMissile();
    void BeginTouch(Actor& other) override;
    void OnRespawnShip();
    void Recenter();
private:
    
    TexturePtr texturePtrNormal;
    TexturePtr texturePtrThrust;
    //SpriteComponentPtr spriteComponentPtr;
    MeshComponentPtr meshComponentPtr;
    SoundPtr fireSoundPtr;
    AudioComponentPtr audioComponentPtr;
    SoundPtr engineSoundPtr;
    AudioComponentPtr engineAudioComponent;
    SoundCue soundCue;
    InputComponentPtr inputComponent;
    SphereCollisionPtr mSphereCollision;
    AudioComponentPtr audioComponent;
    SoundPtr dieSoundPtr;
    CameraComponentPtr mCameraComponent;
  
};
DECL_PTR(Ship);
