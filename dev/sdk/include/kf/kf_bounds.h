////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_BOUNDS_HEADER
#define KF_BOUNDS_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"
#include <limits>

namespace kf
{
	template<typename TT>
	class AABB2T
	{
	public:
		using TYPE = typename TT;

		Vector2T<TT> minCorner;
		Vector2T<TT> maxCorner;
		bool infinite;

		inline AABB2T() :minCorner(std::numeric_limits<TT>::max(), std::numeric_limits<TT>::max()), maxCorner(std::numeric_limits<TT>::min(), std::numeric_limits<TT>::min()), infinite(false)
		{
		}

		inline AABB2T(const Vector2T<TT> &v) : minCorner(v), maxCorner(v), infinite(false)
		{
		}

		inline AABB2T(const Vector2T<TT> &v1, const Vector2T<TT> &v2) : infinite(false)
		{
			if (v1.x <= v2.x)
			{
				minCorner.x = v1.x;
				maxCorner.x = v2.x;
			}
			else
			{
				minCorner.x = v2.x;
				maxCorner.x = v1.x;
			}
			if (v1.y <= v2.y)
			{
				minCorner.y = v1.y;
				maxCorner.y = v2.y;
			}
			else
			{
				minCorner.y = v2.y;
				maxCorner.y = v1.y;
			}
		}

		inline AABB2T(TT x1, TT y1, TT x2, TT y2) : infinite(false)
		{
			if (x1 <= x2)
			{
				minCorner.x = x1;
				maxCorner.x = x2;
			}
			else
			{
				minCorner.x = x2;
				maxCorner.x = x1;
			}
			if (y1 <= y2)
			{
				minCorner.y = y1;
				maxCorner.y = y2;
			}
			else
			{
				minCorner.y = y2;
				maxCorner.y = y1;
			}
		}

		inline AABB2T &operator=(const Vector2T<TT> &v)
		{
			minCorner = v;
			maxCorner = v;
			infinite = false;
			return *this;
		}

		inline AABB2T &set(const Vector2T<TT> &v)
		{
			minCorner = v;
			maxCorner = v;
			infinite = false;
			return *this;
		}

		inline AABB2T &set(const Vector2T<TT> &v1, const Vector2T<TT> &v2)
		{
			if (v1.x <= v2.x)
			{
				minCorner.x = v1.x;
				maxCorner.x = v2.x;
			}
			else
			{
				minCorner.x = v2.x;
				maxCorner.x = v1.x;
			}
			if (v1.y <= v2.y)
			{
				minCorner.y = v1.y;
				maxCorner.y = v2.y;
			}
			else
			{
				minCorner.y = v2.y;
				maxCorner.y = v1.y;
			}
			infinite = false;
			return *this;
		}

		inline AABB2T &set(TT x1, TT y1, TT x2, TT y2)
		{
			if (x1 <= x2)
			{
				minCorner.x = x1;
				maxCorner.x = x2;
			}
			else
			{
				minCorner.x = x2;
				maxCorner.x = x1;
			}
			if (y1 <= y2)
			{
				minCorner.y = y1;
				maxCorner.y = y2;
			}
			else
			{
				minCorner.y = y2;
				maxCorner.y = y1;
			}
			infinite = false;
			return *this;
		}

		inline bool operator==(const AABB2T &aabb)
		{
			return (infinite == aabb.infinite) && (minCorner == aabb.minCorner) && (maxCorner == aabb.maxCorner);
		}

		inline bool operator<(const AABB2T &aabb)
		{
			return minCorner < aabb.minCorner;
		}

		inline AABB2T &merge(const Vector2T<TT> &v)
		{
			if (!infinite)
			{
				minCorner = minCorner.minimum(v);
				maxCorner = maxCorner.maximum(v);
			}
			return *this;
		}

		inline AABB2T &merge(const AABB2T &aabb)
		{
			if (!infinite)
			{
				if (!aabb.infinite)
				{
					minCorner = minCorner.minimum(aabb.minCorner);
					maxCorner = maxCorner.maximum(aabb.maxCorner);
				}
				else
				{
					infinite = true;
				}
			}
			return *this;
		}

		inline TT width() const
		{
			if (!infinite)
			{
				return (maxCorner.x - minCorner.x);
			}
			else
			{
				return 0;
			}
		}

		inline TT height() const
		{
			if (!infinite)
			{
				return (maxCorner.y - minCorner.y);
			}
			else
			{
				return 0;
			}
		}

		inline Vector2T<TT> size() const
		{
			if (!infinite)
			{
				return (maxCorner - minCorner);
			}
			else
			{
				return kf::Vector2T<TT>::ZERO();
			}
		}

		inline Vector2T<TT> centre() const
		{
			if (!infinite)
			{
				return (maxCorner + minCorner)*0.5;
			}
			else
			{
				return kf::Vector2T<TT>::ZERO();
			}
		}

		inline static AABB2T ZERO()
		{
			return AABB2T(0, 0, 0, 0);
		}

		inline static AABB2T Infinite()
		{
			AABB2T aabb;
			aabb.infinite = true;
			return aabb;
		}
	};


	typedef AABB2T<float>  AABB2f;
	typedef AABB2T<int>    AABB2i;
	typedef AABB2T<double> AABB2d;
	typedef AABB2T<float>  AABB2;
}

#endif

