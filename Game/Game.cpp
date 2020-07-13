// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Math/Math2.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include "Math/Transform.h"
#include "Object/Actor.h"
#include "Actors/Player.h"
#include"Actors/Enemy.h"
#include "core.h"
#include <iostream>
#include <vector>
#include <string>


const size_t NUM_POINTS = 40;
std::vector<nc::Vector2> points = { { 3, -3 }, { 3, 3 }, { 0, 3 }, { -3, 3 }, { -3, -3 }, { -7, -3 }, { -7, -9 } , { -9, -9}, { -9, -11}
,{9, -11} , { 9, -9 }, { 7, -9 } , { 7, -3 } , { 3, -3 } };
nc::Color color{ 10, 1, 0 };
//nc::Shape ship;
//nc::Transform transform{ { 400, 300}, 2, 0 };
Player player;
nc::Actor enemy;



float speed = 300.0f;
nc::Vector2 velocity;
float thrust = 300.0f;

float frameTime;
float roundTime{ 0 };
bool gameOver{ false };

float t{ 0 };


DWORD prevTime;
DWORD  deltaTime;


bool Update(float dt)// dt = (1 / 60) = 0.01667 | (1 / 90) = 0.0111
{

	frameTime = dt;
	roundTime += dt;
	//if (roundTime >= 5) gameOver = true;

	t = t + (dt * 5);
	if (gameOver) dt = 0;

	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	//player
	player.Update(dt);

	//ENEMY
	nc::Vector2 direction = player.GetTransform().position - enemy.GetTransform().position;
	direction.Normilize();
	nc::Vector2 enemyVelocity = direction * 100.0f;
	enemy.GetTransform().position = enemy.GetTransform().position + (enemyVelocity * dt);
	//point towards player
	enemy.GetTransform().angle = std::atan2(direction.y, direction.x) + nc::DegreesToRadians(90.0f);

 	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 8, 8, 1 });
	graphics.DrawString(10, 10, std::to_string(frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frameTime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime / 1000.0f).c_str());

	float  v = (std::sin(t) + 1.0f) * 0.5f; // (-1 <-> 1) -> (0 - 2)

	nc::Color c = nc::Lerp(nc::Color{ 1, 0, 0 }, nc::Color{ 0, 1, 1 }, v);
	graphics.SetColor(t);
	nc::Vector2 p = nc::Lerp(nc::Vector2{ 200, 200 }, nc::Vector2{ 600, 200 }, v);
	graphics.DrawString(p.x, p.y, "Last Starfighter");

	if (gameOver) graphics.DrawString(400, 300, "Game Over!");

	graphics.SetColor(color); // [R] 1 byte (8-bits) | [G] 1 byte (8-bits) | [B] 1 byte {8-bits)
	player.Draw(graphics);
	enemy.Draw(graphics);
	// [R] 0.0 - 1.0 
//	graphics.DrawLine(nc::random(0.0f, 800.0f), nc::random(0.0f, 600.0f), static_cast<float>(rand() % 600),
	//	static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));
}
/*
	for (size_t i = 0; i < points.size() - 1; i++)
	{
		// local/object space points
		nc::Vector2 p1 = points[i];
		nc::Vector2 p2 = points[i + 1];

		//transform
		// scale
		p1 = p1 * scale;
		p2 = p2 * scale;
		//rotate
		p1 = nc::Vector2::Rotate(p1, angle);
		p2 = nc::Vector2::Rotate(p2, angle);
		//translate
		p1 = p1 + position;
		p2 = p2 + position;


		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}

	*/
int main()
{
	//float r = nc::PI * 4;

	//for (size_t i = 0; i < NUM_POINTS; i++)
	//{
	//	points.push_back({ nc::random(0.0f, 800.0f), nc::random(0.0f, 600.0f) });
	//}

	DWORD time = GetTickCount();
	std::cout << time/ 1000 / 60 / 60 / 24 << std::endl;

//	ship.Load("ship.txt");
	player.Load("Player.txt");
	enemy.Load("Enemy.txt");

	//ship.SetColor(nc::Color{1,1,1});

	char name[] = "CSC196";
	Core::Init(name, 800, 600, 60);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
