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
		
		static Vector3 Normalize(Vector3 v);
		static float Magnitude(Vector3 v);
		static float Distance(Vector3 a, Vector3 b);

		static Vector3 Project(Vector3 v, Vector3 n);
		static Vector3 Reflect(Vector3 v, Vector3 n);
		static Vector3 Scale(Vector3 a, Vector3 b);

		static float Angle(Vector3 from, Vector3 to);
		static Vector3 Cross(Vector3 a, Vector3 b);
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