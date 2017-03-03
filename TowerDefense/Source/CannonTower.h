//
//  CannonTower.h
//  Game-mac
//
//  Created by apple on 2/16/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Tower.h"

class CannonTower : public Tower
{
    DECL_ACTOR(CannonTower, Tower);
public:
    CannonTower(Game& game);
    ~CannonTower();
    void CannonBallAttack();
private:
    
};
DECL_PTR(CannonTower);
