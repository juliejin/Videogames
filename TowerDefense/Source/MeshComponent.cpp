//
//  MeshComponent.cpp
//  Game-mac
//
//  Created by apple on 2/5/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "MeshComponent.h"
#include "Actor.h"
#include "Renderer.h"

IMPL_COMPONENT(MeshComponent, DrawComponent);

MeshComponent::MeshComponent(Actor& owner)
:DrawComponent(owner){
    mTextureIndex =0;
}

void MeshComponent::Draw(class Renderer& render){
    if (mMesh != nullptr){
        render.DrawBasicMesh(mMesh->GetVertexArray(), mMesh->GetTexture(mTextureIndex), mOwner.GetWorldTransform());
    }
}

void MeshComponent::SetTextureIndex(int index){
    mTextureIndex = index;
}
MeshPtr MeshComponent::GetMesh(){
    return mMesh;
}

void MeshComponent::SetMesh(MeshPtr mesh){
    mMesh = mesh;
}