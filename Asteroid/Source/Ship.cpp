//
//  Ship.cpp
//  Game-mac
//
//  Created by apple on 1/17/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Ship.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Sound.h"
#include "Asteroid.h"

IMPL_ACTOR(Ship, Actor);


Ship::Ship(Game& game):Actor(game){
    /*spriteComponentPtr = SpriteComponent::Create(*this);
    texturePtrNormal = game.GetAssetCache().Load<Texture>("Textures/Spaceship.png");
    texturePtrThrust = game.GetAssetCache().Load<Texture>("Textures/SpaceshipWithThrust.png");
    spriteComponentPtr->SetTexture(texturePtrNormal);*/
    meshComponentPtr = MeshComponent::Create(* this);
    auto& assetCache = game.GetAssetCache();
    auto mesh = assetCache.Load<Mesh>("Meshes/PlayerShip.itpmesh2");
    meshComponentPtr->SetMesh(mesh);
    
    SetScale(0.5f);
    
    inputComponent = InputComponent::Create(*this, Component::PreTick);
    inputComponent->SetLinearSpeed(400.0f);
     inputComponent->SetAngularSpeed(Math::TwoPi);
    
    audioComponentPtr= AudioComponent::Create(*this);
     fireSoundPtr = game.GetAssetCache().Load<Sound>("Sounds/Laser.wav");
    engineSoundPtr = game.GetAssetCache().Load<Sound>("Sounds/ShipEngine.wav");
    soundCue = engineAudioComponent->PlaySound(engineSoundPtr,true);
    soundCue.Pause();
    
    mSphereCollision = SphereCollision::Create(*this);
    mSphereCollision->RadiusFromMesh(mesh);
    mSphereCollision->SetScale(0.5f);
    
    audioComponent = AudioComponent::Create(*this);
    dieSoundPtr = game.GetAssetCache().Load<Sound>("Sounds/ShipDie.wav");
    
}

MoveComponentPtr Ship::GetInputComponent(){
    return inputComponent;
}

void Ship::BeginPlay(){
    mGame.getInput().BindAction("Fire", IE_Pressed, this, &Ship::FireMissile);
    //mGame.getInput().BindAxis("Move", this, mGame.getInput().HandleKeyPressed('s'));
    inputComponent->BindLinearAxis("Move");
    inputComponent->BindAngularAxis("Rotate");

}
void Ship::BeginTouch(Actor &other){
    if(IsPaused()==false&& IsA<Asteroid>(other)){
        setIsPaused(true);
        meshComponentPtr->SetIsVisible(false);
        audioComponent->PlaySound(dieSoundPtr);
        TimerHandle handle;
        mGame.getTimerManager().SetTimer(handle, this, &Ship::OnRespawnShip, 1.0f);
    }
}
void Ship::OnRespawnShip(){
    SetPosition(Vector3(0.0f, 0.0f, 0.0f));
    SetRotation(Math::PiOver2);
     meshComponentPtr->SetIsVisible(true);
     setIsPaused(false);
}


void Ship::Tick(float deltaTime){
    if(inputComponent->GetLinearAxis()==0.0f){
       // spriteComponentPtr->SetTexture(texturePtrNormal);
        soundCue.Pause();
    }else{
       // spriteComponentPtr->SetTexture(texturePtrThrust);
        soundCue.Resume();
         Super::Tick(deltaTime);
    }
}

void Ship::FireMissile(){
    if(IsPaused()==false){
    auto laser = Laser::Spawn(mGame);
   laser->SetPosition(GetPosition());
    laser->SetRotation(GetRotation());
    
    audioComponentPtr->PlaySound(fireSoundPtr);
    }
}
