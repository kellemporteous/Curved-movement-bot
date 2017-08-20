////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_QUATERNION_HEADER
#define KF_QUATERNION_HEADER

#include "kf/kf.h"
#include "kf/kf_vector3.h"
#include "kf/kf_vector4.h"

namespace kf
{
	template<typename T>
	class QuaternionT
	{
	public:
		typedef T type;

		enum Elements
		{
			W = 0,
			X = 1,
			Y = 2,
			Z = 3
		};
		union
		{
			T e[4];
			struct
			{
				T w;
				T x;
				T y;
				T z;
			};
		};

		QuaternionT() : w(1), x(0), y(0), z(0)
		{
		}

		QuaternionT(const T &ww, const T &xx, const T &yy, const T &zz) : w(ww), x(xx), y(yy), z(zz)
		{
		}

		QuaternionT(const Vector4T<T> &v) : x(v.x), y(v.y), z(v.z), w(v.w)
		{
		}

		QuaternionT(const T &angle, const kf::Vector3T<T> &axis)
		{
			kf::Vector3T<T> naxis = kf::normalise(axis);
			T sin_a = sin(angle / T(2));
			w = cos(angle / T(2));
			x = naxis.x * sin_a;
			y = naxis.y * sin_a;
			z = naxis.z * sin_a;
		}

		QuaternionT operator*(const QuaternionT &q) const
		{
			return QuaternionT(w * q.w - x * q.x - y * q.y - z * q.z,
							   w * q.x + x * q.w + y * q.z - z * q.y,
							   w * q.y + y * q.w + z * q.x - x * q.z,
							   w * q.z + z * q.w + x * q.y - y * q.x);
		}

		kf::Vector3T<T> operator*(const kf::Vector3T<T> &v) const
		{
			kf::Vector3T<T> uv, uuv;
			kf::Vector3T<T> qvec(x, y, z);
			uv = qvec.cross(v);
			uuv = qvec.cross(uv);
			uv *= (2.0f * w);
			uuv *= 2.0f;
			return v + uv + uuv;
		}

		QuaternionT operator+(const QuaternionT &q) const
		{
			return QuaternionT(w + q.w, x + q.x, y + q.y, z + q.z);
		}

		QuaternionT operator-(const QuaternionT &q) const
		{
			return QuaternionT(w - q.w, x - q.x, y - q.y, z - q.z);
		}

		inline QuaternionT conjugate() const
		{
			return QuaternionT(-x, -y, -z, w);
		}

		inline float normalise()
		{
			T l;
			l = T(sqrt(x*x + y*y + z*z + w*w));
			if (l != 0.0)
			{
				set(x / l, y / l, z / l, w / l);
			}
			else
			{
				set(0, 0, 0, 1);
			}
			return l;
		}

		friend inline QuaternionT normalise(const QuaternionT &q)
		{
			QuaternionT temp(q);
			temp.normalise();
			return temp;
		}

		inline T length() const
		{
			return sqrt(x*x + y*y + z*z + w*w);
		}

		friend inline T length(const QuaternionT &q)
		{
			return q.length();
		}

		inline T lengthSquared() const
		{
			return x*x + y*y + z*z + w*w;
		}

		friend inline T lengthSquared(const QuaternionT &q)
		{
			return q.lengthSquared();
		}

		inline void set(const QuaternionT &value)
		{
			x = value.x;
			y = value.y;
			z = value.z;
			w = value.w;
		}

		inline void set(T xyzw)
		{
			x = y = z = w = xyzw;
		}

		inline void set(T ww, T xx, T yy, T zz)
		{
			w = ww;
			x = xx;
			y = yy;
			z = zz;
		}

		template<typename T2>
		inline void set(const T2 *p)
		{
			w = T(p[0]);
			x = T(p[1]);
			y = T(p[2]);
			z = T(p[3]);
		}

		inline T dot(const QuaternionT &q) const
		{
			return x * q.x + y * q.y + z * q.z + w * q.w;
		}

		inline friend T dot(const QuaternionT &q1, const QuaternionT &q2)
		{
			return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
		}

		T scalar() const
		{
			return w;
		}

		void scalar(const T &val)
		{
			w = val;
		}

		Vector3T<T> vector() const
		{
			return Vector3T<T>(x, y, z);
		}

		void vector(const Vector3T<T> &val)
		{
			x = val.x;
			y = val.y;
			z = val.z;
		}

		//inline friend std::ostream &operator<<(std::ostream &o, const QuaternionT<T> &q)
		//{
		//	o << "{" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << "}";
		//	return o;
		//}

		//  KF_API static const QuaternionT<T> ZERO;
		//  KF_API static const QuaternionT<T> IDENTITY;
		inline static QuaternionT IDENTITY()
		{
			return QuaternionT(1, 0, 0, 0);
		}

	};

	typedef QuaternionT<float> Quaternion;

	template<typename T>
	QuaternionT<T> conjugate(const QuaternionT<T> &q)
	{
		return QuaternionT<T>(q.w, -q.x, -q.y, -q.z);
	}

	template<typename T>
	QuaternionT<T> normalise(const QuaternionT<T> &q)
	{
		T mag = q.magnitude();
		return QuaternionT<T>(q.w / mag, q.x / mag, q.y / mag, q.z / mag);
	}

	template <typename T1, typename T2>
	T1 convertQuaternion(const T2 &q)
	{
		T1 result;
		result.x = q.x;
		result.y = q.y;
		result.z = q.z;
		result.w = q.w;
		return result;
	}

}
#endif
