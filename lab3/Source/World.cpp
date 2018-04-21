#include "World.h"
#include "Math.h"

World::World()
{

}

World::~World()
{

}

void World::AddActor(ActorPtr actor)
{
	mActors.emplace_back(actor);
}

void World::AddEnemy(Enemy* enemy)
{
	mEnemies.insert(enemy);
}

void World::RemoveEnemy(Enemy* enemy)
{
	auto iter = mEnemies.find(enemy);
	iter = mEnemies.erase(iter);
}

std::vector<Enemy*> World::GetEnemiesInRange(Vector3 position, float radius) {
	std::vector<Enemy*> foesInRange;
	for (Enemy* foe : mEnemies) {
		Vector3 foePos = foe->GetPosition();
		float distX = foePos.x - position.x;
		float distY = foePos.y - position.y;
		float distance = Math::Sqrt(distX * distX + distY * distY);

		if (distance <= radius) {
			foesInRange.emplace_back(foe);
		}
	}

	return foesInRange;
}

Enemy* World::GetClosestEnemy(Vector3 position) {
	Enemy* closestFoe = nullptr;
	for (Enemy* foe : mEnemies) {
		Vector3 foePos = foe->GetPosition();
		float distX = foePos.x - position.x;
		float distY = foePos.y - position.y;
		float distance = Math::Sqrt(distX * distX + distY * distY);

		if (distance <= 150.0f) {
			if (closestFoe == nullptr) {
				closestFoe = foe;
			}
			else {
				float distCloseX = closestFoe->GetPosition().x - position.x;
				float distCloseY = closestFoe->GetPosition().y - position.y;
				float closestDist = Math::Sqrt(distCloseX * distCloseX + distCloseY * distCloseY);
				if (distance < closestDist) {
					closestFoe = foe;
				}
			}
		}
	}

	return closestFoe;
}

void World::Tick(float deltaTime)
{
	// Tick a copy of the actor pointers, in case any actor adds more actors
	auto actors = mActors;
	for (auto& actor : actors)
	{
		actor->TickInternal(deltaTime);
	}

	// Remove any actors that are dead
	auto iter = mActors.begin();
	while (iter != mActors.end())
	{
		if (!(*iter)->IsAlive())
		{
			(*iter)->EndPlay();
			iter = mActors.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void World::RemoveAllActors()
{
	for (auto& actor : mActors)
	{
		actor->EndPlay();
	}
	mActors.clear();
}
