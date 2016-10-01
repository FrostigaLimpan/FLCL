#pragma once

#include <Types.h>
#include <Math/Vector2.h>

#include <iostream>

namespace FLCL {
	namespace Math {

		// Forward declaration, should probably be moved to a common file.
		template <typename> struct Vec3;

		// Basetemplate for a vector 3. Contains the datastructure and the common operators that dosent need to be overloaded
		// by specialization. This template cannot be instanciated outside the vec2 class, since we have a private constructor
		// on it.
		// This should be refactored to a common baseclass for all vectors later on. Note about the hadamard
		// representation in that case since its internal counter is based on the vector size now.
		template <typename T>
		struct Basevector3 {

			// Friend with the Vec3 specialization so its possible to return a correct type from common
			// operators and to be able to instance through the private constructor.
			template<typename> friend struct Vec3;

		private:

			explicit Basevector3<T>(T xyz) : x{ xyz }, y{ xyz }, z{ xyz } {};
			Basevector3<T>(T inX, T inY, T inZ) : x{ inX }, y{ inY }, z{ inZ } {};
			Basevector3<T>(const Basevector3<T>& other) = default;

		public:
			// Internal datastructure and it's union so the variables can be easily accessed though name
			union {
				T values[3];
				struct {
					T x, y, z;
				};
				struct {
					T r, g, b;
				};
				struct {
					T s, t, p;
				};

			};

			// Common operator overloads
			T& operator[](USize index) { return values[index]; };
			const T& operator[](USize index) const { return values[index]; };

			Bool8 operator==(const Vec3<T> other) const {
				for (USize iCount = 0; iCount < 3; iCount++)
					if (values[iCount] != other.values[iCount])
						return false;
				return true;
			};

			Bool8 operator!=(const Vec3<T> other) const {
				return !operator==(other);
			};

			Vec3<T> operator+(const Vec3<T>& other) const {
				return Vec3<T>{x + other.x, y + other.y, z + other.z};
			};

			Vec3<T> operator-(const Vec3<T>& other) const {
				return Vec3<T>{x - other.x, y - other.y, z - other.z};
			};

			// Hadamard product representation
			Vec3<T> operator*(const Vec3<T>& other) const {
				Vec3<T> result;
				for (USize iCount = 0; iCount < 3; iCount++)
					result[iCount] = values[iCount] * other.values[iCount];
				return result;
			}

			Vec3<T>& operator+=(const Vec3<T>& other) {
				x += other.x;
				y += other.y;
				z += other.z;
				return *this;
			};

			Vec3<T>& operator-=(const Vec3<T>& other) {
				x -= other.x;
				y -= other.y;
				z -= other.z;
				return *this;
			};

			Vec3<T> operator*(T scalar) const {
				return Vec3<T>{scalar * x, scalar * y, scalar * z};
			};

			Vec3<T> operator/(T scalar) const {
				return Vec3<T>{x / scalar, y / scalar, z / scalar};
			};

			Vec3<T>& operator*=(T scalar) {
				x *= scalar;
				y *= scalar;
				z *= scalar;
				return *this;
			};

			Vec3<T>& operator/=(T scalar) {
				x /= scalar;
				y /= scalar;
				z /= scalar;
				return *this;
			};

		};

		// Template specialization for Float32 type. 
		template <>
		struct Vec3<Float32> : public Basevector3<Float32> {
			Vec3() :Basevector3(0.f, 0.f, 0.f) {}
			explicit Vec3(Float32 xyz) :Basevector3<Float32>(xyz) {};
			Vec3(Float32 x, Float32 y, Float32 z) :Basevector3(x, y, z) {};
			Vec3(Float32 xyz[]) :Basevector3(xyz[0], xyz[1], xyz[2]) {};
			Vec3(const Vec3<Float32>& other) = default;
			explicit Vec3(const Vec2<Float32>& xy, Float32 z) :Basevector3(xy.x, xy.y, z) {};

		};

		// Template specialization for Float64 type. 
		template <>
		struct Vec3<Float64> : public Basevector3<Float64> {
			Vec3() :Basevector3(0.f, 0.f, 0.f) {}
			explicit Vec3(Float64 xyz) :Basevector3<Float64>(xyz) {};
			Vec3(Float64 x, Float64 y, Float64 z) :Basevector3(x, y, z) {};
			Vec3(Float64 xyz[]) :Basevector3(xyz[0], xyz[1], xyz[2]) {};
			Vec3(const Vec3<Float64>& other) = default;
			explicit Vec3(const Vec2<Float64>& xy, Float64 z) :Basevector3(xy.x, xy.y, z) {};
		};

		// Template specialization for Int8 type. 
		template <>
		struct Vec3<Int8> : public Basevector3<Int8> {
			Vec3() :Basevector3(0, 0, 0) {}
			explicit Vec3(Int8 xyz) :Basevector3<Int8>(xyz) {};
			Vec3(Int8 x, Int8 y, Int8 z) :Basevector3(x, y, z) {};
			Vec3(Int8 xyz[]) :Basevector3(xyz[0], xyz[1], xyz[2]) {};
			Vec3(const Vec3<Int8>& other) = default;
			explicit Vec3(const Vec2<Int8>& xy, Int8 z) :Basevector3(xy.x, xy.y, z) {};
		};

		// Template specialization for Int16 type. 
		template <>
		struct Vec3<Int16> : public Basevector3<Int16> {
			Vec3() :Basevector3(0, 0, 0) {}
			explicit Vec3(Int16 xyz) :Basevector3<Int16>(xyz) {};
			Vec3(Int16 x, Int16 y, Int16 z) :Basevector3(x, y, z) {};
			Vec3(Int16 xyz[]) :Basevector3(xyz[0], xyz[1], xyz[2]) {};
			Vec3(const Vec3<Int16>& other) = default;
			explicit Vec3(const Vec2<Int16>& xy, Int16 z) :Basevector3(xy.x, xy.y, z) {};
		};

		// Template specialization for Int32 type. 
		template <>
		struct Vec3<Int32> : public Basevector3<Int32> {
			Vec3() :Basevector3(0, 0, 0) {}
			explicit Vec3(Int32 xyz) :Basevector3<Int32>(xyz) {};
			Vec3(Int32 x, Int32 y, Int32 z) :Basevector3(x, y, z) {};
			Vec3(Int32 xyz[]) :Basevector3(xyz[0], xyz[1], xyz[2]) {};
			Vec3(const Vec3<Int32>& other) = default;
			explicit Vec3(const Vec2<Int32>& xy, Int32 z) :Basevector3(xy.x, xy.y, z) {};
		};

		// Template specialization for Int64 type. 
		template <>
		struct Vec3<Int64> : public Basevector3<Int64> {
			Vec3() :Basevector3(0, 0, 0) {}
			explicit Vec3(Int64 xyz) :Basevector3<Int64>(xyz) {};
			Vec3(Int64 x, Int64 y, Int64 z) :Basevector3(x, y, z) {};
			Vec3(Int64 xyz[]) :Basevector3(xyz[0], xyz[1], xyz[2]) {};
			Vec3(const Vec3<Int64>& other) = default;
			explicit Vec3(const Vec2<Int64>& xy, Int64 z) :Basevector3(xy.x, xy.y, z) {};
		};

		/*
		* Outside functions and operators that is common
		*/
		template<typename T>
		inline T dot(const Vec3<T>& first, const Vec3<T> second) {
			return first.x * second.x + first.y * second.y + first.z * second.z;
		};

		template<typename T>
		inline Vec3<T> cross(const Vec3<T>& first, const Vec3<T> second) {
			return Vec3<T>(first.y * second.z - second.y * first.z,	// x
				first.z * second.x - second.z * first.x,	// y
				first.x * second.y - second.x * first.y);	// z
		};

		template<typename T>
		inline Vec3<T> operator*(T scalar, const Vec3<T>& vector) {
			return vector * scalar;
		};

		// We might want a specialization that always uses Float32 as a scalar even on
		// non-Float32 vectors. Not decided on this yet.
		// TODO: Decide on this
		/*template<typename T>
		inline Vec3<T> operator*(Float32 scalar, const Vec3<T>& vector) {
		return vector * scalar;
		};*/

		template<typename T>
		inline Vec3<T> norm(const Vec3<T>& a) {
			return a * (1.0f / length(a));
		}

		template<typename T>
		inline T lengthSquared(const Vec3<T>& a) {
			return dot(a, a);
		};

		template<typename T>
		inline T length(const Vec3<T>& a) {
			//return std::sqrtf(dot(a, a));
			return std::sqrtf(lengthSquared(a));
		};

		template<typename T>
		inline std::ostream& operator<<(std::ostream& outStream, const Vec3<T>& vec) {
			return outStream << "Vec3<" << typeid(T).name() << ">(" << vec[0] << ":" << vec[1] << ":" << vec[2] << ")";
		};

	} //namespace Math
} // namespace FLCL

