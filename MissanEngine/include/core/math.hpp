#pragma once

namespace Missan {

	namespace Math {

		extern const float pi;
		extern const float epsilon;
		extern const float e;
		extern const float deg2Rad;
		extern const float rad2Deg;
		extern const float positiveInfinity;
		extern const float negativeInfinity;

		float Acos(float x);
		float Asin(float x);
		float Atan(float x);
		float Atan2(float y, float x);

		float Cos(float x);
		float Sin(float x);
		float Tan(float x);

		float Abs(float x);
		float Sign(float x);
		float Min(float a, float b);
		float Max(float a, float b);
		
		float Floor(float x);
		float Round(float x);
		float Ceil(float x);		
		float Clamp(float x, float min, float max);

		float Log(float x, float base);
		float Ln(float x);
		float Log2(float x);
		float Log10(float x);

		float Exp(float x);
		float Pow(float base, float exponent);
		float Sqrt(float x);


	}
}