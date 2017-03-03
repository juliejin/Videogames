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

void InputComponent::OnAngularAxis(float value){
    SetAngularAxis(value);
}

void InputComponent::BindLinearAxis(const std::string &name){
    mOwner.GetGame().getInput().BindAxis(name, this, &InputComponent::OnLinearAxis);
}

void InputComponent::BindAngularAxis(const std::string &name){
    mOwner.GetGame().getInput().BindAxis(name, this, &InputComponent::OnAngularAxis);
}