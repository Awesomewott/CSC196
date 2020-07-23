#pragma once
#include "Object/Actor.h"

class Player : public nc::Actor
{
public:
	Player() {}

	virtual eType GetType() { return eType::PLAYER; }


	virtual bool Load(const std::string& filename);
	virtual void Update(float dt);

protected:
	float m_thrust{ 200.0f };
	float m_rotationRate{ 0 };

	float m_firerate{0.02f};
	float m_firetimer{ 3 };
	nc::Vector2 m_velocity;
};
