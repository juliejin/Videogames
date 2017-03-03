//
//  InputComponent.cpp
//  Game-mac
//
//  Created by apple on 2/5/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "InputComponent.h"
#include "Actor.h"
#include "Game.h"

IMPL_COMPONENT(InputComponent, MoveComponent);

InputComponent::InputComponent(Actor& owner)
    :MoveComponent(owner){
    
}

void InputComponent::OnLinearAxis(float value){
    SetLinearAxis(value);
}

void InputComponent::OnYawAxis(float value){
    SetYawAxis(value);
}

void InputComponent::OnPitchAxis(float value){
    SetPitchAxis(value);
}

void InputComponent::BindLinearAxis(const std::string &name){
    mOwner.GetGame().getInput().BindAxis(name, this, &InputComponent::OnLinearAxis);
}

void InputComponent::BindYawAxis(const std::string &name){
    mOwner.GetGame().getInput().BindAxis(name, this, &InputComponent::OnYawAxis);
}

void InputComponent::BindPitchAxis(const std::string &name){
    mOwner.GetGame().getInput().BindAxis(name, this, &InputComponent::OnPitchAxis);
}