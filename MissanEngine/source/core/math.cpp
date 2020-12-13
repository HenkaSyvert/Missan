#include "core/math.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <cfloat>

using namespace Missan;

const float Math::pi =(float)M_PI;
const float Math::epsilon = FLT_EPSILON;
const float Math::e = (float)M_E;
const float Math::deg2Rad = Math::pi / 180.0f;
const float Math::rad2Deg = 180.0f / Math::pi;
const float Math::positiveInfinity = INFINITY;
const float Math::negativeInfinity = -INFINITY;


float Math::Acos(float x) { return acosf(x); }
float Math::Asin(float x) { return asinf(x); }
float Math::Atan(float x) { return atanf(x); }
float Math::Atan2(float y, float x) { return atan2f(y, x); }

float Math::Cos(float x) { return cosf(x); }
float Math::Sin(float x) { return sinf(x); }
float Math::Tan(float x) { return tanf(x); }

float Math::Abs(float x) { return abs(x); }
float Math::Sign(float x) { return x < 0 ? -1.0f : 1.0f; }
float Math::Min(float a, float b) { return a < b ? a : b; }
float Math::Max(float a, float b) { return a > b ? a : b; }

float Math::Floor(float x) { return floorf(x); }
float Math::Round(float x) { return roundf(x); }
float Math::Ceil(float x) { return ceilf(x); }
float Math::Clamp(float x, float min, float max) { return x < min ? min : x > max ? max : x; }

float Math::Log(float x, float base) { return logf(x) / logf(base); }
float Math::Ln(float x) { return logf(x); }
float Math::Log2(float x) { return log2(x); }
float Math::Log10(float x) { return log10f(x); }

float Math::Exp(float x) { return expf(x); }
float Math::Pow(float base, float exponent) { return powf(base, exponent); }
float Math::Sqrt(float x) { return sqrtf(x); }
