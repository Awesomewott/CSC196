#pragma once
#include "core.h"
#include "Object/Scene.h"
class Game
{
	public:
		void Initialize();

		bool Update(float dt);
		void Draw(Core::Graphics& graphics);

protected:
	int m_score{ 0 };
	int m_lives{ 3 };

	nc::Scene m_scene;

	float frameTime;
	float spawnTimer{ 0 };
	float t{ 0 };

};

