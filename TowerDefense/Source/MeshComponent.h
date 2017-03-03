//
//  MeshComponent.h
//  Game-mac
//
//  Created by apple on 2/5/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "DrawComponent.h"
#include "Mesh.h"

class MeshComponent : public DrawComponent
{
    DECL_COMPONENT(MeshComponent, DrawComponent);
public:
    MeshComponent(Actor& owner);
    void Draw(class Renderer& render) override;
    MeshPtr GetMesh();
    void SetMesh(MeshPtr mesh);
    void SetTextureIndex(int index);
private:
    MeshPtr mMesh;
    int mTextureIndex;
};

DECL_PTR(MeshComponent);