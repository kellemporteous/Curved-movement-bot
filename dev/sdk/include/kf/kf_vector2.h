////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_VECTOR2_HEADER
#define KF_VECTOR2_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"

#pragma warning( disable : 4201)

namespace kf
{
	template<typename TT>
	class Vector2T
	{
	public:
		using TYPE = typename TT;
		enum
		{
			size = 2
		};
		enum Elements
		{
			X = 0, R = 0, U = 0,
			Y = 1, G = 1, V = 1
		};
		union
		{
			TT e[2];
			union
			{
				struct
				{
					TT x;
					TT y;
				};
				struct
				{
					TT r;
					TT g;
				};
				struct
				{
					TT u;
					TT v;
				};
			};
		};

		inline Vector2T() : x(0), y(0)
		{
		}

		inline Vector2T(const Vector2T &c) : x(c.x), y(c.y)
		{
		}

		explicit inline Vector2T(TT xy) : x(xy), y(xy)
		{
		}

		template<typename T2>
		explicit inline Vector2T(const T2 *p) : x(TT(p[0])), y(TT(p[1]))
		{
		}

		inline Vector2T(TT xx, TT yy) : x(xx), y(yy)
		{
		}

		inline TT operator [] (unsigned int i) const
		{
			return e[i];
		}

		inline TT& operator [] (unsigned int i)
		{
			return e[i];
		}

		inline Vector2T operator*=(const TT &c)
		{
			x *= c;
			y *= c;
			return *this;
		}
		inline Vector2T operator/=(const TT &c)
		{
			x /= c;
			y /= c;
			return *this;
		}
		inline Vector2T operator+=(const Vector2T &c)
		{
			x += c.x;
			y += c.y;
			return *this;
		}
		inline Vector2T operator-=(const Vector2T &c)
		{
			x -= c.x;
			y -= c.y;
			return *this;
		}
		inline Vector2T operator*=(const Vector2T &c)
		{
			x *= c.x;
			y *= c.y;
			return *this;
		}
		inline Vector2T operator/=(const Vector2T &c)
		{
			x /= c.x;
			y /= c.y;
			return *this;
		}
		inline Vector2T operator=(const TT *p)
		{
			x = p[0];
			y = p[1];
			return *this;
		}
		inline Vector2T operator=(const Vector2T &v)
		{
			x = v.x;
			y = v.y;
			return *this;
		}

		inline float normalise()
		{
			TT l;
			l = TT(sqrt(x*x + y*y));
			if (l != 0.0)
			{
				set(x / l, y / l);
			}
			else
			{
				set(0, 0);
			}
			return l;
		}

		static inline Vector2T normalise(const Vector2T &v)
		{
			Vector2T temp(v);
			temp.normalise();
			return temp;
		}

		inline TT length() const
		{
			return sqrt(x*x + y*y);
		}

		static inline TT length(const Vector2T &v)
		{
			return v.length();
		}

		inline TT lengthSquared() const
		{
			return x*x + y*y;
		}

		static inline TT lengthSquared(const Vector2T &v)
		{
			return v.lengthSquared();
		}

		inline void clamp(float low, float high)
		{
			if (x < low) x = low;
			if (x > high) x = high;
			if (y < low) y = low;
			if (y > high) y = high;
		}

		inline Vector2T clamped(float low, float high) const
		{
			Vector2T v(*this);
			v.clamp(low, high);
			return v;
		}

		static inline void clamp(const Vector2T &v, float low, float high)
		{
			v.clamp(low, high);
		}

		static inline Vector2T clamped(const Vector2T &v, float low, float high)
		{
			return v.clamped(low, high);
		}

		inline void clamp(const Vector2T &low, const Vector2T &high)
		{
			if (x < low.x) x = low.x;
			if (x > high.x) x = high.x;
			if (y < low.y) y = low.y;
			if (y > high.y) y = high.y;
		}

		inline Vector2T clamped(const Vector2T &low, const Vector2T &high) const
		{
			Vector2T v(*this);
			v.clamp(low, high);
			return v;
		}

		static inline void clamp(Vector2T &v, const Vector2T &low, const Vector2T &high)
		{
			v.clamp(low, high);
		}

		static inline Vector2T clamped(const Vector2T &v, const Vector2T &low, const Vector2T &high)
		{
			return v.clamped(low, high);
		}

		inline void saturate()
		{
			clamp((TT)0, (TT)1);
		}

		inline Vector2T saturated() const
		{
			return clamped((TT)0, (TT)1);
		}

		static inline void saturate(const Vector2T &v)
		{
			v.saturate();
		}

		static inline Vector2T saturated(const Vector2T &v)
		{
			return v.saturated();
		}

		inline Vector2T perpCW() const
		{
			return Vector2T(y,-x);
		}

		static inline Vector2T perpCW(const Vector2T &v)
		{
			return v.perpCW();
		}

		inline Vector2T perpCCW() const
		{
			return Vector2T(-y, x);
		}

		static inline Vector2T perpCCW(const Vector2T &v)
		{
			return v.perpCCW();
		}

		inline Vector2T reflect(const Vector2T &n) const
		{
			return (TT)2.0 * n * dot(n) - *this;
		}

		static inline Vector2T reflect(const Vector2T &v, const Vector2T &n)
		{
			return v.reflect(n);
		}

		inline Vector2T dominantAxis() const
		{
			Vector2T v = abs();
			if (v.x >= v.y)
			{
				return x >= 0 ? UNIT_X() : NEGATIVE_UNIT_X();
			}
			else
			{
				return y >= 0 ? UNIT_Y() : NEGATIVE_UNIT_Y();
			}
		}

		static inline Vector2T dominantAxis(const Vector2T &v)
		{
			return v.dominantAxis();
		}

		inline Vector2T swiz(Elements comp1, Elements comp2) const
		{
			return Vector2T(e[comp1], e[comp2]);
		}

		static inline Vector2T swiz(const Vector2T &v, Elements comp1, Elements comp2)
		{
			return v.swiz(comp1, comp2);
		}

		inline void set(const Vector2T &value)
		{
			x = value.x;
			y = value.y;
		}

		inline void set(TT xy)
		{
			x = y = xy;
		}

		inline void set(TT xx, TT yy)
		{
			x = xx;
			y = yy;
		}

		template<typename T2>
		inline void set(const T2 *p)
		{
			x = TT(p[0]);
			y = TT(p[1]);
		}

		inline TT dot(const Vector2T &v) const
		{
			return x * v.x + y * v.y;
		}

		inline static TT dot(const Vector2T &v1, const Vector2T &v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		inline TT cross(const Vector2T &v) const
		{
			return x * v.y - y * v.x;
		}

		inline static TT cross(const Vector2T &v1, const Vector2T &v2)
		{
			return v1.x * v2.y - v1.y * v2.x;
		}

		inline friend Vector2T operator*(const Vector2T &v, const TT &val)
		{
			return Vector2T(v.x*val, v.y*val);
		}

		inline friend Vector2T operator*(const TT &val, const Vector2T &v)
		{
			return Vector2T(val*v.x, val*v.y);
		}

		inline friend Vector2T operator*(const Vector2T &v1, const Vector2T &v2)
		{
			return Vector2T(v1.x*v2.x, v1.y*v2.y);
		}

		inline friend Vector2T operator+(const Vector2T &v, const TT &val)
		{
			return Vector2T(v.x + val, v.y + val);
		}

		inline friend Vector2T operator+(const TT &val, const Vector2T &v)
		{
			return Vector2T(val + v.x, val + v.y);
		}

		inline friend Vector2T operator+(const Vector2T &v1, const Vector2T &v2)
		{
			return Vector2T(v1.x + v2.x, v1.y + v2.y);
		}

		inline friend Vector2T operator-(const Vector2T &v, const TT &val)
		{
			return Vector2T(v.x - val, v.y - val);
		}

		inline friend Vector2T operator-(const TT &val, const Vector2T &v)
		{
			return Vector2T(val - v.x, val - v.y);
		}

		inline friend Vector2T operator-(const Vector2T &v1, const Vector2T &v2)
		{
			return Vector2T(v1.x - v2.x, v1.y - v2.y);
		}

		inline friend Vector2T operator/(const Vector2T &v, const TT &val)
		{
			return Vector2T(v.x / val, v.y / val);
		}

		inline friend Vector2T operator/(const TT &val, const Vector2T &v)
		{
			return Vector2T(val / v.x, val / v.y);
		}

		inline friend Vector2T operator/(const Vector2T &v1, const Vector2T &v2)
		{
			return Vector2T(v1.x / v2.x, v1.y / v2.y);
		}

		inline Vector2T &operator=(TT c)
		{
			x = c;
			y = c;
			return *this;
		}

		inline Vector2T &operator,(TT c)
		{
			y = c;
			return *this;
		}

		inline bool operator==(const Vector2T &v)
		{
			return (x == v.x) && (y == v.y);
		}

		inline bool operator<(const Vector2T &v)
		{
			return x < v.x;
		}

		inline Vector2T minimum(const Vector2T &v) const
		{
			return Vector2T((x<v.x ? x : v.x), (y<v.y ? y : v.y));
		}

		static inline Vector2T minimum(const Vector2T &v1, const Vector2T &v2)
		{
			return v1.minimum(v2);
		}

		inline Vector2T maximum(const Vector2T &v) const
		{
			return Vector2T((x>v.x ? x : v.x), (y>v.y ? y : v.y));
		}

		static inline Vector2T maximum(const Vector2T &v1, const Vector2T &v2)
		{
			return v1.maximum(v2);
		}

		inline TT dist(const Vector2T &v) const
		{
			return (v - *this).length();
		}

		static inline TT dist(const Vector2T &v1, const Vector2T &v2)
		{
			return (v1 - v2).length();
		}

		static inline Vector2T pow(const Vector2T &v, const TT &e)
		{
			return v.pow(e);
		}

		static inline Vector2T log(const Vector2T &v)
		{
			return v.log();
		}

		static inline Vector2T exp(const Vector2T &v)
		{
			return Vector2T(std::exp(v.x), std::exp(v.y));
		}

		static inline Vector2T abs(const Vector2T &v)
		{
			return v.abs();
		}

		static inline Vector2T sign(const Vector2T &v)
		{
			return v.sign();
		}

		inline Vector2T rotate(TT angle) const
		{
			return Vector2T(x*cos(angle) - y*sin(angle), x*sin(angle) + y*cos(angle));
		}

		static inline Vector2T rotate(const Vector2T &v, TT angle)
		{
			return v.rotate(angle);
		}




		#define KF_SWIZZLE2D(a,b) inline Vector2T a##b() const { return Vector2T(a, b); }
		KF_SWIZZLE2D(x, x) KF_SWIZZLE2D(x, y) KF_SWIZZLE2D(y, x) KF_SWIZZLE2D(y, y) 
		KF_SWIZZLE2D(r, r) KF_SWIZZLE2D(r, g) KF_SWIZZLE2D(g, r) KF_SWIZZLE2D(g, g) 
		KF_SWIZZLE2D(s, s) KF_SWIZZLE2D(s, t) KF_SWIZZLE2D(t, s) KF_SWIZZLE2D(t, t)
		KF_SWIZZLE2D(u, u) KF_SWIZZLE2D(u, v) KF_SWIZZLE2D(v, u) KF_SWIZZLE2D(v, v)
		#undef KF_SWIZZLE2D

		inline static Vector2T ZERO()
		{
			return Vector2T(0, 0);
		}

		inline static Vector2T ONE()
		{
			return Vector2T(1, 1);
		}

		inline static Vector2T UNIT_X()
		{
			return Vector2T(1, 0);
		}

		inline static Vector2T UNIT_Y()
		{
			return Vector2T(0, 1);
		}

		inline static Vector2T NEGATIVE_UNIT_X()
		{
			return Vector2T(-1, 0);
		}

		inline static Vector2T NEGATIVE_UNIT_Y()
		{
			return Vector2T(0, -1);
		}
	};

	template <typename T1, typename T2>
	T1 convertVector2(const T2 &v)
	{
		T1 result;
		result.x = v.x;
		result.y = v.y;
		return result;
	}

	typedef Vector2T<float>  Vector2f;
	typedef Vector2T<double> Vector2d;
	typedef Vector2T<float>  Vector2;

}

#endif

