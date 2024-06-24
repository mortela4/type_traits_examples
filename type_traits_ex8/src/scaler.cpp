
#include <iostream>
#include <string>
#include <cmath>
#include <variant>
#include <type_traits>

#include "scaler.h"


namespace HwDefs
{
	using namespace std;

	template <class T>
	Scaler<T>::Scaler(const string uom, const float factor, const float range)
    {
		static_assert( (std::is_floating_point<T>::value || std::is_integral<T>::value), "Cannot compile - 'Scale' class must be FP-type or integral type!");

		unitOfMeasure = uom;
    	scaleFactor = factor;
    	fullRange = range;
    }

	template <class T>
    float Scaler<T>::Scale(const T inval, const int numBits)
    {
		static_assert( (std::is_floating_point<T>::value || std::is_integral<T>::value), "Cannot compile - 'Scale' class must be FP-type or integral type!");

		float outval = 0.0F;

    	if (std::is_floating_point<T>::value)
    	{
    		cout << "Scaling floating-point value ..." << endl;
    		/* Primary check on INPUT variable - must happen RUNTIME */
    		if ( (float)abs((double)inval) > fullRange)
    		{
    			cout << "Cannot compute: 'inval' value is out-of-range! (max=" << fullRange << ")" << endl;
    			// Possibly throw exception here ...
    			return 0.0F;
    		}

    		raw = (double)inval;
    		auto tmp = std::get<double>(raw);
    		cout << "Raw input = " << tmp << endl;
    		outval = (float)(inval * scaleFactor);
    		cout << "Scaled output:" << outval << " [" << unitOfMeasure << "]" << endl;
    	}
    	else // INTeger type ...
    	{
    		cout << "Scaling integral value ..." << endl;
    		raw = (long)inval;
    		long tmp = std::get<long>(raw);
    		cout << "Raw input = " << tmp << endl;
    		/* Scaling using range and number of bits - should optionally check for numBits != 0 here */
    		unsigned int adcRange = PowerOfTwo(numBits);
    		/* Check for valid range must happen RUNTIME (could be fixed with RangesV3-library;-) */
    		if ( (unsigned int)abs((long)inval) > adcRange)
    		{
    			cout << "Cannot compute: 'inval' value is out-of-range! (max=" << adcRange-1 << ")" << endl;
    			// Possibly throw exception here ...
    			return 0.0F;
    		}
    		/* 'inval' within correct range */
    		float fractionPerBit = fullRange / adcRange;
    		cout << "Fraction = " << fractionPerBit << " [V/LSB]" << endl;
    		outval = (float)((inval * fractionPerBit) * scaleFactor);
    		cout << "Scaled output:" << outval << " [" << unitOfMeasure << "]" << endl;
    	}

		return outval;

    }

	template <class T>
    T Scaler<T>::GetRaw(void)
    {
		/* Redundant - only needed in constructor */
		static_assert( (std::is_floating_point<T>::value || std::is_integral<T>::value), "Cannot compile - 'Scale' class must be FP-type or integral type!");

		T rawVal;

    	if (std::is_floating_point<T>::value)
    	{
    		rawVal = std::get<double>(raw);
    		cout << "Raw value returned as FP-type! Value = " << rawVal << endl;
    	}
    	else // INTeger type ...
    	{
    		rawVal = std::get<long>(raw);
    		cout << "Raw value returned as INTegral-type! Value = " << rawVal << endl;
    	}

    	return rawVal;
    }

}
