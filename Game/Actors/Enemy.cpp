#include "Enemy.h"
#include "Math/Math2.h"
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

void Enemy::Update(float dt)
{
}
