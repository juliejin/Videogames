#include "CameraComponent.h"
#include "Actor.h"
#include "Renderer.h"
#include "Game.h"

IMPL_COMPONENT(CameraComponent, Component);

CameraComponent::CameraComponent(Actor & owner) : Component(owner)
{
    minFollow = 200.0f;
    maxFollow = 250.0f;
}

void CameraComponent::Tick(float deltaTime){
    float SpringConstant = 200.0f;
    float fDampConstant = 2.0f * Math::Sqrt(SpringConstant);
    
    ShipUp = mOwner.GetWorldTransform().GetZAxis();
    ShipForward = mOwner.GetWorldTransform().GetXAxis();
    ShipForward.Normalize();
    ShipUp.Normalize();

    Vector3 vDisplacement = mActualCameraPos - IdealCameraPos();
    Vector3 vSpringAccel = (-SpringConstant * vDisplacement) - (fDampConstant * vCameraVelocity);
    vCameraVelocity += vSpringAccel * deltaTime;
    mActualCameraPos += vCameraVelocity * deltaTime;
    
    TargetPos = mOwner.GetPosition() + ShipForward * TargetOffset;
    mCameraForward = TargetPos - mActualCameraPos;
    mCameraForward.Normalize();
    mCameraLeft = Cross(ShipUp, mCameraForward);
    mCameraLeft.Normalize();
    mCameraUp = Cross(mCameraForward, mCameraLeft);
    mCameraUp.Normalize();
    mFollowCamera = Matrix4::CreateLookAt(mActualCameraPos, TargetPos, mCameraUp);
    mOwner.GetGame().GetRenderer().UpdateViewMatrix(mFollowCamera);
}

Vector3 CameraComponent::IdealCameraPos(){
     ShipPos = mOwner.GetPosition();
    ShipForward = mOwner.GetWorldTransform().GetXAxis();
     ShipUp = mOwner.GetWorldTransform().GetZAxis();
    float hFollow = Math::Lerp(minFollow, maxFollow, mMoveComp->GetLinearAxis());
    Vector3 mCameraPos = ShipPos - hFollow * ShipForward + 100.0f * ShipUp;
    mCameraForward = TargetPos - mActualCameraPos;
    mCameraForward.Normalize();
    mCameraLeft = Cross(ShipUp,mCameraForward);
    mCameraLeft.Normalize();
    mCameraUp = Cross(mCameraForward,mCameraLeft);
    mCameraUp.Normalize();
    return mCameraPos;
}

void CameraComponent::Center()
{
    mFollowCamera = Matrix4::CreateLookAt(IdealCameraPos(), TargetPos, mCameraUp);
    mOwner.GetGame().GetRenderer().UpdateViewMatrix(mFollowCamera);
}

void CameraComponent::SnapToIdeal(){
    mFollowCamera = Matrix4::CreateLookAt(mActualCameraPos, TargetPos, mCameraUp);
    mOwner.GetGame().GetRenderer().UpdateViewMatrix(mFollowCamera);
}