// World.h
// All actors in the game world should either
// directly or indirectly (by parent) be
// controlled by World

#pragma once
#include <memory>
#include <vector>
#include "Actor.h"
#include "Enemy.h"

class World
{
public:
	World();
	~World();

	void AddActor(ActorPtr actor);
	void AddEnemy(Enemy* enemy);
	void RemoveEnemy(Enemy* enemy);
	std::vector<Enemy*> GetEnemiesInRange(Vector3 position, float radius);
	Enemy* GetClosestEnemy(Vector3 position);

	void Tick(float deltaTime);
	
	void RemoveAllActors();
private:
	std::vector<ActorPtr> mActors;
	std::unordered_set<Enemy*> mEnemies;
};
