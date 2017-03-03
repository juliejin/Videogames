//
//  NavComponent.cpp
//  Game-mac
//
//  Created by apple on 2/19/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "NavComponent.h"
#include "Actor.h"
#include <iostream>

IMPL_COMPONENT(NavComponent, MoveComponent);
NavComponent::NavComponent(Actor & owner) : MoveComponent(owner){
    
}
void NavComponent::Tick(float deltaTime){
    float length = mOwner.GetPosition().Length()-nextNode->tile->GetPosition().Length();
        if (length < 1.0f){
            if (nextNode->parent){
                nextNode = nextNode->parent;
            auto node = nextNode->tile->GetPosition() - mOwner.GetPosition();
            node.Normalize();
                float angle = 180*Math::Acos(Dot(node, Vector3::UnitX)/nextNode->tile->GetPosition().Length()*nextNode->tile->GetPosition().Length())/Math::Pi;
            float z = Cross(Vector3::UnitX, node).z;
            if (z < 0.0f){
               angle = -1.0f * angle;
            }
            mOwner.SetRotation(angle);
             
        }
        }
    MoveComponent::Tick(deltaTime);
    
}
void NavComponent::FollowPath(PathNode*start, PathNode*end){
    endNode = end;
    nextNode = start->parent;
    Vector3 node = nextNode->tile->GetPosition() - mOwner.GetPosition();
    node.Normalize();
   float angle = 180*Math::Acos(Dot(node, Vector3::UnitX)/nextNode->tile->GetPosition().Length()*nextNode->tile->GetPosition().Length())/Math::Pi;
    float z = Cross(Vector3::UnitX, node).z;
    if (z < 0.0f){
        angle *= -1.0f;
    }
    mOwner.SetRotation(angle);
     
}

