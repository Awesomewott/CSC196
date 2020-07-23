#include "Game.h"
#include "Math/Math2.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include "Math/Transform.h"
#include "Object/Actor.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Object/Scene.h"
#include "Graphics/ParticalSystem.h"
#include "core.h"
#include <vector>
#include <string>
#include <list>


void Game::Initialize()
{
	// initalize engine
	m_scene.Startup();
	g_particleSystem.Startup();

	nc::Actor* player = new Player;
	player->Load("Player.txt");
	m_scene.AddActor(player);
	

	for (size_t i = 0; i < 10; i++)
	{
		nc::Actor* actor = new Enemy;
		actor->Load("enemy.txt");

		Enemy* enemy = dynamic_cast<Enemy*>(actor);
		enemy->SetTarget(player);
		enemy->SetSpeed(nc::random(50, 100));

		actor->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0 , 600) };
		m_scene.AddActor(actor);
	}
}

bool Game::Update(float dt)
{

		frameTime = dt;
		spawnTimer += dt;

		if (spawnTimer >= 3.0f)
		{
			spawnTimer = 0;

			//spawn enemy

			Enemy* enemy = new Enemy;
			enemy->Load("enemy.txt");
			enemy->SetTarget(m_scene.GetActor<Player>());
			enemy->SetSpeed(nc::random(50, 100));

			enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0 , 600) };
			m_scene.AddActor(enemy);
		}

		//if (Core::Input::IsPressed(VK_SPACE))
		//{
		//	Enemy* enemy = scene.GetActor<Enemy>();
		//	scene.RemoveActor(enemy);
			/*
			auto enemies = GetActors<Enemy>();
			for (Enemy* enemy : enemies)
			{
				RemoveActor(enemy);
			}
			*/
			//}

			//DWORD time = GetTickCount();
			//deltaTime = time - prevTime;
			//prevTime = time;
		bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	
		Player* player = m_scene.GetActor<Player>();

		int x, y;
		Core::Input::GetMousePos(x, y);

		if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))

		{
			nc::Color colors[]{ {1,1,1}, nc::Color::red, {1,1,0}, {0,1,1} };
			nc::Color color = colors[rand() % 4];
			g_particleSystem.Create({ x, y }, 0, 180, 30, 1, color, 100, 200);

		}

		m_scene.Update(dt);
		g_particleSystem.Update(dt);
		return quit;
	}


void Game::Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 1, 1, 1 });
	graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frameTime).c_str());
	//graphics.DrawString(10, 30, std::to_string(deltaTime / 1000.0f).c_str());

	float  v = (std::sin(t) + 1.0f) * 0.5f; // (-1 <-> 1) -> (0 - 2)

	nc::Color c = nc::Lerp(nc::Color{ 1, 0, 0 }, nc::Color{ 0, 1, 1 }, v);
	graphics.SetColor(t);
	nc::Vector2 p = nc::Lerp(nc::Vector2{ 200, 200 }, nc::Vector2{ 600, 200 }, v);
	

	//graphics.SetColor(color); // [R] 1 byte (8-bits) | [G] 1 byte (8-bits) | [B] 1 byte {8-bits)
	
	g_particleSystem.Draw(graphics);
	m_scene.Draw(graphics);
}
