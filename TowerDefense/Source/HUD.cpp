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
    FontPtr font = mGame.GetAssetCache().Load<Font>("Fonts/Carlito-Regular.ttf");
    
    auto towerHealth = Actor::SpawnAttached(*this);
    mHealth = FontComponent::Create(*towerHealth);
    towerHealth->SetPosition(Vector3(200.0f, 300.0f, 0.0f));
     mHealth->SetFont(font);
    
    auto playerMoney = Actor::SpawnAttached(*this);
    mMoney = FontComponent::Create(*playerMoney);
    playerMoney->SetPosition(Vector3(200.0f, 350.0f, 0.0f));
    mMoney->SetFont(font);
    
    auto errors = Actor::SpawnAttached(*this);
    mError = FontComponent::Create(*errors);
    errors->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
    mError->SetFont(font);
}

void HUD::Tick(float deltaTime){
    std::string out = "Health: ";
    std::ostringstream stream;
    stream << mGame.GetGameMode()->GetHealth();
    out += stream.str();
    mHealth->SetText(out, Color::Green, 30);
    mHealth->SetAlignment(FontComponent::AlignLeft);
    
    out = "Money: ";
    std::ostringstream mStream;
    mStream << mGame.GetGameMode()->GetMoney();
    out += mStream.str();
    mMoney->SetText(out, Color::Green, 30);
    mMoney->SetAlignment(FontComponent::AlignLeft);
    
    
    mError->SetText(mErrorMessage, Color::Red, 30);
    mError->SetAlignment(FontComponent::AlignCenter);
}

void HUD::SetErrorMessage(std::string errorMessage) {
    mErrorMessage = errorMessage;
    TimerHandle handle;
    mGame.getTimerManager().SetTimer(handle, this, &HUD::ClearError, 2.0f);
}

void HUD::ClearError(){
    mErrorMessage = "";
}

