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
    void BindAngularAxis(const std::string& name);
    void OnLinearAxis(float value);
    void OnAngularAxis(float value);
    
};
DECL_PTR(InputComponent);
