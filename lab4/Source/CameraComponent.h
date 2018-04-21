#pragma once
#include "Component.h"
#include "MoveComponent.h"
#include "Actor.h"

class CameraComponent : public Component {
	DECL_COMPONENT(CameraComponent, Component);
public:
	CameraComponent(Actor& owner);

	void Tick(float deltaTime) override;
	void CalculateIdealCameraPos();
	void SetCameraToIdealPos();
	void SetCameraMoveComponent(MoveComponentPtr cameraMove) { mCameraMoveComponent = cameraMove; }
private:
	MoveComponentPtr mCameraMoveComponent;
	Matrix4 mCameraMatrix;
	Vector3 mCameraPosition;
	Vector3 mCameraForward;
	Vector3 mCameraLeft;
	Vector3 mCameraUp;
	Vector3 mIdealCameraPosition;
	Vector3 mCameraVelocity;
	Vector3 mDisplacement;
	Vector3 mSpringAccel;
	float springConst;
	float dampingConst;
	float followHDist;
	float followVDist;
	float targetOffset;
};

DECL_PTR(CameraComponent);