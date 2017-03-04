//
//  Arrow.h
//  Game-mac
//
//  Created by apple on 3/3/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"

class Arrow : public Actor
{
    DECL_ACTOR(Arrow, Actor);
public:
    Arrow(Game& game);
    ~Arrow();
    void BeginPlay() override;
    void Tick(float deltaTime) override;
    
    void UpdateWorldPos();
    void SetPlayer(ActorPtr player) { mActor = player; }
    
    ActorPtr GetPlayer() { return mActor;}
    void SetCheckPointPos(Vector3 pos) { mCheckPoint = pos; }
    
private:
    ActorPtr mActor;
    Vector3 mCheckPoint;
};

DECL_PTR(Arrow);
