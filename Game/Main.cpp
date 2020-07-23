#include "core.h"
#include "Game.h"


//const size_t NUM_POINTS = 40;
//std::vector<nc::Vector2> points = { { 3, -3 }, { 3, 3 }, { 0, 3 }, { -3, 3 }, { -3, -3 }, { -7, -3 }, { -7, -9 } , { -9, -9}, { -9, -11}
//,{9, -11} , { 9, -9 }, { 7, -9 } , { 7, -3 } , { 3, -3 } };
//nc::Color color{ 10, 1, 0 };



Game game;


bool Update(float dt)// dt = (1 / 60) = 0.01667 | (1 / 90) = 0.0111
{
	bool quit = game.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	game.Draw(graphics);
}

int main()
{
	game.Initialize();

	char name[] = "CSC196";
	Core::Init(name, 800, 600, 60);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();

	//g_particleSystem.Shutdown();
	//scene.Shutdown();
}
