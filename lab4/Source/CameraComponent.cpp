#include "CameraComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"

IMPL_COMPONENT(CameraComponent, Component);

CameraComponent::CameraComponent(Actor& owner) : Component(owner) {
	springConst = 200.0f;
	dampingConst = 2.0f * sqrt(springConst);
	followHDist = 200.0f;
	followVDist = 100.0f;
	targetOffset = 150.0f;
}

void CameraComponent::Tick(float deltaTime) {
	Matrix4 worldtrans = mOwner.GetWorldTransform();
	Vector3 pos = mOwner.GetPosition();
	Vector3 fwd = worldtrans.GetXAxis();
	Vector3 up = worldtrans.GetZAxis();
	Vector3 left = worldtrans.GetYAxis();
	Vector3 targetPos = pos + fwd * targetOffset;
	CalculateIdealCameraPos();
	mDisplacement = mCameraPosition - mIdealCameraPosition;
	mSpringAccel = (-springConst * mDisplacement) - (dampingConst * mCameraVelocity);
	mCameraVelocity += mSpringAccel * deltaTime;
	mCameraPosition += mCameraVelocity * deltaTime;
	mCameraForward = targetPos - mCameraPosition;
	mCameraForward.Normalize();
	mCameraLeft = Cross(up, mCameraForward);
	mCameraLeft.Normalize();
	mCameraUp = Cross(mCameraForward, left);
	mCameraUp.Normalize();
	mCameraVelocity = mCameraForward * mCameraMoveComponent->GetLinearAxis() * mCameraMoveComponent->GetLinearSpeed();
	mCameraMatrix = Matrix4::CreateLookAt(mCameraPosition, targetPos, mCameraUp);
	mOwner.GetGame().GetRenderer().UpdateViewMatrix(mCameraMatrix);
}

void CameraComponent::CalculateIdealCameraPos() {
	Matrix4 worldtrans = mOwner.GetWorldTransform();
	Vector3 pos = mOwner.GetPosition();
	Vector3 fwd = worldtrans.GetXAxis();
	Vector3 up = worldtrans.GetZAxis();
	Vector3 targetPos = pos + fwd * targetOffset;
	followHDist = Math::Lerp(200.0f, 250.0f, mCameraMoveComponent->GetLinearAxis());
	mIdealCameraPosition = pos - fwd * followHDist + up * followVDist;
}

void CameraComponent::SetCameraToIdealPos() {
	mCameraPosition = mIdealCameraPosition;
}