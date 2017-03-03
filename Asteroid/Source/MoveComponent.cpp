#include "MoveComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"

IMPL_COMPONENT(MoveComponent, Component);

MoveComponent::MoveComponent(Actor& owner)
	:Component(owner)
	,mLinearSpeed(0.0f)
	,mAngularSpeed(0.0f)
	,mLinearAxis(0.0f)
	,mAngularAxis(0.0f)
{

}

void MoveComponent::Tick(float deltaTime)
{
	// TODO
    if(!Math::IsZero(mAngularAxis)){
        float rot = mOwner.GetRotation();
            rot += mAngularSpeed * mAngularAxis * deltaTime;
        mOwner.SetRotation(rot);
    }
    
    if (!Math::IsZero(mLinearAxis))
    {
        Vector3 velocity= mOwner.GetForward()*mLinearSpeed*mLinearAxis;
        Vector3 newPosition = mOwner.GetPosition()+velocity*deltaTime;
        
        if( newPosition.x<-512){
            newPosition.Set(510, newPosition.y, newPosition.z);
        }else if (newPosition.x>512){
            newPosition.Set(-510, newPosition.y, newPosition.z);
        }
        if( newPosition.y<-384){
           newPosition.Set(newPosition.x, 382, newPosition.z);
        }else if (mOwner.GetPosition().y>384){
            newPosition.Set(newPosition.x, -382, newPosition.z);
        }  
        mOwner.SetPosition(newPosition);
    }
}

void MoveComponent::AddToLinearAxis(float delta)
{
	mLinearAxis += delta;
	mLinearAxis = Math::Clamp(mLinearAxis, -1.0f, 1.0f);
}

void MoveComponent::AddToAngularAxis(float delta)
{
	mAngularAxis += delta;
	mAngularAxis = Math::Clamp(mAngularAxis, -1.0f, 1.0f);
}

void MoveComponent::SetLinearAxis(float axis)
{
	mLinearAxis = Math::Clamp(axis, -1.0f, 1.0f);
}

void MoveComponent::SetAngularAxis(float axis)
{
	mAngularAxis = Math::Clamp(axis, -1.0f, 1.0f);
}

