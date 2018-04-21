#include "MeshComponent.h"
#include "Renderer.h"
#include "Actor.h"

IMPL_COMPONENT(MeshComponent, DrawComponent);

MeshComponent::MeshComponent(Actor& owner) : DrawComponent(owner) {

}

void MeshComponent::Draw(class Renderer& render) {
	VertexArrayPtr vertArray = mMesh->GetVertexArray();
	TexturePtr texture = mMesh->GetTexture(mMeshIndex);
	const Matrix4& worldTransform = mOwner.GetWorldTransform();

	if (mMesh != nullptr) {
		render.DrawBasicMesh(vertArray, texture, worldTransform);
	}
}