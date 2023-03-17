#pragma once
#include <glm/vec3.hpp>

#include <vector>

namespace Missan {

	///
	/// Describes a point of contact where a collision occurs. 
	/// This information is sent along inside a Collision when the
	/// OnCollisionEnter/Stay/Exit events occur, and 
	/// is in the same perspective as the collision. 
	/// The other GameObject involved in the collision will get a 
	/// mirrored set of contact points from its perspective. 
	class ContactPoint {

	public:

		///
		/// The point of contact. This is the point on the surface of
		/// our GameObject which first collided with the other GameObject. 
		/// Note that two objects colliding will thus likely have two different points
		/// of contact, since this is measured while they are still overlapping, and 
		/// their surfaces probably do not align exactly.  
		glm::vec3 point;

		///
		/// The normal of the point of contact. 
		glm::vec3 normal;		

		///
		/// The separation (or penetration, as is the case when a collision has happened) 
		/// between the two GameObjects. 
		float separation;

	};

	///
	/// Describes a collision from the perspective of one of the GameObjects
	/// involved in the collision. Collision information is passed to 
	/// OnCollisionEnter/Stay/Exit. The other GameObject recieves a mirrored
	/// instance of this collision from the other perspective. 
	class Collision {

	public:

		///
		/// The GameObject we collided with. 
		class GameObject* gameObject = nullptr;

		///
		/// The Transform of the GameObject we collided with. 
		class Transform* transform = nullptr;

		///
		/// The Collider of the GameObject that we collided with. 
		class Collider* collider = nullptr;

		///
		/// The RigidBody of the GameObject that we collided with. 
		class RigidBody* rigidBody = nullptr;



		///
		/// The relative linear velocity of the two colliding GameObjects,  
		/// i.e. the velocity as if one of the objects was a stationary
		/// observer. 
		glm::vec3 relativeVelocity;

		///
		/// The total impulse applied by the physics engine to resolve this
		/// collision. This is the sum of the impulses applied by each contact point, 
		/// as per the penetration, momentum and contact normal. The total force applied
		/// can be obtained by dividing by Time::deltaTime. 
		glm::vec3 impulse;
		
		///
		/// The points of contact of this collision. For two spheres, this is always
		/// a single point. 
		std::vector<ContactPoint> contactPoints;

	};

}