//
//  FrostTower.h
//  Game-mac
//
//  Created by apple on 2/16/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Tower.h"

class FrostTower : public Tower
{
    DECL_ACTOR(FrostTower, Tower);
public:
    FrostTower(Game& game);
    ~FrostTower();
    void SlowerEnemies();
private:
    
};

DECL_PTR(FrostTower);
