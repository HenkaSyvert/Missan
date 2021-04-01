#pragma once

namespace Missan {

	// Some useful math functions and constants. 
	namespace Math {

		extern const float pi;

		///
		/// Smallest number that can be represented. 
		extern const float epsilon;

		///
		/// Euler's number. 
		extern const float e;

		///
		/// Constant for converting degrees to radians. 
		extern const float deg2Rad;

		///
		/// Constant for converting radians to degrees. 
		extern const float rad2Deg;

		extern const float positiveInfinity;
		extern const float negativeInfinity;

		///
		/// The arcus cosine in range [0, pi] of x radians. 
		float Acos(float x);

		/// 
		/// The arcus sine in range [-pi/2, pi/2] of x radians. 
		float Asin(float x);

		/// 
		/// The arcus tangent in range [-pi/2, pi/2] of x radians. 
		float Atan(float x);

		/// 
		/// The 2 argument arcus tangent in range [0, 2pi] of point (x, y). 
		float Atan2(float y, float x);

		/// 
		/// The cosine of x radians. 
		float Cos(float x);

		/// 
		/// The sine of x radians. 
		float Sin(float x);

		/// 
		/// The tangent of x radians. 
		float Tan(float x);



		/// 
		/// The absolute value of x. 
		float Abs(float x);

		/// 
		/// The sign of x. 
		float Sign(float x);

		/// 
		/// Returns the smallest value of a and b. 
		float Min(float a, float b);

		/// 
		/// Returns the largest value of a and b. 
		float Max(float a, float b);

		
		/// 
		/// Returns the largest integer smaller than x. 
		float Floor(float x);

		/// 
		/// Rounds x to the nearest integer. 
		float Round(float x);

		/// 
		/// Returns the smallest integer larger than x. 
		float Ceil(float x);		

		/// 
		/// Returns x clamped to between min and max. 
		float Clamp(float x, float min, float max);


		/// 
		/// The logarithm of x in given base. 
		float Log(float x, float base);

		/// 
		/// The natural logarithm of x. 
		float Ln(float x);

		/// 
		/// The binary logarithm of x. 
		float Log2(float x);

		/// 
		/// The decimal logarithm of x. 
		float Log10(float x);


		/// 
		/// e (euler's number) raised to the x. 
		float Exp(float x);

		/// 
		/// Returns base raised to the exponent. 
		float Pow(float base, float exponent);

		/// 
		/// The square root of x. 
		float Sqrt(float x);


	}
}