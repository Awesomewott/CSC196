#include "Player.h"
#include "Math/Math2.h"
#include "Projectile.h"
#include "Object/Scene.h"
#include "Graphics/ParticalSystem.h"
#include <fstream>

bool Player::Load(const std::string& filename)
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
			m_thrust = stof(line);
			std::getline(stream, line);
			m_rotationRate = stof(line);
			stream.close();

		}
		return success;
	}
}

void Player::Update(float dt)
{
	m_firetimer += dt;
	if (Core::Input::IsPressed(VK_SPACE) && m_firetimer >= m_firerate)
	{
		m_firetimer = 0;

		Projectile* projectile = new Projectile;
		projectile->Load("projectile.txt");
		projectile->GetTransform().position = m_transform.position;
		projectile->GetTransform().angle = m_transform.angle;
		m_scene->AddActor(projectile);

	}
	//get force
	nc::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * m_thrust; }
	force = nc::Vector2::Rotate(force, m_transform.angle);

	

	m_velocity = m_velocity + (force * dt);
	m_velocity = m_velocity * 0.98f;
	m_transform.position = m_transform.position + (m_velocity * dt);


	if (m_transform.position.x > 800) m_transform.position.x = 0;
	if (m_transform.position.x < 0)m_transform.position.x = 800;
	if (m_transform.position.y > 600) m_transform.position.y = 0;
	if (m_transform.position.y < 0) m_transform.position.y = 600;

	

	if (Core::Input::IsPressed('A')) m_transform.angle -= dt * nc::DegreesToRadians(360.0f);
	if (Core::Input::IsPressed('D')) m_transform.angle += dt * nc::DegreesToRadians(360.0f);


	if (force.LengthSqr() > 0)
	{
		g_particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 25, 1, 1, nc::Color{ 1,1,0 }, 100, 200);
	}


	m_transform.update();
}


