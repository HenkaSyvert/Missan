#pragma once

#include <string>

namespace Missan {

	///
	/// Represents 3D vectors and points. 
	class Vector3 {

	public:
		///
		/// The x component of this vector. 
		float x = 0;

		///
		/// The y component of this vector. 
		float y = 0;

		///
		/// The z component of this vector. 
		float z = 0;

		Vector3(float x = 0, float y = 0, float z = 0);

		///
		/// Shorthand for {1, 0, 0}
		static const Vector3 right;

		///
		/// Shorthand for {-1, 0, 0}
		static const Vector3 left;

		///
		/// Shorthand for {0, 1, 0}
		static const Vector3 up;

		///
		/// Shorthand for {0, -1, 0}
		static const Vector3 down;

		///
		/// Shorthand for {0, 0, 1}
		static const Vector3 backward;

		///
		/// Shorthand for {0, 0, -1}
		static const Vector3 forward;

		///
		/// Shorthand for {0, 0, 0}
		static const Vector3 zero;

		///
		/// Shorthand for {1, 1, 1}
		static const Vector3 one;

		///
		/// Shorthand for {-inf, -inf, -inf}
		static const Vector3 negativeInfinity;

		///
		/// Shorthand for {inf, inf, inf}
		static const Vector3 positiveInfinity;

		Vector3 operator+(Vector3 v);
		Vector3 operator-(Vector3 v);
		Vector3 operator-();
		//float& operator[](int index);
		
		bool operator==(Vector3 v);
		bool operator!=(Vector3 v);

		Vector3 operator*(float scalar);
		friend Vector3 operator*(float scalar, Vector3 v);
		Vector3 operator/(float s);

		
		///
		/// Normalizes v, i.e. returns a vector of length 1 with the same direction. 
		static Vector3 Normalize(Vector3 v);

		///
		/// The magnitude (or length) of v
		static float Magnitude(Vector3 v);

		///
		/// The distance between a and b. 
		static float Distance(Vector3 a, Vector3 b);

		///
		/// Projects v unto n. 
		static Vector3 Project(Vector3 v, Vector3 n);

		///
		/// Reflects vector v on the normal n. 
		static Vector3 Reflect(Vector3 v, Vector3 n);

		///
		/// Scales a elementwise by b. Same as hadamard product. 
		static Vector3 Scale(Vector3 a, Vector3 b);

		///
		/// The angle (radians) between from and to. 
		static float Angle(Vector3 from, Vector3 to);

		///
		/// The cross product between a and b. The resultant i perpendicular to both a and b. 
		static Vector3 Cross(Vector3 a, Vector3 b);

		///
		/// The dot product (also known as the scalar product) between a and b. 
		static float Dot(Vector3 a, Vector3 b);

		///
		/// Linearly interpolates by t between a and b. 
		Vector3 Lerp(Vector3 a, Vector3 b, float t);

		///
		/// Spherically interpolates by t between a and b. 
		Vector3 Slerp(Vector3 a, Vector3 b, float t);
		

		//Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta);
		//Vector3 RotateTowards(Vector3 current, Vector3 target, float maxRadiansDelta, float maxMagnitudeDelta);

		/// 
		/// Projects vector v unto the plane described by the normal n
		Vector3 ProjectOnPlane(Vector3 v, Vector3 n);

		///
		/// Returns the signed angle between from and to along axis.
		float SignedAngle(Vector3 from, Vector3 to, Vector3 axis);
		

	};

}