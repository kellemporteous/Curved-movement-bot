////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_MATRIX3_HEADER
#define KF_MATRIX3_HEADER

#include "kf/kf.h"
#include "kf/kf_vector3.h"

namespace kf
{
	template<typename T>
	class Matrix3T
	{
	public:
		enum { rows = 3, columns = 3 };

		union
		{
			T m[rows][columns];
			struct
			{
				T m11, m12, m13;
				T m21, m22, m23;
				T m31, m32, m33;
			};
		};

		Matrix3T() : m11(0),m12(0),m13(0),m21(0),m22(0),m23(0),m31(0),m32(0),m33(0)
		{
		}

		Matrix3T(T arg11, T arg12, T arg13, T arg21, T arg22, T arg23, T arg31, T arg32, T arg33)
		{
			m11 = arg11;
			m12 = arg12;
			m13 = arg13;
			m21 = arg21;
			m22 = arg22;
			m23 = arg23;
			m31 = arg31;
			m32 = arg32;
			m33 = arg33;
		}

		Matrix3T operator*(const Matrix3T &mat)
		{
			return Matrix3T(m11*mat.m11 + m12*mat.m21 + m13*mat.m31,
				m11*mat.m12 + m12*mat.m22 + m13*mat.m32,
				m11*mat.m13 + m12*mat.m23 + m13*mat.m33,
				m21*mat.m11 + m22*mat.m21 + m23*mat.m31,
				m21*mat.m12 + m22*mat.m22 + m23*mat.m32,
				m21*mat.m13 + m22*mat.m23 + m23*mat.m33,
				m31*mat.m11 + m32*mat.m21 + m33*mat.m31,
				m31*mat.m12 + m32*mat.m22 + m33*mat.m32,
				m31*mat.m13 + m32*mat.m23 + m33*mat.m33);
		}

		Matrix3T operator+(const Matrix3T &mat) const
		{
			return Matrix3T(m11 + mat.m11, m12 + mat.m12, m13 + mat.m13,
				m21 + mat.m21, m22 + mat.m22, m23 + mat.m23,
				m31 + mat.m31, m32 + mat.m32, m33 + mat.m33);
		}

		Matrix3T operator-(const Matrix3T &mat) const
		{
			return Matrix3T(m11 - mat.m11, m12 - mat.m12, m13 - mat.m13,
				m21 - mat.m21, m22 - mat.m22, m23 - mat.m23,
				m31 - mat.m31, m32 - mat.m32, m33 - mat.m33);
		}
		kf::Vector3T<T> operator * (const kf::Vector3T<T> &v) const
		{
			return kf::Vector3T<T>((m11 * v.x + m12 * v.y + m13 * v.z),
				(m21 * v.x + m22 * v.y + m23 * v.z),
				(m31 * v.x + m32 * v.y + m33 * v.z));
		}

		Matrix3T transpose()
		{
			return Matrix3T(m11, m21, m31, m12, m22, m32, m13, m23, m33);
		}

		kf::Vector3T<T> row(u32 i) const
		{
			return kf::Vector3T<T>(m[i][0], m[i][1], m[i][2]);
		}

		kf::Vector3T<T> column(u32 i) const
		{
			return kf::Vector3T<T>(m[0][i], m[1][i], m[2][i]);
		}

		void row(u32 i, kf::Vector3T<T> v)
		{
			m[i][0] = v.x;
			m[i][1] = v.y;
			m[i][2] = v.z;
		}

		void column(u32 i, kf::Vector3T<T> v)
		{
			m[0][i] = v.x;
			m[1][i] = v.y;
			m[2][i] = v.z;
		}

		T *operator[](u32 i)
		{
			return m[i];
		}

		const T *operator[](u32 i) const
		{
			return m[i];
		}

		T &operator()(u32 j, u32 i)
		{
			return m[j][i];
		}

		const T &operator()(u32 j, u32 i) const
		{
			return m[j][i];
		}

		kf::Vector3 xaxis()
		{
			return kf::Vector3(m[0][0], m[1][0], m[2][0]);
		}

		void xaxis(const kf::Vector3 &v)
		{
			m[0][0] = v.x;
			m[1][0] = v.y;
			m[2][0] = v.z;
		}

		kf::Vector3 yaxis()
		{
			return kf::Vector3(m[0][1], m[1][1], m[2][1]);
		}

		void yaxis(const kf::Vector3 &v)
		{
			m[0][1] = v.x;
			m[1][1] = v.y;
			m[2][1] = v.z;
		}

		kf::Vector3 zaxis()
		{
			return kf::Vector3(m[0][2], m[1][2], m[2][2]);
		}

		void zaxis(const kf::Vector3 &v)
		{
			m[0][2] = v.x;
			m[1][2] = v.y;
			m[2][2] = v.z;
		}

		static const Matrix3T<T> ZERO()
		{
			return Matrix3T<T>(0, 0, 0, 0, 0, 0, 0, 0, 0);
		}

		static const Matrix3T<T> IDENTITY()
		{
			return Matrix3T<T>(1, 0, 0, 0, 1, 0, 0, 0, 1);
		}
	};

	typedef Matrix3T<float> Matrix3;
}
#endif
