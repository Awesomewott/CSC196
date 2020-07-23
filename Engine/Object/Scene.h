#pragma once
#include <vector>
#include <core.h>
#include <list>
namespace nc
{
	class Scene
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		void AddActor(class Actor* actor);
		void RemoveActor(class Actor* object);

		template <typename T>
		T* GetActor() 
		{
			{

				T* actor{ nullptr };



				for (nc::Actor* a : m_actors)

				{

					actor = dynamic_cast<T*>(a);

					if (actor) break;

				}

				return actor;

			}
		}

		

		template <typename T>
		std::vector<T*> GetActors()
		{
			{

				T* actor{ nullptr };



				for (nc::Actor* a : m_actors)

				{

					actor = dynamic_cast<T*>(a);

					if (actor) break;

				}

				return actor;

			}
		}

	private:
		std::list<nc::Actor*> m_actors;
	};
}
