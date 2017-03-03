//
//  Tower.h
//  Game-mac
//
//  Created by apple on 2/16/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//
#pragma once
#include "Actor.h"

class Tower : public Actor
{
    DECL_ACTOR(Tower, Actor);
public:
    Tower(Game& game);
    ~Tower();
private:
    
};

DECL_PTR(Tower);
