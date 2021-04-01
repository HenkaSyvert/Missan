#pragma once

#include <string>
#include <ostream>

namespace Missan {

	// Represents 3D vectors and points. 
	class Vector3 {

	public:
		float x = 0;
		float y = 0;
		float z = 0;

		Vector3(float x = 0, float y = 0, float z = 0);

		static const Vector3 right;
		static const Vector3 left;
		static const Vector3 up;
		static const Vector3 down;
		static const Vector3 backward;
		static const Vector3 forward;
		static const Vector3 zero;
		static const Vector3 one;
		static const Vector3 negativeInfinity;
		static const Vector3 positiveInfinity;

		Vector3 operator+(Vector3 v);
		Vector3 operator-(Vector3 v);
		Vector3 operator-();
		
		bool operator==(Vector3 v);
		bool operator!=(Vector3 v);

		Vector3 operator*(float scalar);
		friend Vector3 operator*(float scalar, Vector3 v);
		Vector3 operator/(float s);

		float& operator[](unsigned int index);		
		friend std::ostream& operator<<(std::ostream& out, Vector3 v);
		
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

		// The dot product (also known as the scalar product) between a and b. 
		static float Dot(Vector3 a, Vector3 b);

		// Vector3 Lerp(Vector3 a, Vector3 b, float t = [0,1]);
		// Vector3 Slerp(Vector3 a, Vector3 b, float t = [0,1]);
		
		// Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta);
		// Vector3 RotateTowards(Vector3 current, Vector3 target, float maxRadiansDelta, float maxMagnitudeDelta);

		// Vector3 ProjectOnPlane(Vector3 v, Vector3 n);
		// float SignedAngle(Vector3 from, Vector3 to, Vector3 axis);
		

	};

	std::ostream& operator<<(std::ostream& out, Vector3 v);
	Vector3 operator*(float scalar, Vector3 v);
}