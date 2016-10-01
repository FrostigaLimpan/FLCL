#pragma once

#include <Types.h>
#include <Math/Math.h>
#include <Math/Vector3.h>

#include <iostream>

namespace FLCL {
	namespace Math {

		// Forward declaration, should probably be moved to a common file.
		template <typename> struct Vec4;

		// Basetemplate for a vector 3. Contains the datastructure and the common operators that dosent need to be overloaded
		// by specialization. This template cannot be instanciated outside the vec2 class, since we have a private constructor
		// on it.
		// This should be refactored to a common baseclass for all vectors later on. Note about the hadamard
		// representation in that case since its internal counter is based on the vector size now.
		template <typename T>
		struct Basevector4 {

			// Friend with the Vec4 specialization so its possible to return a correct type from common
			// operators and to be able to instance through the private constructor.
			template<typename> friend struct Vec4;

		private:

			explicit Basevector4<T>(T xyzw) : x{ xyzw }, y{ xyzw }, z{ xyzw }, w{ xyzw } {};
			Basevector4<T>(T inX, T inY, T inZ, T inW) : x{ inX }, y{ inY }, z{ inZ }, w{ inW } {};
			Basevector4<T>(const Basevector4<T>& other) = default;

		public:
			// Internal datastructure and it's union so the variables can be easily accessed though name
			union {
				T values[4];
				struct {
					T x, y, z, w;
				};
				struct {
					T r, g, b, a;
				};
				struct {
					T s, t, p, q;
				};

			};

			// Common operator overloads
			T& operator[](USize index) { return values[index]; };
			const T& operator[](USize index) const { return values[index]; };

			Bool8 operator==(const Vec4<T> other) const {
				for (USize iCount = 0; iCount < 4; iCount++)
					if (values[iCount] != other.values[iCount])
						return false;
				return true;
			};

			Bool8 operator!=(const Vec4<T> other) const {
				return !operator==(other);
			};

			Vec4<T> operator+(const Vec4<T>& other) const {
				return Vec4<T>{x + other.x, y + other.y, z + other.z, w + other.w};
			};

			Vec4<T> operator-(const Vec4<T>& other) const {
				return Vec4<T>{x - other.x, y - other.y, z - other.z, w - other.w};
			};

			// Hadamard product representation
			Vec4<T> operator*(const Vec4<T>& other) const {
				Vec4<T> result;
				for (USize iCount = 0; iCount < 4; iCount++)
					result[iCount] = values[iCount] * other.values[iCount];
				return result;
			}

			Vec4<T>& operator+=(const Vec4<T>& other) {
				x += other.x;
				y += other.y;
				z += other.z;
				w += other.w;
				return *this;
			};

			Vec4<T>& operator-=(const Vec4<T>& other) {
				x -= other.x;
				y -= other.y;
				z -= other.z;
				w -= other.w;
				return *this;
			};

			Vec4<T> operator*(T scalar) const {
				return Vec4<T>{scalar * x, scalar * y, scalar * z, scalar * w};
			};

			Vec4<T> operator/(T scalar) const {
				return Vec4<T>{x / scalar, y / scalar, z / scalar, w / scalar};
			};

			Vec4<T>& operator*=(T scalar) {
				x *= scalar;
				y *= scalar;
				z *= scalar;
				w *= scalar;
				return *this;
			};

			Vec4<T>& operator/=(T scalar) {
				x /= scalar;
				y /= scalar;
				z /= scalar;
				w /= scalar;
				return *this;
			};

		};

		// Template specialization for Float32 type. 
		template <>
		struct Vec4<Float32> : public Basevector4<Float32> {
			Vec4() :Basevector4(0.f, 0.f, 0.f, 0.f) {}
			explicit Vec4(Float32 xyzw) :Basevector4<Float32>(xyzw) {};
			Vec4(Float32 x, Float32 y, Float32 z, Float32 w) :Basevector4(x, y, z, w) {};
			Vec4(Float32 xyzw[]) :Basevector4(xyzw[0], xyzw[1], xyzw[2], xyzw[3]) {};
			Vec4(const Vec4<Float32>& other) = default;
			explicit Vec4(const Vec3<Float32>& xyz, Float32 w) :Basevector4(xyz.x, xyz.y, xyz.z, w) {};
			explicit Vec4(const Vec2<Float32>& xy, Float32 z, Float32 w) :Basevector4(xy.x, xy.y, z, w) {};
			explicit Vec4(const Vec2<Float32>& xy, const Vec2<Float32>& zw) :Basevector4(xy.x, xy.y, zw.x, zw.x) {};
		};

		// Template specialization for Float64 type. 
		template <>
		struct Vec4<Float64> : public Basevector4<Float64> {
			Vec4() :Basevector4(0.f, 0.f, 0.f, 0.f) {}
			explicit Vec4(Float64 xyzw) :Basevector4<Float64>(xyzw) {};
			Vec4(Float64 x, Float64 y, Float64 z, Float64 w) :Basevector4(x, y, z, w) {};
			Vec4(Float64 xyzw[]) :Basevector4(xyzw[0], xyzw[1], xyzw[2], xyzw[3]) {};
			Vec4(const Vec4<Float64>& other) = default;
			explicit Vec4(const Vec3<Float64>& xyz, Float64 w) :Basevector4(xyz.x, xyz.y, xyz.z, w) {};
			explicit Vec4(const Vec2<Float64>& xy, Float64 z, Float64 w) :Basevector4(xy.x, xy.y, z, w) {};
			explicit Vec4(const Vec2<Float64>& xy, const Vec2<Float64>& zw) :Basevector4(xy.x, xy.y, zw.x, zw.y) {};
		};

		// Template specialization for Int8 type. 
		template <>
		struct Vec4<Int8> : public Basevector4<Int8> {
			Vec4() :Basevector4(0, 0, 0, 0) {}
			explicit Vec4(Int8 xyzw) :Basevector4<Int8>(xyzw) {};
			Vec4(Int8 x, Int8 y, Int8 z, Int8 w) :Basevector4(x, y, z, w) {};
			Vec4(Int8 xyzw[]) :Basevector4(xyzw[0], xyzw[1], xyzw[2], xyzw[3]) {};
			Vec4(const Vec4<Int8>& other) = default;
			explicit Vec4(const Vec3<Int8>& xyz, Int8 w) :Basevector4(xyz.x, xyz.y, xyz.z, w) {};
			explicit Vec4(const Vec2<Int8>& xy, Int8 z, Int8 w) :Basevector4(xy.x, xy.y, z, w) {};
			explicit Vec4(const Vec2<Int8>& xy, const Vec2<Int8>& zw) :Basevector4(xy.x, xy.y, zw.x, zw.y) {};
		};

		// Template specialization for Int16 type. 
		template <>
		struct Vec4<Int16> : public Basevector4<Int16> {
			Vec4() :Basevector4(0, 0, 0, 0) {}
			explicit Vec4(Int16 xyzw) :Basevector4<Int16>(xyzw) {};
			Vec4(Int16 x, Int16 y, Int16 z, Int16 w) :Basevector4(x, y, z, w) {};
			Vec4(Int16 xyzw[]) :Basevector4(xyzw[0], xyzw[1], xyzw[2], xyzw[3]) {};
			Vec4(const Vec4<Int16>& other) = default;
			explicit Vec4(const Vec3<Int16>& xyz, Int16 w) :Basevector4(xyz.x, xyz.y, xyz.z, w) {};
			explicit Vec4(const Vec2<Int16>& xy, Int16 z, Int16 w) :Basevector4(xy.x, xy.y, z, w) {};
			explicit Vec4(const Vec2<Int16>& xy, const Vec2<Int16>& zw) :Basevector4(xy.x, xy.y, zw.x, zw.y) {};
		};

		// Template specialization for Int32 type. 
		template <>
		struct Vec4<Int32> : public Basevector4<Int32> {
			Vec4() :Basevector4(0, 0, 0, 0) {}
			explicit Vec4(Int32 xyzw) :Basevector4<Int32>(xyzw) {};
			Vec4(Int32 x, Int32 y, Int32 z, Int32 w) :Basevector4(x, y, z, w) {};
			Vec4(Int32 xyzw[]) :Basevector4(xyzw[0], xyzw[1], xyzw[2], xyzw[3]) {};
			Vec4(const Vec4<Int32>& other) = default;
			explicit Vec4(const Vec3<Int32>& xyz, Int32 w) :Basevector4(xyz.x, xyz.y, xyz.z, w) {};
			explicit Vec4(const Vec2<Int32>& xy, Int32 z, Int32 w) :Basevector4(xy.x, xy.y, z, w) {};
			explicit Vec4(const Vec2<Int32>& xy, const Vec2<Int32>& zw) :Basevector4(xy.x, xy.y, zw.x, zw.y) {};
		};

		// Template specialization for Int64 type. 
		template <>
		struct Vec4<Int64> : public Basevector4<Int64> {
			Vec4() :Basevector4(0, 0, 0, 0) {}
			explicit Vec4(Int64 xyzw) :Basevector4<Int64>(xyzw) {};
			Vec4(Int64 x, Int64 y, Int64 z, Int64 w) :Basevector4(x, y, z, w) {};
			Vec4(Int64 xyzw[]) :Basevector4(xyzw[0], xyzw[1], xyzw[2], xyzw[3]) {};
			Vec4(const Vec4<Int64>& other) = default;
			explicit Vec4(const Vec3<Int64>& xyz, Int64 w) :Basevector4(xyz.x, xyz.y, xyz.z, w) {};
			explicit Vec4(const Vec2<Int64>& xy, Int64 z, Int64 w) :Basevector4(xy.x, xy.y, z, w) {};
			explicit Vec4(const Vec2<Int64>& xy, const Vec2<Int64>& zw) :Basevector4(xy.x, xy.y, zw.x, zw.y) {};
		};

		/*
		* Outside functions and operators that is common
		*/
		template<typename T>
		inline T dot(const Vec4<T>& first, const Vec4<T> second) {
			return first.x * second.x + first.y * second.y + first.z * second.z + first.w * second.w;
		};

		template<typename T>
		inline Vec4<T> operator*(T scalar, const Vec4<T>& vector) {
			return vector * scalar;
		};

		template<typename T>
		inline Vec4<T> norm(const Vec4<T>& a) {
			return a * (1.0f / length(a));
		}

		template<typename T>
		inline T lengthSquared(const Vec4<T>& a) {
			return dot(a, a);
		};

		template<typename T>
		inline T length(const Vec4<T>& a) {
			//return std::sqrtf(dot(a, a));
			return std::sqrtf(lengthSquared(a));
		};

		template<typename T>
		inline std::ostream& operator<<(std::ostream& outStream, const Vec4<T>& vec) {
			return outStream << "Vec4<" << typeid(T).name() << ">(" << vec[0] << ":" << vec[1] << ":" << vec[2] << ":" << vec[3] << ")";
		};

	} //namespace Math
} // namespace FLCL
