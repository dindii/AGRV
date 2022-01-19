#include "AGRVPCH.h"

namespace PDG
{
	//regula clamp
	template<typename T>
	T clamp(const T& min, const T& max, const T& val)
	{
		T aux = 0;

		if (val < min)
		{
			aux = min;
			return aux;
		}
		else if (val > max)
		{
			aux = max;
			return aux;
		}

		return val;
	}

	//Clamps the value only to the floor
	//i.e: a clamp without max
	template<typename T>
	T clampMin(const T& min, const T& val)
	{
		T aux = 0;

		if (val < min)
		{
			aux = min;
			return aux;
		}

		return val;
	}
}