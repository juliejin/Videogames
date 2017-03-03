//
//  Asteroid.h
//  Game-mac
//
//  Created by apple on 1/16/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//
#pragma once
#include "Actor.h"

class Asteroid : public Actor
{
    DECL_ACTOR(Asteroid, Actor);
public:
    Asteroid(Game& game);
};
DECL_PTR(Asteroid);

