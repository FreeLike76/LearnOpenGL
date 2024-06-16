#ifndef VERTEX_STRUCTURE_H
#define VERTEX_STRUCTURE_H

#include <glm/glm.hpp>

namespace Entities
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;
		glm::vec2 texUV;
	};
}

#endif // VERTEX_STRUCTURE_H
