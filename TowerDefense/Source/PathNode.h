//
//  PathNode.h
//  Game-mac
//
//  Created by apple on 2/19/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Tile.h"
#include <vector>

struct PathNode{
    std::vector<PathNode *> adjacencyList;
    TilePtr tile;
    Vector2 position;
    PathNode * parent;
    float fx;
    float gx;
    float hx;
    bool isBlocked;
};
