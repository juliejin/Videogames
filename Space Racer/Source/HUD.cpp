//
//  HUD.cpp
//  Game-mac
//
//  Created by apple on 2/19/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "HUD.h"
#include "Game.h"
#include "Font.h"
#include <string>
#include <sstream>

IMPL_ACTOR(HUD, Actor);

HUD::HUD(Game & game) : Actor(game){
}

void HUD::BeginPlay(){
    mScore = 0;
    
    auto font = mGame.GetAssetCache().Load<Font>("Fonts/Carlito-Regular.ttf");
    
    ScoreText = Actor::SpawnAttached(*this);
    ScoreFont = FontComponent::Create(*ScoreText);
    ScoreFont->SetFont(font);
   
    Vector3 pos1(-100.0f, 250.0f, 00.0f);
    ScoreText->SetPosition(pos1);
    
    TimeText = Actor::SpawnAttached(*this);
    TimeRemainingFont = FontComponent::Create(*TimeText);
    TimeRemainingFont->SetFont(font);
    Vector3 pos2(-100.0f,300.0f,0.0f);
    TimeText->SetPosition(pos2);
    
    GameOverText = Actor::SpawnAttached(*this);
    GameOverFont = FontComponent::Create(*GameOverText);
    GameOverFont->SetFont(font);
    Vector3 pos3 = mGame.GetRenderer().Unproject(Vector3(0, 0, 0.0));
    GameOverText->SetPosition(pos3);
    
    ScoreText->AddComponent(ScoreFont);
    GameOverText->AddComponent(GameOverFont);
    TimeText->AddComponent(TimeRemainingFont);
}

void HUD::Tick(float deltaTime){
 
}

void HUD::SetErrorMessage(std::string errorMessage) {
    
}

void HUD::ClearError(){
    
}

