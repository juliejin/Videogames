//
//  NavComponent.h
//  Game-mac
//
//  Created by apple on 2/19/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "MoveComponent.h"
#include "PathNode.h"

class NavComponent : public MoveComponent{
    DECL_COMPONENT(NavComponent, MoveComponent);
public:
    NavComponent(Actor & owner);
    void Tick(float deltaTime) override;
    void FollowPath(PathNode * start, PathNode * end);
    
private:
    PathNode * nextNode;
    PathNode * endNode;
    
};
DECL_PTR(NavComponent);
