#include "Arrow.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"

IMPL_ACTOR(Arrow, Actor);

Arrow::Arrow(Game& game) : Actor(game) {
	auto mesh = MeshComponent::Create(*this);
	AssetCache& texture = game.GetAssetCache();
	mesh->SetMesh(texture.Load<Mesh>("Meshes/Arrow.itpmesh2"));
}

void Arrow::Tick(float deltaTime) {
	Super::Tick(deltaTime);

	Vector3 arrowPos = UpdateWorldPosition();
	SetPosition(arrowPos);

	Vector3 shipToCheckpoint = mNextCheckpointPos - mPlayer->GetPosition();
	shipToCheckpoint.Normalize();
	Vector3 rotAxis = Cross(Vector3::UnitX, shipToCheckpoint);
	rotAxis.Normalize();
	float dotprod = Dot(Vector3::UnitX, shipToCheckpoint);
	if (Math::IsZero(dotprod - 1.0f)) {
		SetRotation(Quaternion::Identity);
	}
	else if (Math::IsZero(dotprod + 1.0f)) {
		Quaternion rotQuat = Quaternion(Vector3(0.0f, 0.0f, 1.0f), Math::Pi);
		SetRotation(rotQuat);
	}
	else {
		float rotAngle = Math::Acos(dotprod);
		Quaternion rotQuat = Quaternion(rotAxis, rotAngle);
		SetRotation(rotQuat);
	}
}

void Arrow::BeginPlay() {
	Vector3 arrowPos = UpdateWorldPosition();
	SetPosition(arrowPos);
	SetRotation(Quaternion::Identity);
}

Vector3 Arrow::UpdateWorldPosition() {
	Vector3 screenPoint = Vector3(0.0f, 150.0f, 0.6f);
	Vector3 arrowPoint = mGame.GetRenderer().Unproject(screenPoint);
	return arrowPoint;
}