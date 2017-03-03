//
//  Asteroid.cpp
//  Game-mac
//
//  Created by apple on 1/16/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Asteroid.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Random.h"
#include "MoveComponent.h"
#include "SphereCollision.h"
#include "MeshComponent.h"
IMPL_ACTOR(Asteroid, Actor);

Asteroid::Asteroid(Game& game):Actor(game){
   /* auto sprite = SpriteComponent::Create(*this);
    auto texture = game.GetAssetCache().Load<Texture>("Textures/Asteroid.png");
    sprite->SetTexture(texture);
    */
    auto meshComponent = MeshComponent::Create(*this);
    auto& assetCache = game.GetAssetCache();
    auto mesh = assetCache.Load<Mesh>("Meshes/AsteroidMesh.itpmesh2");
    meshComponent->SetMesh(mesh);
    
    //SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
    
    //auto move = MoveComponent::Create(*this, Component::PreTick);
   // move->SetLinearSpeed(150.0f);
   // move->SetLinearAxis(1.0f);
    
    auto coll = SphereCollision::Create(*this);
    coll->RadiusFromMesh(mesh);
    coll->SetScale(0.1f);
}