#pragma once
#include "Object/Actor.h"

class Enemy : public nc::Actor
{
public:
	Enemy() {}

	virtual bool Load(const std::string& filename);
	virtual void Update(float dt);

protected:
	float m_speed{ 200.0f };
};