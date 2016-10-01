#include <Math/Matrix4.h>
#include <cmath>

namespace FLCL
{
	namespace Math
	{
		namespace Matrix
		{
			// Matrix scalar multiply reverse
			Matrix4 operator*(Float32 scalar, const Matrix4& mat) {
				Matrix4 resultMatrix;
				for (USize iCount = 0; iCount < 4; iCount++)
					resultMatrix[iCount] = mat[iCount] * scalar;
				return resultMatrix;
			};

			Matrix4 hadamardProduct(const Matrix4& first, const Matrix4& second)
			{
				Matrix4 result;

				for (USize i = 0; i < 4; i++)
					result[i] = first[i] * second[i];

				return result;
			};

			Matrix4 transpose(const Matrix4& mat) {
				Matrix4 result;

				for (USize i = 0; i < 4; i++)
					for (USize j = 0; j < 4; j++)
						result[i][j] = mat[j][i];

				return result;
			};

			Float32 determinant(const Matrix4& m) {

				//const Matrix4& m = *this;
				Float32 coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
				Float32 coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
				Float32 coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

				Float32 coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
				Float32 coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
				Float32 coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

				Float32 coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
				Float32 coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
				Float32 coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

				Float32 coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
				Float32 coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
				Float32 coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

				Float32 coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
				Float32 coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
				Float32 coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

				Float32 coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
				Float32 coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
				Float32 coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

				Vec4<Float32> fac0(coef00, coef00, coef02, coef03);
				Vec4<Float32> fac1(coef04, coef04, coef06, coef07);
				Vec4<Float32> fac2(coef08, coef08, coef10, coef11);
				Vec4<Float32> fac3(coef12, coef12, coef14, coef15);
				Vec4<Float32> fac4(coef16, coef16, coef18, coef19);
				Vec4<Float32> fac5(coef20, coef20, coef22, coef23);

				Vec4<Float32> vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
				Vec4<Float32> vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
				Vec4<Float32> vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
				Vec4<Float32> vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

				Vec4<Float32> inv0(vec1 * fac0 - vec2 * fac1 + vec3 * fac2);
				Vec4<Float32> inv1(vec0 * fac0 - vec2 * fac3 + vec3 * fac4);
				Vec4<Float32> inv2(vec0 * fac1 - vec1 * fac3 + vec3 * fac5);
				Vec4<Float32> inv3(vec0 * fac2 - vec1 * fac4 + vec2 * fac5);

				Vec4<Float32> signA(+1, -1, +1, -1);
				Vec4<Float32> signB(-1, +1, -1, +1);
				Matrix4 inverse(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

				Vec4<Float32> row0(inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]);

				Vec4<Float32> dot0(m[0] * row0);
				Float32 dot1 = (dot0.x + dot0.y) + (dot0.z + dot0.w);
				return dot1;

			};

			Matrix4 inverse(const Matrix4& m) {

				//const Matrix4& m = *this;

				Float32 coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
				Float32 coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
				Float32 coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

				Float32 coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
				Float32 coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
				Float32 coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

				Float32 coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
				Float32 coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
				Float32 coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

				Float32 coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
				Float32 coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
				Float32 coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

				Float32 coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
				Float32 coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
				Float32 coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

				Float32 coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
				Float32 coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
				Float32 coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

				Vec4<Float32> fac0(coef00, coef00, coef02, coef03);
				Vec4<Float32> fac1(coef04, coef04, coef06, coef07);
				Vec4<Float32> fac2(coef08, coef08, coef10, coef11);
				Vec4<Float32> fac3(coef12, coef12, coef14, coef15);
				Vec4<Float32> fac4(coef16, coef16, coef18, coef19);
				Vec4<Float32> fac5(coef20, coef20, coef22, coef23);
				Vec4<Float32> vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
				Vec4<Float32> vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
				Vec4<Float32> vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
				Vec4<Float32> vec3(m[1][3], m[0][3], m[0][3], m[0][3]);
				Vec4<Float32> inv0(vec1 * fac0 - vec2 * fac1 + vec3 * fac2);
				Vec4<Float32> inv1(vec0 * fac0 - vec2 * fac3 + vec3 * fac4);
				Vec4<Float32> inv2(vec0 * fac1 - vec1 * fac3 + vec3 * fac5);
				Vec4<Float32> inv3(vec0 * fac2 - vec1 * fac4 + vec2 * fac5);
				Vec4<Float32> signA(+1, -1, +1, -1);
				Vec4<Float32> signB(-1, +1, -1, +1);

				Matrix4 inverse(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

				Vec4<Float32> row0(inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]);
				Vec4<Float32> dot0(m[0] * row0);
				Float32 dot1 = (dot0.x + dot0.y) + (dot0.z + dot0.w);
				Float32 oneOverDeterminant = 1.0f / dot1;

				//return inverse * oneOverDeterminant;
				return oneOverDeterminant * inverse;

			};

			Matrix4 translate(const Vec3<Float32>& vec) {
				Matrix4 result;
				result[3] = Vec4<Float32>(vec, 1);
				return result;
			};

			// Angle in radians
			Matrix4 rotate(Float32 angle, const Vec3<Float32>& vec) {
				const Float32 angle_cos = std::cos(angle);
				const Float32 angle_sin = std::sin(angle);

				const Vec3<Float32> axis(norm(vec));
				const Vec3<Float32> t = (1.0f - angle_cos) * axis;

				Matrix4 rotation;
				rotation[0][0] = angle_cos + t[0] * axis[0];
				rotation[0][1] = 0 + t[0] * axis[1] + angle_sin * axis[2];
				rotation[0][2] = 0 + t[0] * axis[2] - angle_sin * axis[1];
				rotation[0][3] = 0;

				rotation[1][0] = 0 + t[1] * axis[0] - angle_sin * axis[2];
				rotation[1][1] = angle_cos + t[1] * axis[1];
				rotation[1][2] = 0 + t[1] * axis[2] + angle_sin * axis[2];
				rotation[1][3] = 0;

				rotation[2][0] = 0 + t[2] * axis[0] + angle_sin * axis[1];
				rotation[2][1] = 0 + t[2] * axis[0] - angle_sin * axis[0];
				rotation[2][2] = angle_cos + t[2] * axis[2];
				rotation[2][3] = 0;

				return rotation;

			};

			Matrix4 scale(const Vec3<Float32>& vec) {
				Matrix4 result({ vec.x, 0, 0, 0 }, { 0, vec.y, 0, 0 }, { 0, 0, vec.z, 0 }, { 0, 0, 0, 1 });

				return result;
			};

			Matrix4 orthographic(Float32 left, Float32 right, Float32 bottom, Float32 top)
			{
				Matrix4 result;

				result[0][0] = 2.0f / (right - left);
				result[1][1] = 2.0f / (top - bottom);
				result[2][2] = -1.0f;
				result[3][0] = -(right + left) / (right - left);
				result[3][1] = -(top + bottom) / (top - bottom);

				return result;
			};

			Matrix4 orthographic(Float32 left, Float32 right, Float32 bottom, Float32 top, Float32 zNear, Float32 zFar)
			{
				Matrix4 result;

				result[0][0] = 2.0f * zNear / (right - left);
				result[1][1] = 2.0f * zNear / (top - bottom);
				result[2][2] = -2.0f / (zFar - zNear);
				result[3][0] = -(right + left) / (right - left);
				result[3][1] = -(top + bottom) / (top - bottom);
				result[3][2] = -(zFar + zNear) / (zFar - zNear);

				return result;
			};

			Matrix4 perspective(Float32 fovy, Float32 aspect, Float32 zNear, Float32 zFar)
			{

				const Float32 tanHalfFovy = std::tan(fovy / 2.0f);

				Matrix4 result(0.0f);

				result[0][0] = 1.0f / (aspect * tanHalfFovy);
				result[1][1] = 1.0f / (tanHalfFovy);
				result[2][2] = -(zFar + zNear) / (zFar - zNear);
				result[2][3] = -1.0f;
				result[3][2] = -2.0f * zFar * zNear / (zFar - zNear);

				return result;
			};

			Matrix4 infinitePerspective(Float32 fovy, Float32 aspect, Float32 zNear)
			{
				const Float32 range = std::tan(fovy / 2.0f) * zNear;
				const Float32 left = -range * aspect;
				const Float32 right = range * aspect;
				const Float32 bottom = -range;
				const Float32 top = range;

				Matrix4 result(0.0f);
				result[0][0] = (2.0f * zNear) / (right - left);
				result[1][1] = (2.0f * zNear) / (top - bottom);
				result[2][2] = -1.0f;
				result[2][3] = -1.0f;
				result[3][2] = -2.0f * zNear;

				return result;
			};

			Matrix4 lookAt(const Vec3<Float32>& eye, const Vec3<Float32> center, const Vec3<Float32>& upDirection)
			{
				const Vec3<Float32> f(norm(center - eye));
				const Vec3<Float32> s(norm(cross(f, upDirection)));
				const Vec3<Float32> u(cross(s, f));

				Matrix4 result;

				result[0][0] = +s.x;
				result[1][0] = +s.y;
				result[2][0] = +s.z;

				result[0][1] = +u.x;
				result[1][1] = +u.y;
				result[2][1] = +u.z;

				result[0][2] = -f.x;
				result[1][2] = -f.y;
				result[2][2] = -f.z;

				result[3][0] = -dot(s, eye);
				result[3][1] = -dot(u, eye);
				result[3][2] = +dot(f, eye);

				return result;
			}
		}

	} // namespace Math
} // namespace FLCL