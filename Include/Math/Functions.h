#pragma once

#include <Types.h>
#include <Math/Math.h>

namespace FLCL {
	namespace Math {

		Float32 DegreesToRadians(Float32 radians) {
			return radians * (180 / pi);
		};

		Float32 RadiansToDegrees(Float32 degrees) {
			return degrees * (pi / 180);
		};

		Float32 Lerp(Float32 v0, Float32 v1, Float32 time) {
			return (1.0f - time) * v0 + time*v1;
		}

		Float32 Clamp(Float32 value, Float32 min, Float32 max) {
			Float32 res = value;

			if (res < min)
				res = min;
			else if (res > max)
				res = max;

			return res;
		};

		template<typename T>
		T Min(T lh, T rh) {
			return ((lh) > (rh) ? (rh) : (lh));
		};

		template<typename T>
		T Max(T lh, T rh) {
			return ((lh) < (rh) ? (rh) : (lh));
		};

		template<typename T>
		T Abs(T val) {
			return ((val) < 0 ? -(val) : (val));
		};

		template<typename T>
		T Mod(T val, T mod) {
			return (((val) % (mod)) >= 0 ? ((val) % (mod)) : (((val) % (mod)) + (mod)));
		};

		template<typename T>
		T Square(T val) {
			return (val * val);
		};

	} // namespace Math
} // namespace FLCL