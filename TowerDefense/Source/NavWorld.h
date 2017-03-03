//
//  NavWorld.h
//  Game-mac
//
//  Created by apple on 2/19/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "PathNode.h"
#include <vector>

class NavWorld{
public:
    NavWorld();
    ~NavWorld();
    void Init(std::vector<std::vector<TilePtr>> mGrid);
    void setStartNode(int x, int y);
    void setEndNode(int x, int y);
    PathNode * getStartNode() { return startNode; }
    PathNode * getEndNode() { return endNode;  }
    bool TryFindPath();
    bool setBlock(int x,int y);
private:
    std::vector<std::vector<PathNode *> > mNavWorldGrid;
    PathNode* startNode;
    PathNode* endNode;
    float CalculateHX(PathNode * node);
    float CalaulateGX(PathNode * parent);
    std::unordered_set<PathNode *> openSet;
    std::unordered_set<PathNode *> closedSet;
};
