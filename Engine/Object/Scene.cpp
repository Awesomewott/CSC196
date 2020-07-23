#include "pch.h"
#include "Scene.h"
#include "Actor.h"

void nc::Scene::Startup()
{
}

void nc::Scene::Shutdown()
{
	// iterate through the actors and call delete on each actor
		// this will free up the memory for each actor
	for (nc::Actor* actor : m_actors)
	{
		delete actor;
	}
	// clear m_actors list
	m_actors.clear();
}

void nc::Scene::Update(float dt)
{
	//check for collision
	std::vector<Actor*> actors{ m_actors.begin(), m_actors.end() };
	for (size_t i = 0; i < actors.size(); i++)
	{
		for (size_t j = i + 1; j < actors.size(); j++)
		{
			float distance = nc::Vector2::Distance(actors[i]->GetTransform().position, actors[j]->GetTransform().position);
			if (distance <= (actors[i]->GetRadius() + actors[j]->GetRadius()))
			{
				actors[i]->OnCollision(actors[j]);
				actors[j]->OnCollision(actors[i]);
			}
		}
	}
	
	// remove destroyed actors
	auto iter = m_actors.begin();
	while (iter != m_actors.end())
	{
		if ((*iter)->IsDestroyed())
		{
			delete (*iter);
			iter =m_actors.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	for (nc::Actor* a : m_actors)
	{
		a->Update(dt);
	}
}

void nc::Scene::Draw(Core::Graphics& graphics)
{
	for (nc::Actor* a : m_actors)
	{
		a->Draw(graphics);
	}
}

void nc::Scene::AddActor(Actor* actor)
{
	actor->SetScene(this);
	m_actors.push_back(actor);

}


void nc::Scene::RemoveActor(Actor* actor)
{
	auto iter = std::find(m_actors.begin(), m_actors.end(), actor);
	if (iter != m_actors.end())
	{
		delete* iter;
		m_actors.erase(iter);
	}
}
