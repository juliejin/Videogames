
#pragma once
#include "Component.h"
#include "MoveComponent.h"

class CameraComponent : public Component{
    DECL_COMPONENT(CameraComponent, Component);
    
public:
    CameraComponent(Actor & owner);
    void Tick(float deltaTime) override;
    void SnapToIdeal();
    void Center();
     void SetMoveComp(MoveComponentPtr move){ mMoveComp = move; }
private:
    float minFollow;
    float maxFollow;
    MoveComponentPtr mMoveComp;
    Vector3 IdealCameraPos();
    Vector3 mActualCameraPos;
    Vector3 mCameraForward;
    Vector3 mCameraLeft;
    Vector3 mCameraUp;
    Vector3 vCameraVelocity;
    Vector3 TargetPos;
    Vector3 TargetOffset;
    Vector3 ShipPos;
    Vector3 ShipForward;
    Vector3 ShipUp;
    Matrix4 mFollowCamera;
    

};

DECL_PTR(CameraComponent);
