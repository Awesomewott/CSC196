#include "Enemy.h"
#include "Math/Math2.h"
#include "Graphics/ParticalSystem.h"
#include <fstream>

bool Enemy::Load(const std::string& filename)
{
	{
		bool success = false;

		// open stream
		std::ifstream stream(filename);
		// check if stream is open
		if (stream.is_open())
		{
			// set success to true
			// stream >> into transform
			success = true;
			Actor::Load(stream);
			std::string line;
			std::getline(stream, line);
			m_speed = stof(line);
			
			stream.close();

		}
		return success;
	}
}

void Enemy::Update(float dt)
{
	//nc::Vector2 direction = m_transform.position - m_transform.position;
	nc::Vector2 direction = m_target->GetTransform().position - m_transform.position;
	direction.Normilize();
	nc::Vector2 velocity = direction * m_speed;
	//m_transform.position = m_transform.position + (velocity * dt);
	//point towards player
	m_transform.angle = std::atan2(direction.y, direction.x) + nc::DegreesToRadians(-90.0f);

	m_transform.update();
}

void Enemy::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::PROJECTILE) //actor->GetType() == eType::PLAYER)
	{
		m_destroy = true;

		nc::Color colors[]{ {1,1,1}, nc::Color::red, {1,1,0}, {0,1,1} };
		nc::Color color = colors[rand() % 4];
		g_particleSystem.Create( m_transform.position, 0, 180, 30, 1, color, 100, 200);
	}
}
