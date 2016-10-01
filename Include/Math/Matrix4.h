#pragma once

#include <Math/Vector4.h>
#include <array>

namespace FLCL {
	namespace Math {

		class Matrix4 {

		public:
			// Works fine
			Matrix4()
				: data({ Vec4<Float32>(1, 0, 0, 0),
					Vec4<Float32>(0, 1, 0, 0),
					Vec4<Float32>(0, 0, 1, 0),
					Vec4<Float32>(0, 0, 0, 1) })
			{};

			Matrix4(Float32 scale)
				: data({ Vec4<Float32>(scale, 0, 0, 0),
					Vec4<Float32>(0, scale, 0, 0),
					Vec4<Float32>(0, 0, scale, 0),
					Vec4<Float32>(0, 0, 0, scale) })
			{};

			Matrix4(const Vec4<Float32>& vec0, const Vec4<Float32>& vec1, const Vec4<Float32>& vec2, const Vec4<Float32>& vec3)
				: data({ vec0, vec1, vec2, vec3 })
			{};

			Matrix4(const Matrix4& other) = default;

			Vec4<Float32>& operator[](USize index) { return data[index]; };
			const Vec4<Float32>& operator[](USize index) const { return data[index]; };

			Bool8 operator==(const Matrix4& other) const {
				for (USize iCount = 0; iCount < 4; iCount++)
					if (data[iCount] != other[iCount])
						return false;
				return true;

				// Not sure we need a temporary variable here.
				/*const Matrix4& mat = *this;
				for (USize iCount = 0; iCount < 4; iCount++)
				if (mat[iCount] != other[iCount])
				return false;

				return true;*/
			};

			Bool8 operator!=(const Matrix4& other) const {
				return !operator==(other);
			};

			// Matrix addition
			Matrix4 operator+(const Matrix4& other) const {
				Matrix4 resultMatrix;
				for (USize iCount = 0; iCount < 4; iCount++)
					resultMatrix[iCount] = data[iCount] + other.data[iCount];
				return resultMatrix;
			}

			// Matrix subtract
			Matrix4 operator-(const Matrix4& other) const {
				Matrix4 resultMatrix;
				for (USize iCount = 0; iCount < 4; iCount++)
					resultMatrix[iCount] = data[iCount] - other.data[iCount];
				return resultMatrix;
			}

			// Matrix multiplication
			Matrix4 operator*(const Matrix4& other) const {

				const Matrix4& thisMat = *this;

				Matrix4 result;

				result[0] = thisMat[0] * other[0][0] + thisMat[1] * other[0][1] + thisMat[2] * other[0][2] + thisMat[3] * other[0][3];
				result[1] = thisMat[0] * other[1][0] + thisMat[1] * other[1][1] + thisMat[2] * other[1][2] + thisMat[3] * other[1][3];
				result[2] = thisMat[0] * other[2][0] + thisMat[1] * other[2][1] + thisMat[2] * other[2][2] + thisMat[3] * other[2][3];
				result[3] = thisMat[0] * other[3][0] + thisMat[1] * other[3][1] + thisMat[2] * other[3][2] + thisMat[3] * other[3][3];

				return result;

			};

			// Vector multiply
			Vec4<Float32> operator*(const Vec4<Float32>& vec) const {
				const Matrix4& thisMat = *this;

				const Vec4<Float32> mul0 = thisMat[0] * vec[0];
				const Vec4<Float32> mul1 = thisMat[1] * vec[1];
				const Vec4<Float32> mul2 = thisMat[2] * vec[2];
				const Vec4<Float32> mul3 = thisMat[3] * vec[3];

				const Vec4<Float32> add0 = mul0 + mul1;
				const Vec4<Float32> add1 = mul2 + mul3;

				return add0 + add1;

			};

			// Matrix scalar multiply
			Matrix4 operator*(Float32 scalar) const {
				Matrix4 resultMatrix;
				for (USize iCount = 0; iCount < 4; iCount++)
					resultMatrix[iCount] = data[iCount] * scalar;
				return resultMatrix;
			}

			// Matrix scalar divide
			Matrix4 operator/(Float32 scalar) const {
				Matrix4 resultMatrix;
				for (USize iCount = 0; iCount < 4; iCount++)
					resultMatrix[iCount] = data[iCount] / scalar;
				return resultMatrix;
			};

			Matrix4& operator+=(const Matrix4& other) {
				return (*this = (*this) + other);
			};

			Matrix4& operator-=(const Matrix4& other) {
				return (*this = (*this) - other);
			};

			Matrix4& operator*=(const Matrix4& other) {
				return (*this = (*this) * other);
			};

			std::array<Vec4<Float32>, 4> data;

		};

		inline std::ostream& operator<<(std::ostream& outStream, const Matrix4& mat) {

			outStream << "Matrix4(";
			for (USize i = 0; i < 4; i++)
				outStream << "\n\t[" << mat[i] << "]";
			outStream << "\n)";
			return outStream;
		};

		namespace Matrix
		{
			Matrix4 operator*(Float32 scalar, const Matrix4& mat);
			Matrix4 transpose(const Matrix4& m);
			Float32 determinant(const Matrix4& m);
			Matrix4 inverse(const Matrix4& m);
			Matrix4 hadamardProduct(const Matrix4& first, const Matrix4& second);

			Matrix4 translate(const Vec3<Float32>& vec);
			// Angle in radians
			Matrix4 rotate(Float32 angle, const Vec3<Float32>& vec);
			Matrix4 scale(const Vec3<Float32>& vec);

			Matrix4 orthographic(Float32 left, Float32 right, Float32 bottom, Float32 top);
			Matrix4 orthographic(Float32 left, Float32 right, Float32 bottom, Float32 top, Float32 zNear, Float32 zFar);

			// Angle in radians
			Matrix4 perspective(Float32 angle, Float32 aspect, Float32 zNear, Float32 zFar);
			Matrix4 infinitePerspective(Float32 angle, Float32 aspect, Float32 zNear);

			Matrix4 lookAt(const Vec3<Float32>& eye, const Vec3<Float32> center, const Vec3<Float32>& upDirection);

		}; // namespace Matrix

	}; // namespace Math
}; //namespcae FLCL



   // Original matrix multiply function
   //Matrix4 operator*(const Matrix4& other) const {
   //
   //	
   //	// Should work fine. Perhaps easier to read as well
   //	const Matrix4& mat = *this;
   //
   //	const Vec4f srcA0 = mat[0];
   //	const Vec4f srcA1 = mat[1];
   //	const Vec4f srcA2 = mat[2];
   //	const Vec4f srcA3 = mat[3];
   //
   //	const Vec4f srcB0 = other[0];
   //	const Vec4f srcB1 = other[1];
   //	const Vec4f srcB2 = other[2];
   //	const Vec4f srcB3 = other[3];
   //
   //	Matrix4 result;
   //
   //	result[0] = srcA0 * srcB0[0] + srcA1 * srcB0[1] + srcA2 * srcB0[2] +
   //	srcA3 * srcB0[3];
   //	result[1] = srcA0 * srcB1[0] + srcA1 * srcB1[1] + srcA2 * srcB1[2] +
   //	srcA3 * srcB1[3];
   //	result[2] = srcA0 * srcB2[0] + srcA1 * srcB2[1] + srcA2 * srcB2[2] +
   //	srcA3 * srcB2[3];
   //	result[3] = srcA0 * srcB3[0] + srcA1 * srcB3[1] + srcA2 * srcB3[2] +
   //	srcA3 * srcB3[3];
   //
   //	return result;
   //};
