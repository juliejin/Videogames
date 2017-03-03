//
//  Actor.cpp
//  Game-mac
//
//  Created by apple on 2/5/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Actor.h"
#include "Game.h"

IMPL_ACTOR(Actor,Object);


Actor::Actor(Game& game)
:mGame(game)
,mParent(nullptr)
,mScale(1.0f)
,mIsAlive(true)
,mIsPaused(false)
{
    
}

Actor::~Actor()
{
    mGame.getTimerManager().ClearAllTimers(this);
    RemoveAllChildren();
    RemoveAllComponents();
}

void Actor::BeginPlay()
{
    
}

void Actor::Tick(float deltaTime)
{
    
    
}

void Actor::EndPlay()
{
    
}

void Actor::BeginTouch(Actor& other)
{
    
}

void Actor::AddComponent(ComponentPtr component, Component::UpdateType update)
{
    component->Register();
    if (update == Component::PostTick)
    {
        mPostTickComponents.emplace(component);
    }
    else
    {
        mPreTickComponents.emplace(component);
    }
}

void Actor::RemoveComponent(ComponentPtr component)
{
    component->Unregister();
    
    // This may be pre-tick or post-tick
    auto iter = mPreTickComponents.find(component);
    if (iter != mPreTickComponents.end())
    {
        mPreTickComponents.erase(component);
    }
    
    iter = mPostTickComponents.find(component);
    if (iter != mPreTickComponents.end())
    {
        mPostTickComponents.erase(component);
    }
}

void Actor::AddChild(ActorPtr child)
{
    mChildren.emplace(child);
    child->mParent = this;
    // Force the child to compute their transform matrix
    child->ComputeWorldTransform();
}

void Actor::RemoveChild(ActorPtr child)
{
    auto iter = mChildren.find(child);
    if (iter != mChildren.end())
    {
        (*iter)->EndPlay();
        mChildren.erase(iter);
    }
    child->mParent = nullptr;
}

Vector3 Actor::GetForward() const
{
    // Following Unreal coordinate system so X is forward
    return mWorldTransform.GetXAxis();
}

void Actor::ComputeWorldTransform()
{
    
    Matrix4 scaleMat = Matrix4::CreateScale(mScale);
    Matrix4 scaleRot = Matrix4::CreateFromQuaternion(mRotation);
    Matrix4 scaleTran = Matrix4::CreateTranslation(mPosition);
    mWorldTransform=scaleMat*scaleRot*scaleTran;
    
    if (mParent)
    {
        // My transform * Parent's transform
        mWorldTransform *= mParent->GetWorldTransform(); }
    // Tell my children to recompute their transforms
    for (auto& child : mChildren)
    {
        child->ComputeWorldTransform();
    }// TODO
}

void Actor::TickInternal(float deltaTime)
{
    if(mIsPaused==true)
        return;
    
    for(auto& tick : mPreTickComponents){
        tick->Tick(deltaTime);
    }
    Tick(deltaTime);
    for(auto& tick : mPostTickComponents){
        tick->Tick(deltaTime);
    }
    for(auto& tick : mChildren){
        tick->TickInternal(deltaTime);
    }
    /*for(std::unordered_set<ComponentPtr>::iterator it = mPreTickComponents.begin();
     it!=mPreTickComponents.end();++it){
     (*it)->Tick(deltaTime);
     }
     Tick(deltaTime);
     for(std::unordered_set<ComponentPtr>::iterator it = mPostTickComponents.begin();
     it!=mPostTickComponents.end();++it){
     (*it)->Tick(deltaTime);
     }
     for(std::unordered_set<ActorPtr>::iterator it = mChildren.begin();
     it!= mChildren.end();++it){
     (*it)->Tick(deltaTime);
     }*/
}

void Actor::RemoveAllComponents()
{
    // Unregister everything first
    for (auto& comp : mPreTickComponents)
    {
        comp->Unregister();
    }
    
    for (auto& comp : mPostTickComponents)
    {
        comp->Unregister();
    }
    
    mPreTickComponents.clear();
    mPostTickComponents.clear();
}

void Actor::RemoveAllChildren()
{
    for (auto& child : mChildren)
    {
        child->EndPlay();
        child->mParent = nullptr;
    }
    
    mChildren.clear();
}

