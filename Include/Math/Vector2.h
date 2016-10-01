#pragma once

#include <Types.h>
#include <iostream>
#include <typeinfo>

namespace FLCL {
	namespace Math {

		// Forward declaration, should probably be moved to a common file.
		template <typename> struct Vec2;

		// Basetemplate for a vector 2. Contains the datastructure and the common operators that dosent need to be overloaded
		// by specialization. This template cannot be instanciated outside the vec2 class, since we have a private constructor
		// on it.
		// This should be refactored to a common baseclass for all vectors later on. Note about the hadamard
		// representation in that case since its internal counter is based on the vector size now.
		template <typename T>
		struct Basevector2 {

			// Friend with the Vec2 specialization so its possible to return a correct type from common
			// operators and to be able to instance through the private constructor.
			template<typename> friend struct Vec2;

		private:

			explicit Basevector2<T>(T xy) : x{ xy }, y{ xy } {};
			Basevector2<T>(T inX, T inY) : x{ inX }, y{ inY } {};
			Basevector2<T>(const Basevector2<T>& other) = default;

		public:
			// Internal datastructure and it's union so the variables can be easily accessed though name
			union {
				T values[2];
				struct {
					T x, y;
				};
				struct {
					T r, g;
				};
				struct {
					T s, t;
				};
				struct {
					T width, height;
				};

			};

			// Common operator overloads
			T& operator[](USize index) { return values[index]; };
			const T& operator[](USize index) const { return values[index]; };

			Bool8 operator==(const Vec2<T> other) const {
				for (USize iCount = 0; iCount < 2; iCount++)
					if (values[iCount] != other.values[iCount])
						return false;
				return true;
			};

			Bool8 operator!=(const Vec2<T> other) const {
				return !operator==(other);
			};

			Vec2<T> operator+(const Vec2<T>& other) const {
				return Vec2<T>{x + other.x, y + other.y};
			};

			Vec2<T> operator-(const Vec2<T>& other) const {
				return Vec2<T>{x - other.x, y - other.y};
			};

			// Hadamard product representation
			Vec2<T> operator*(const Vec2<T>& other) const {
				Vec2<T> result;
				for (USize iCount = 0; iCount < 2; iCount++)
					result[iCount] = values[iCount] * other.values[iCount];
				return result;
			}

			Vec2<T>& operator+=(const Vec2<T>& other) {
				x += other.x;
				y += other.y;
				return *this;
			};

			Vec2<T>& operator-=(const Vec2<T>& other) {
				x -= other.x;
				y -= other.y;
				return *this;
			};

			Vec2<T> operator*(T scalar) const {
				return Vec2<T>{scalar * x, scalar * y};
			};

			Vec2<T> operator/(T scalar) const {
				return Vec2<T>{x / scalar, y / scalar};
			};

			Vec2<T>& operator*=(T scalar) {
				x *= scalar;
				y *= scalar;
				return *this;
			};

			Vec2<T>& operator/=(T scalar) {
				x /= scalar;
				y /= scalar;
				return *this;
			};

		};

		// Template specialization for Float32 type. 
		template <>
		struct Vec2<Float32> : public Basevector2<Float32> {
			Vec2() :Basevector2(0.f, 0.f) {}
			explicit Vec2(Float32 xy) :Basevector2<Float32>(xy) {};
			Vec2(Float32 x, Float32 y) :Basevector2(x, y) {};
			Vec2(Float32 xy[]) :Basevector2(xy[0], xy[1]) {};
			Vec2(const Vec2<Float32>& other) = default;

		};

		// Template specialization for Float64 type. 
		template <>
		struct Vec2<Float64> : public Basevector2<Float64> {
			Vec2() :Basevector2(0.f, 0.f) {}
			explicit Vec2(Float64 xy) :Basevector2<Float64>(xy) {};
			Vec2(Float64 x, Float64 y) :Basevector2(x, y) {};
			Vec2(Float64 xy[]) :Basevector2(xy[0], xy[1]) {};
			Vec2(const Vec2<Float64>& other) = default;

		};

		// Template specialization for Int8 type. 
		template <>
		struct Vec2<Int8> : public Basevector2<Int8> {
			Vec2() :Basevector2(0, 0) {}
			explicit Vec2(Int8 xy) :Basevector2<Int8>(xy) {};
			Vec2(Int8 x, Int8 y) :Basevector2(x, y) {};
			Vec2(Int8 xy[]) :Basevector2(xy[0], xy[1]) {};
			Vec2(const Vec2<Int8>& other) = default;
		};

		// Template specialization for Int16 type. 
		template <>
		struct Vec2<Int16> : public Basevector2<Int16> {
			Vec2() :Basevector2(0, 0) {}
			explicit Vec2(Int16 xy) :Basevector2<Int16>(xy) {};
			Vec2(Int16 x, Int16 y) :Basevector2(x, y) {};
			Vec2(Int16 xy[]) :Basevector2(xy[0], xy[1]) {};
			Vec2(const Vec2<Int16>& other) = default;
		};

		// Template specialization for Int32 type. 
		template <>
		struct Vec2<Int32> : public Basevector2<Int32> {
			Vec2() :Basevector2(0, 0) {}
			explicit Vec2(Int32 xy) :Basevector2<Int32>(xy) {};
			Vec2(Int32 x, Int32 y) :Basevector2(x, y) {};
			Vec2(Int32 xy[]) :Basevector2(xy[0], xy[1]) {};
			Vec2(const Vec2<Int32>& other) = default;
		};

		// Template specialization for Int64 type. 
		template <>
		struct Vec2<Int64> : public Basevector2<Int64> {
			Vec2() :Basevector2(0, 0) {}
			explicit Vec2(Int64 xy) :Basevector2<Int64>(xy) {};
			Vec2(Int64 x, Int64 y) :Basevector2(x, y) {};
			Vec2(Int64 xy[]) :Basevector2(xy[0], xy[1]) {};
			Vec2(const Vec2<Int64>& other) = default;
		};

		/*
		* Outside functions and operators that is common
		*/
		template<typename T>
		inline T dot(const Vec2<T>& first, const Vec2<T> second) {
			return first.x * second.x + first.y * second.y;
		};

		template<typename T>
		inline T cross(const Vec2<T>& first, const Vec2<T> second) {
			return first.x * second.y - second.x * first.y;
		};

		template<typename T>
		inline Vec2<T> operator*(T scalar, const Vec2<T>& vector) {
			return vector * scalar;
		};

		// We might want a specialization that always uses Float32 as a scalar even on
		// non-Float32 vectors. Not decided on this yet.
		// TODO: Decide on this
		/*template<typename T>
		inline Vec2<T> operator*(Float32 scalar, const Vec2<T>& vector) {
		return vector * scalar;
		};*/

		template<typename T>
		inline Vec2<T> norm(const Vec2<T>& a) {
			return a * (1.0f / length(a));
		}

		template<typename T>
		inline T lengthSquared(const Vec2<T>& a) {
			return dot(a, a);
		};

		template<typename T>
		inline T length(const Vec2<T>& a) {
			//return std::sqrtf(dot(a, a));
			return std::sqrtf(lengthSquared(a));
		};

		template<typename T>
		inline std::ostream& operator<<(std::ostream& outStream, const Vec2<T>& vec) {
			return outStream << "Vec2<" << typeid(T).name() << ">(" << vec[0] << ":" << vec[1] << ")";
		};

	} //namespace Math
} // namespace FLCL