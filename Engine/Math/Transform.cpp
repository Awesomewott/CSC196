#include "pch.h"
#include "Transform.h"
#include <fstream>
#include <string>

namespace nc
{
	std::istream& nc::operator>>(std::istream& stream, Transform& transform)
	{
		stream >> transform.position;

		std::string line;
		std::getline(stream, line);
		transform.scale = stof(line);

		

		std::getline(stream, line);
		transform.angle = stof(line);


		return stream;
	}

}
