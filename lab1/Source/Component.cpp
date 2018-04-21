#include "Component.h"
#include "Actor.h"

IMPL_COMPONENT(Component, Object);

Component::Component(Actor& owner)
	:mOwner(owner)
{
}

Component::~Component()
{

}

void Component::Tick(float deltaTime)
{

}

void Component::Register()
{

}

void Component::Unregister()
{

}
