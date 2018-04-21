#include "SpriteComponent.h"
#include "Actor.h"
#include <SDL/SDL.h>
#include "Renderer.h"

IMPL_COMPONENT(SpriteComponent, DrawComponent);

SpriteComponent::SpriteComponent(Actor& owner)
	:DrawComponent(owner)
{

}

void SpriteComponent::Draw(Renderer& render)
{
	if (mTexture != nullptr) {
		Matrix4 scale = Matrix4::CreateScale((float)mTexture->GetWidth(), (float)mTexture->GetHeight(), 1.0f);
		Matrix4 worldTrans = scale * mOwner.GetWorldTransform();
		render.DrawSprite(mTexture, worldTrans);
	}
}

