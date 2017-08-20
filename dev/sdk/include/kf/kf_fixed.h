////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_FIXED_HEADER
#define KF_FIXED_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"

namespace kf
{
	template<typename T, int FRACBITS>
	class FixedT
	{
	public:
		typedef T type;
		enum
		{
			intBits = sizeof(T) * 8 - FRACBITS,
			fracBits = FRACBITS,
			multiplier = 1<<fracBits
		};
		T number;

		FixedT():number(0)
		{
		}

		template <typename TT>
		FixedT(TT v):number(v*multiplier)
		{
		}

		inline FixedT operator+(const FixedT &v) const
		{
			return number + v.number;
		}

		inline FixedT operator-(const FixedT &v) const
		{
			return number - v.number;
		}

		inline FixedT operator*(const FixedT &v) const
		{
			return (number * v.number) >> fracBits;
		}

		inline FixedT operator/(const FixedT &v) const
		{
			return (number / v.number) << fracBits;
		}

		inline FixedT operator-() const
		{
			return -number;
		}

		inline T integer() const
		{
			return number >= 0 ? number >> fracBits : (number >> fracBits) + 1;
		}

		inline double frac() const
		{
			double d = double(number & (multiplier - 1)) / double(multiplier);
			return number >= 0 ? d : 1.0 - d;
		}

		explicit inline operator float()
		{
			return float(number) / multiplier;
		}

		explicit inline operator double()
		{
			return double(number) / multiplier;
		}
	};

	typedef FixedT<int, 8>  Fixed24_8;
	typedef FixedT<int, 16>  Fixed16_16;
	typedef FixedT<long long, 16>  Fixed48_16;
	typedef FixedT<long long, 32>  Fixed32_32;

}

#endif

