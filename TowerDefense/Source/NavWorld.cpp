//
//  NavWorld.cpp
//  Game-mac
//
//  Created by apple on 2/19/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "NavWorld.h"
#include <unordered_set>
#include <iostream>

NavWorld::NavWorld(){
    
}

NavWorld::~NavWorld(){
    
}

void NavWorld::setStartNode(int x, int y){
            startNode = mNavWorldGrid[x][y];
}

void NavWorld::setEndNode(int x, int y){
            endNode = mNavWorldGrid[x][y];
}

void NavWorld::Init(std::vector<std::vector<TilePtr> > mGrid){
    mNavWorldGrid.resize(mGrid.size());
    for (int i = 0; i < mNavWorldGrid.size(); i++){
        for (int j = 0; j <mGrid[i].size(); j++){
            PathNode * node = new PathNode();
            node->position = Vector2(i,j);
            node->tile = mGrid[i][j];
            node->parent = nullptr;
            node->gx = 0.0f;
            node->hx = 0.0f;
            node->fx = node->gx + node->hx;
            node->isBlocked = false;
            mNavWorldGrid[i].push_back(node);
        }
    }
    
    for (int i = 0; i < mNavWorldGrid.size(); i++){
        for (int j = 0; j < mNavWorldGrid[i].size(); j++){
            PathNode * node = mNavWorldGrid[i][j];
            if (i-1 >= 0){
                node->adjacencyList.push_back(mNavWorldGrid[i - 1][j]);
            }
            if (i+1 < mNavWorldGrid.size()){
                node->adjacencyList.push_back(mNavWorldGrid[i + 1][j]);
            }
            if (j-1 >= 0){
                node->adjacencyList.push_back(mNavWorldGrid[i][j - 1]);
            }
            if (j+1 < mNavWorldGrid[i].size()){
                node->adjacencyList.push_back(mNavWorldGrid[i][j + 1]);
            }
        }
    }
}

//use Manhatan distance
float NavWorld::CalculateHX(PathNode * node){
    if (node == nullptr){
        return 0.0f;
    }else{
        float dx = node->position.x-startNode->position.x;
        float dy = node->position.y-startNode->position.y;
        return dx + dy;
    }
}

float NavWorld::CalaulateGX(PathNode * parent){
    if (parent == nullptr)
        return 0.0f;
    return CalaulateGX(parent->parent)+1.0f;
}

bool NavWorld::TryFindPath(){
    openSet.clear();
    closedSet.clear();
    for (int i = 0; i < mNavWorldGrid.size(); i++){
        for (int j = 0; j < mNavWorldGrid[i].size(); j++){
            mNavWorldGrid[i][j]->tile->SetOnPath(false);
        }
    }
    
    PathNode* curr=endNode;
    curr->hx = CalculateHX(curr);
    curr->gx = 0.0f+1.0f;
    curr->fx = curr->hx+curr->gx;
    closedSet.insert(curr);
    
    while(curr != startNode){
        for(auto& node : curr->adjacencyList){
            if(!closedSet.count(node)){
             if(openSet.count(node)){
                    float newGX = CalaulateGX(curr);
                        if(newGX<node->gx){
                        node->gx = newGX;
                        node->fx = node->gx + node->hx;
                        node->parent=curr;
                        }
             }else if(!node->isBlocked){
                        float newGX = CalaulateGX(curr);
                        openSet.insert(node);
                        float newHX = CalculateHX(node);
                        node->gx = newGX;
                        node->hx = newHX;
                        node->fx = node->gx + node->hx;
                        node->parent=curr;
             }
            }
        }
            if (openSet.size() == 0){
                return false;
            }
                curr=*openSet.begin();
                for (auto it = openSet.begin(); it != openSet.end(); it++){
                PathNode * temp = *it;
                    if (temp->fx < curr->fx){
                        curr = temp;
                    }
                }
                closedSet.insert(curr);
                openSet.erase(curr);
    }
    if(curr==startNode){
        PathNode * current = startNode;
        while (current != nullptr){
            current->tile->SetOnPath(true);
            current = current->parent;
        }
        return true;
    }
        return false;
}

bool NavWorld::setBlock(int x,int y){
    if (x < mNavWorldGrid.size()){
        if (y < (int)(mNavWorldGrid[x].size())){
            mNavWorldGrid[x][y]->isBlocked = true;
            if (TryFindPath()){
                return true;
            }else {
                mNavWorldGrid[x][y]->isBlocked = false;
                TryFindPath();
                return false;
            }
        }
    }
    return false;
}
