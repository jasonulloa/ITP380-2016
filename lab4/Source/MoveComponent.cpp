#include "MoveComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"

IMPL_COMPONENT(MoveComponent, Component);

MoveComponent::MoveComponent(Actor& owner)
	:Component(owner)
	,mLinearSpeed(0.0f)
	,mYawSpeed(0.0f)
	,mPitchSpeed(0.0f)
	,mLinearAxis(0.0f)
	,mYawAxis(0.0f)
	,mPitchAxis(0.0f)
{

}

void MoveComponent::Tick(float deltaTime)
{
	Matrix4 worldtrans = mOwner.GetWorldTransform();
	Vector3 yawAxis = worldtrans.GetZAxis();
	Vector3 pitchAxis = worldtrans.GetYAxis();
	Quaternion rot = mOwner.GetRotation();

	if (!Math::IsZero(mYawAxis)){
		float yawAngle = mYawSpeed * mYawAxis * deltaTime;
		Quaternion incQuat = Quaternion(yawAxis, yawAngle);
		rot = Concatenate(rot, incQuat);
	}

	if (!Math::IsZero(mPitchAxis)) {
		float pitchAngle = mPitchSpeed * mPitchAxis * deltaTime;
		Quaternion incQuat = Quaternion(pitchAxis, pitchAngle);
		rot = Concatenate(rot, incQuat);
	}

	mOwner.SetRotation(rot);
	
	if (!Math::IsZero(mLinearAxis)) { 
		// Update velocity based on current forward
		Vector3 forward = mOwner.GetForward();
		mVelocity = forward * mLinearSpeed * mLinearAxis;

		// Update position of owner based on velocity
		Vector3 pos = mOwner.GetPosition();
		pos = pos + mVelocity * deltaTime;
		mOwner.SetPosition(pos);
	}
}

void MoveComponent::AddToLinearAxis(float delta)
{
	mLinearAxis += delta;
	mLinearAxis = Math::Clamp(mLinearAxis, -1.0f, 1.0f);
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