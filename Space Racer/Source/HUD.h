//
//  HUD.h
//  Game-mac
//
//  Created by apple on 2/19/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "FontComponent.h"

class HUD : public Actor {
    DECL_ACTOR(HUD, Actor);
public:
    HUD(Game & game);
    void Tick(float deltaTime) override;
    void SetErrorMessage(std::string errorMessage);
    void BeginPlay() override;
private:
    void ClearError();
    FontComponentPtr mHealth;
    FontComponentPtr mMoney;
    FontComponentPtr mError;
    std::string mErrorMessage = "";
    
    int mScore;
    int mTime;
    //int mHealth;
    
    ActorPtr ScoreText;
    ActorPtr GameOverText;
    ActorPtr TimeText;
    
    FontComponentPtr ScoreFont;
    FontComponentPtr GameOverFont;
    FontComponentPtr TimeRemainingFont;
};
DECL_PTR(HUD);
