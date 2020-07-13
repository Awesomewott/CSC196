#include "pch.h"
#include "Actor.h"
//#include <iostream>
#include <fstream>

namespace nc
{
	bool nc::Actor::Load(const std::string& filename)
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



	void nc::Actor::Update(float dt)
	{
		//Nothing
	}

	void nc::Actor::Draw(Core::Graphics& graphics)
	{
		// draw shape using transform
		m_shape.Draw(graphics, m_transform);
	}
}
