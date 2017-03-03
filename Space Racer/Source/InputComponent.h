//
//  InputComponent.h
//  Game-mac
//
//  Created by apple on 2/5/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "MoveComponent.h"
#include <iostream>

class InputComponent : public MoveComponent
{
    DECL_COMPONENT(InputComponent, MoveComponent);
public:
    InputComponent(Actor& owner);
    void BindLinearAxis(const std::string& name);
    void BindYawAxis(const std::string& name);
    void BindPitchAxis(const std::string& name);
    void OnLinearAxis(float value);
    void OnYawAxis(float value);
    void OnPitchAxis(float value);
    
};
DECL_PTR(InputComponent);
