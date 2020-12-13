#include "core/vector3.hpp"

#include "missanpch.hpp"
#include "core/math.hpp"


using namespace Missan; 


namespace {
	// this is just for convenient casting back and forth from glm
	inline glm::fvec3 toglm(Vector3 a) { return { a.x, a.y, a.z }; }
	inline Vector3 fromglm(glm::fvec3 a) { return { a.x, a.y, a.z }; }
}


Vector3::Vector3(float x, float y, float z) {
	this->x = x, this->y = y, this->z = z;
}

Vector3 const Vector3::right	= {  1,  0,  0 };
Vector3 const Vector3::left		= { -1,  0,  0 };
Vector3 const Vector3::up		= {  0,  1,  0 };
Vector3 const Vector3::down		= {  0, -1,  0 };
Vector3 const Vector3::backward = {  0,  0,  1 };
Vector3 const Vector3::forward	= {  0,  0, -1 };
Vector3 const Vector3::zero		= {  0,  0,  0 };
Vector3 const Vector3::one		= {  1,  1,  1 };
Vector3 const Vector3::negativeInfinity = { Math::negativeInfinity, Math::negativeInfinity, Math::negativeInfinity};
Vector3 const Vector3::positiveInfinity = { Math::positiveInfinity, Math::positiveInfinity, Math::positiveInfinity};


float& Vector3::operator[](unsigned int index) {
	return index == 0 ? x : index == 1 ? y : z;
}
std::ostream& Missan::operator<<(std::ostream& out, Vector3 v) {
	out << "[" << v.x << ", " << v.y << ", " << v.z << "]";
	return out;
}

Vector3 Vector3::operator+(Vector3 v) { return { x + v.x, y + v.y, z + v.z }; }
Vector3 Vector3::operator- () { return Vector3(*this) * -1; }
Vector3 Vector3::operator-(Vector3 v) {return { x - v.x, y - v.y, z - v.z};}

bool Vector3::operator==(Vector3 v) { return x == v.x && y == v.y && z == v.z; }
bool Vector3::operator!=(Vector3 v) { return !(*this == v); }

Vector3 Vector3::operator* (float scalar) { return { x * scalar,y * scalar,z * scalar }; }
Vector3 Missan::operator* (float scalar, Vector3 v) { return { v.x * scalar,v.y * scalar,v.z * scalar }; }
Vector3 Vector3::operator/(float scalar) { return { x / scalar,y / scalar,z / scalar }; }

Vector3 Vector3::Normalize(Vector3 v) { return fromglm(glm::normalize(toglm(v))); }
float Vector3::Magnitude(Vector3 v) { return Math::Sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }
float Vector3::Distance(Vector3 a,  Vector3 b) { return Vector3::Magnitude(a - b); }

Vector3 Vector3::Project(Vector3 v, Vector3 n) { return fromglm(glm::proj(toglm(v), toglm(n))); }
Vector3 Vector3::Reflect(Vector3 v, Vector3 n) { return fromglm(glm::reflect(toglm(v), toglm(n))); }
Vector3 Vector3::Scale(Vector3 a, Vector3 b) { return { a.x * b.x,a.y * b.y,a.z * b.z }; }


float Vector3::Angle(Vector3 a, Vector3 b) { return Math::Acos(Vector3::Dot(a,b) / (Vector3::Magnitude(a) * Vector3::Magnitude(b))); }
Vector3 Vector3::Cross(Vector3 a, Vector3 b) { return fromglm(glm::cross(toglm(a), toglm(b))); }
float Vector3::Dot(Vector3 a, Vector3 b) { return glm::dot(toglm(a), toglm(b)); }





