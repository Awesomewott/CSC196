#include "Projectile.h"
#include "Math/Math2.h"
#include "Graphics/ParticalSystem.h"
#include "Graphics/Particles.h"
#include <fstream>

bool Projectile::Load(const std::string& filename)
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
			stream >> m_transform;

			std::string shapename;
			std::getline(stream, shapename);
			m_shape.Load(shapename);
			stream.close();

			success = true;
		}
		return success;
	}
}

void Projectile::Update(float dt)
{

	m_lifetime -= dt;
	if (m_lifetime <= 0)
	{
		m_destroy = true;
	}
	nc::Vector2 direction = nc::Vector2::Rotate(nc::Vector2::forward, m_transform.angle);


	//nc::Vector2 direction = m_transform.position - m_transform.position;
	//nc::Vector2 direction = m_target->GetTransform().position - m_transform.position;
	//direction.Normilize();
	nc::Vector2 velocity = direction * m_speed;
	m_transform.position = m_transform.position + (velocity * dt);
	g_particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 25, 1, 1, nc::Color{ 1,1,0 }, 100, 200);

	//point towards player
	//m_transform.angle = std::atan2(direction.y, direction.x) + nc::DegreesToRadians(-90.0f);

	m_transform.update();
}

void Projectile::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::ENEMY)
	{
		m_destroy = true;
	}
}
