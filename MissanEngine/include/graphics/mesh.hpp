#pragma once

#include "ecs/object.hpp"

#include <string>

namespace Missan {

	/// 
	/// Stores data about 3D model
	class Mesh : public Object {

	public:
		size_t vaoId;

		// vertices.size() * 3
		size_t elementCount;

		/// 
		/// Creates new Mesh
		static void Load(const std::string& fileName);

	};

}