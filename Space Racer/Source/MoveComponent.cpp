#include "MoveComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"

IMPL_COMPONENT(MoveComponent, Component);

MoveComponent::MoveComponent(Actor& owner)
	:Component(owner)
	,mLinearSpeed(0.0f)
	,mYawSpeed(0.0f)
	,mLinearAxis(0.0f)
	,mYawAxis(0.0f)
    ,mPitchAxis(0.0f)
    ,mPitchSpeed(0.0f)
{

}

void MoveComponent::Tick(float deltaTime)
{
    if(!Math::IsZero(mYawAxis)){
       Quaternion rot = mOwner.GetRotation();
        float rotation = mYawSpeed * mYawAxis * deltaTime;
        Quaternion inc = Quaternion(mOwner.GetWorldTransform().GetZAxis(), rotation);
        rot = Concatenate(rot, inc);
        mOwner.SetRotation(rot);
    }
    
    if(!Math::IsZero(mPitchAxis)){
        Quaternion rot = mOwner.GetRotation();
        float rotation = mPitchSpeed * mPitchAxis * deltaTime;
        Quaternion inc = Quaternion(mOwner.GetWorldTransform().GetYAxis(), rotation);
        rot = Concatenate(rot, inc);
        mOwner.SetRotation(rot);
    }
    
    if (!Math::IsZero(mLinearAxis))
    {
        Vector3 velocity= mOwner.GetForward()*mLinearSpeed*mLinearAxis;
        Vector3 newPosition = mOwner.GetPosition()+velocity*deltaTime;
        
       /* if( newPosition.x<-512){
            newPosition.Set(510, newPosition.y, newPosition.z);
        }else if (newPosition.x>512){
            newPosition.Set(-510, newPosition.y, newPosition.z);
        }
        if( newPosition.y<-384){
            newPosition.Set(newPosition.x, 382, newPosition.z);
        }else if (mOwner.GetPosition().y>384){
            newPosition.Set(newPosition.x, -382, newPosition.z);
        }*/
        mOwner.SetPosition(newPosition);
    }

}

void MoveComponent::AddToLinearAxis(float delta)
{
	mLinearAxis += delta;
	mLinearAxis = Math::Clamp(mLinearAxis, -1.0f, 1.0f);
}


void MoveComponent::SetLinearAxis(float axis)
{
	mLinearAxis = Math::Clamp(axis, -1.0f, 1.0f);
}

void MoveComponent::SetYawAxis(float axis)
{
    mYawAxis = Math::Clamp(axis, -1.0f, 1.0f);
}

void MoveComponent::SetPitchAxis(float axis)
{
    mPitchAxis = Math::Clamp(axis, -1.0f, 1.0f);
}

void MoveComponent::AddToYawAxis(float delta)
{
    mYawAxis += delta;
    mYawAxis = Math::Clamp(mYawAxis, -1.0f, 1.0f);
}

void MoveComponent::AddToPitchAxis(float delta)
{
    mPitchAxis += delta;
    mPitchAxis = Math::Clamp(mPitchAxis, -1.0f, 1.0f);
}

