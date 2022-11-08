#pragma once

#include "component.hpp"
#include "boundingbox.hpp"
#include "transform.hpp"

#include <vector>

namespace Missan {

	/// 
	/// Class that detects collisions against other Colliders
	class Collider : public Component<Collider> {

	public:

		Transform* transform;

		// this is probably very inefficient
		std::vector<Collider*> overlappingColliders;

		/// 
		/// The amount of overlap between this Collider and other. 0 means no overlap
		glm::vec3 OverlapsWith(Collider* other);

		/// 
		/// The bounding box used to calculate overlap. Note that it takes the attached Transform into account.
		/// By default the boundingBox will grow to encapsulate the attached Mesh (if any)
		BoundingBox boundingBox;


		void Start();

	};

}