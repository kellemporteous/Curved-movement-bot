////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_MATRIX2_HEADER
#define KF_MATRIX2_HEADER

#include "kf/kf.h"
#include "kf/kf_vector2.h"

namespace kf
{
	template<typename T>
	class Matrix2T
	{
	public:
		enum { rows = 2, columns = 2 };

		union
		{
			T m[rows][columns];
			struct
			{
				T m11, m12;
				T m21, m22;
			};
		};

		Matrix2T() : m11(0),m12(0),m21(0),m22(0)
		{
		}

		Matrix2T(T arg11, T arg12, T arg21, T arg22)
		{
			m11 = arg11;
			m12 = arg12;
			m21 = arg21;
			m22 = arg22;
		}

		Matrix2T operator*(const Matrix2T &mat)
		{
			return Matrix2T(m11*mat.m11 + m12*mat.m21,
							m11*mat.m12 + m12*mat.m22,
							m21*mat.m11 + m22*mat.m21,
							m21*mat.m12 + m22*mat.m22);
		}

		Matrix2T operator+(const Matrix2T &mat) const
		{
			return Matrix2T(m11 + mat.m11, m12 + mat.m12,
				m21 + mat.m21, m22 + mat.m22);
		}

		Matrix2T operator-(const Matrix2T &mat) const
		{
			return Matrix2T(m11 - mat.m11, m12 - mat.m12,
				m21 - mat.m21, m22 - mat.m22);
		}
		kf::Vector2T<T> operator * (const kf::Vector2T<T> &v) const
		{
			return kf::Vector2T<T>((m11 * v.x + m12 * v.y),
				(m21 * v.x + m22 * v.y));
		}

		Matrix2T transpose()
		{
			return Matrix2T(m11, m21, m12, m22);
		}

		kf::Vector2T<T> row(u32 i) const
		{
			return kf::Vector2T<T>(m[i][0], m[i][1]);
		}

		kf::Vector2T<T> column(u32 i) const
		{
			return kf::Vector2T<T>(m[0][i], m[1][i]);
		}

		void row(u32 i, kf::Vector2T<T> v)
		{
			m[i][0] = v.x;
			m[i][1] = v.y;
		}

		void column(u32 i, kf::Vector2T<T> v)
		{
			m[0][i] = v.x;
			m[1][i] = v.y;
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

		kf::Vector2T<T> xaxis()
		{
			return kf::Vector2T<T>(m[0][0], m[1][0]);
		}

		void xaxis(const kf::Vector2T<T> &v)
		{
			m[0][0] = v.x;
			m[1][0] = v.y;
		}

		kf::Vector2T<T> yaxis()
		{
			return kf::Vector2T<T>(m[0][1], m[1][1]);
		}

		void yaxis(const kf::Vector2T<T> &v)
		{
			m[0][1] = v.x;
			m[1][1] = v.y;
		}

		static const Matrix2T<T> ZERO()
		{
			return Matrix2T<T>(0, 0, 0, 0);
		}

		static const Matrix2T<T> IDENTITY()
		{
			return Matrix2T<T>(1, 0, 0, 1);
		}
	};

	typedef Matrix2T<float> Matrix2;
}
#endif
