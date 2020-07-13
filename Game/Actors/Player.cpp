#include "Player.h"
#include "Math/Math2.h"
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
			stream >> m_transform;

			std::string shapename;
			stream >> shapename;
			m_shape.Load(shapename);
			stream.close();

			success = true;
		}
		return success;
	}
}

void Player::Update(float dt)
{
	nc::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * m_thrust; }
	force = nc::Vector2::Rotate(force, m_transform.angle);

	//force = force + nc::Vector2{ 0, 100 };
	//gravity
	//nc::Vector2 direction = nc::Vector2{ 400, 300 } -player.GetTransform().position;
	//if (direction.Length() <= 200.0f)
	//{
	//	float strength = 1.0f - (direction.Length() / 200.0f); // (0 - 200) -> (0 - 1) -> (1 - 0)
	//	direction.Normilize();
	//	force = force + (direction * 300.0f * strength);
	//}

	//direction.Normilize();
	//force = force + (direction * 200.0f);

	//nc::Vector2 direction = force * dt;

	m_velocity = m_velocity + (force * dt);
	m_velocity = m_velocity * 0.98f;
	m_transform.position = m_transform.position + (m_velocity * dt);
	

	

	//player.GetTransform().position = nc::Clamp(player.GetTransform().position, nc::Vector2{ 0, 0 }, nc::Vector2{ 800, 600 });

	//player.GetTransform().position.x = nc::Clamp<float>(player.GetTransform().position.x, 0.0f, 800.0f);
	//player.GetTransform().position.y = nc::Clamp<float>(player.GetTransform().position.y, 0.0f, 600.0f);


	if (m_transform.position.x > 800) m_transform.position.x = 0;
	if (m_transform.position.x < 0)m_transform.position.x = 800;
	if (m_transform.position.y > 600) m_transform.position.y = 0;
	if (m_transform.position.y < 0) m_transform.position.y = 600;

	//	if (direction.Length() < 150.0f)
		//{
		//	position = position + (-direction * speed);
		//}
		//position = nc::Vector2{ x, y };

		//for (nc::Vector2& point : points)
		//{
		//	point = nc::Vector2{ nc::random(-10.0f, 10.0f), nc::random(-10.0f, 10.0f) };
		//}
		/*
		for (size_t i = 0; i < NUM_POINTS; i++)
		{
			points[i] = nc::Vector2{ nc::random(-10.0f, 10.0f), nc::random(-10.0f, 10.0f) };
		}

		*/
		//if (Core::Input::IsPressed('A')) position += nc::Vector2::left * (speed * dt);
		//if (Core::Input::IsPressed('D')) position += nc::Vector2::right * (speed * dt);
		//if (Core::Input::IsPressed('W')) position += nc::Vector2{ 0.0f, -1.0f } * speed;
		//if (Core::Input::IsPressed('S')) position += nc::Vector2{ 0.0f, 1.0f } * speed;


	if (Core::Input::IsPressed('A')) m_transform.angle -= dt * nc::DegreesToRadians(360.0f);
	if (Core::Input::IsPressed('D')) m_transform.angle += dt * nc::DegreesToRadians(360.0f);
}


