#pragma once
#include "Object/Actor.h"

class Player : public nc::Actor
{
public:
	Player() {}

	virtual bool Load(const std::string& filename);
	virtual void Update(float dt);

protected:
	float m_thrust{ 200.0f };
	nc::Vector2 m_velocity;
};