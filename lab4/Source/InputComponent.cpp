#include "InputComponent.h"
#include "Actor.h"
#include "Game.h"

IMPL_COMPONENT(InputComponent, MoveComponent);

InputComponent::InputComponent(Actor& owner) : MoveComponent(owner) {

}

void InputComponent::BindLinearAxis(const std::string& name) {
	mOwner.GetGame().GetInput().BindAxis(name, this, &InputComponent::OnLinearAxis);
}

void InputComponent::BindYawAxis(const std::string& name) {
	mOwner.GetGame().GetInput().BindAxis(name, this, &InputComponent::OnYawAxis);
}

void InputComponent::BindPitchAxis(const std::string& name) {
	mOwner.GetGame().GetInput().BindAxis(name, this, &InputComponent::OnPitchAxis);
}

void InputComponent::OnLinearAxis(float value) {
	SetLinearAxis(value);
}

void InputComponent::OnYawAxis(float value) {
	SetYawAxis(value);
}

void InputComponent::OnPitchAxis(float value) {
	SetPitchAxis(value);
}