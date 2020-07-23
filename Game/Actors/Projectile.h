#pragma once
#include "Object/Actor.h"

class Projectile : public nc::Actor
{
public:
	Projectile() {}

	virtual eType GetType() override { return eType::PROJECTILE; }

	virtual void OnCollision(Actor* actor)  override;

	virtual bool Load(const std::string& filename);
	virtual void Update(float dt);
	//void SetTarget(Actor* actor) { m_target = actor; }
	void SetSpeed(float speed) { m_speed = speed; }

protected:
	float m_speed{ 300.0f };
	float m_lifetime{ 1 };
	//Actor* m_target{ nullptr };
};