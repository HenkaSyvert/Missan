#pragma once

#include "core/component.hpp"
#include "physics/boundingbox.hpp"
#include "graphics/mesh.hpp"

namespace Missan {

	/// 
	/// Class that detects collisions against other Colliders
	class Collider : public Component {

	public:

		/// 
		/// The amount of overlap between this Collider and other. 0 means no overlap
		glm::vec3 OverlapsWith(Collider* other);

		/// 
		/// The bounding box used to calculate overlap. Note that it takes the attached Transform into account.
		/// By default the boundingBox will grow to encapsulate the attached Mesh (if any)
		BoundingBox boundingBox;


		// NOT PART OF PUBLIC API ////////////////////////
		void Start();

		Collider* Clone() const { return new Collider(*this); }

	};

}