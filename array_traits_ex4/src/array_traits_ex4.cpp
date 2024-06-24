//============================================================================
// Name        : array_traits_ex4.cpp
// Author      : ml
// Version     :
// Copyright   : 
// Description : Demonstrate 'std::is_array<T>' from STL (#include <type_traits>)
//               (using it for safe usage of memcpy() - and possibly others ...)
//============================================================================

#include <iostream>
#include <array>
#include <utility>
#include <type_traits>
//
#include <stdint.h>

using namespace std;


template <typename T>
bool IsArray(T& mayBeArray)
{
	bool chk = std::is_array<typeof(mayBeArray)>::value;
#ifdef NDEBUG
	cout << "IsArray(): argument is " << (chk?"":"not ") << "an array type" << endl;
#endif
	return chk;
}

/**
 * @brief Assumes one-dimensional array.
 */
template <typename T>
int GetArrayRange(T& mayBeArray)
{
	if ( IsArray(mayBeArray) )
	{
		// return (int)sizeof(mayBeArray);  /* Only works with byte-sized element arrays */
		return (int)( sizeof(mayBeArray) / sizeof(mayBeArray[0]) );
	}
	else
	{
		return -1;	// = No size ...
	}
}

template <typename T>
int GetArraySize(T& mayBeArray)
{
	if ( IsArray(mayBeArray) )
	{
		return (int)sizeof(mayBeArray);  /* memory size of total array */
	}
	else
	{
		return -1;	// = No size ...
	}
}

/**
 * @brief Handles up to 3-dimensional arrays (who would need more?? :-)
 */
template <typename T>
int GetDimensionExtent(T& arr, const int dim)
{
	int size_along_axis = 0;

	/* Awkward (and ugly) work-around ... :-( */
	switch (dim)
	{
	case 0: size_along_axis = extent<typeof(arr), 0>::value; break;
	case 1: size_along_axis = extent<typeof(arr), 1>::value; break;
	case 2: size_along_axis = extent<typeof(arr), 2>::value; break;
	default: size_along_axis = 0; cout << "Arrays of dimension = " << dim+1 << " is NOT supported! (max=3)" << endl; break;
	}

	return size_along_axis;
}


/**
 * @brief Returns number of bytes copied.
 * If one or both arguments are non-array (declared) type,
 * -1 is returned.
 */
template <typename T1, typename T2>
int SafeMemCopyRangeChecked(T1& dest, T2& src)
{
	int destSize = GetArraySize(dest);
	int srcSize = GetArraySize(src);
	int copySize = 0;

	/* Check A: both args (declared) arrays? */
	if ( destSize >= 0 && srcSize >= 0)
	{
		/* Check B: destination fits source? */
		if ( destSize >= srcSize )
		{
			copySize = srcSize;
			cout << "SafeMemCopy(): dest >= src --> safe to copy: " << copySize << " bytes copied ..." << endl;
		}
		else
		{
			copySize = destSize;
			cout << "SafeMemCopy(): WARNING: dest < src --> unsafe to copy! Partial copy of source = " << copySize << " bytes ..." << endl;
		}

		/* Check C: same size of elements in both arrays?? */
		if ( sizeof(dest[0]) != sizeof(src[0]) )
		{
			cout << "SafeMemCopy(): INFO: size of (0'th dimension) array elements differ (i.e. not same type) sure this is OK??" << endl;
		}

		/* Check D: same # of dimensions for both arrays?? */
		if ( rank<T1>::value != rank<T2>::value )
		{
			cout << "SafeMemCopy(): WARNING: dimensions of arrays differ - sure copy from <src> to <dest> is OK??" << endl;
			cout << "Summary:" << endl << "==============" << endl << "dim(dest) = " << rank<T1>::value << endl << "dim(src) = " << rank<T2>::value << endl;
		}
		else
		{
			int dimensions = rank<T1>::value;
			cout << "SafeMemCopy(): INFO: dim(A) == dim(B) --> both have # dimensions = " << dimensions << endl;

			/* Validate extent along each dimension: */
			for (int i=0; i<dimensions; i++)
			{
				auto srcExtent = GetDimensionExtent(src, i);
				auto destExtent = GetDimensionExtent(dest, i);

				if (srcExtent != destExtent)
				{
					cout << "SafeMemCopy(): WARNING: array <dest> dimension " << i << " extent = " << destExtent << " differs differs from <src> extent = " << srcExtent << endl;
				}
				else
				{
					if (srcExtent > 0 && destExtent > 0)
					{
						cout << "SafeMemCopy(): INFO: dim." << i << " --> array <dest> dimension equals <src> extent = " << srcExtent << endl;
					}
					else
					{
						cout << "SafeMemCopy(): WARNING: one or both of array <dest> and <src> have more than 3 (=unsupported) dimensions! " << endl;
					}
				}
			}
		}

		/* Do memcpy((void *)dest, (void *)src, copySize); here! */

		return copySize;
	}
	else
	{
		cout << "SafeMemCopy(): ERROR - one or both of <src> and <dest> are NOT declared arrays!!" << endl;

		return -1;	// = No copy ...
	}
}


int main()
{
	uint64_t byteArr[10];
	uint8_t complexArrA[2][3][10];        // x=2, y=3, z=10 --> total size = 2*3*10*sizeof(uint8_t) = 60*1 = 60 bytes
	uint8_t complexArrB[3][5][4];        // x=3, y=5, z=4 --> total size = 3*5*4*sizeof(uint8_t) = 60*1 = 60 bytes (= same size as 'complexArrA', but different structure)
	uint8_t complexArrC[2][3][5][2];    // not supported .... (but, size=60 bytes)
	uint8_t complexArrD[2][3][5][2];    // not supported .... (but, also size=60 bytes - and identical to 'complexArrC')
	char *myStr = "abc";				// trigger en fet warning! (ISO C++ forbids conversion of str.constant to ptr)
	char myArr[] = "test";
	array<uint16_t, 10> stlByteArr{};

	int tstCount = 1;

	// Test 1:
	cout << endl << "Test no." << tstCount++ << endl;
	(void)SafeMemCopyRangeChecked(byteArr, myArr);	// OK: dest > src

	// Test 2:
	cout << endl << "Test no." << tstCount++ << endl;
	(void)SafeMemCopyRangeChecked(myArr, byteArr);	// WARN: dest < src --> partial copy!

	// Test 3:
	cout << endl << "Test no." << tstCount++ << endl;
	(void)SafeMemCopyRangeChecked(byteArr, stlByteArr);  // Nope ...

	// Test 4:
	cout << endl << "Test no." << tstCount++ << endl;
	(void)SafeMemCopyRangeChecked(myStr, byteArr);   // Nope too ...

	// Test 5:
	cout << endl << "Test no." << tstCount++ << endl;
	(void)SafeMemCopyRangeChecked(complexArrA, byteArr);   // WARN: dest < src --> partial copy!

	// Test 6:
	cout << endl << "Test no." << tstCount++ << endl;
	(void)SafeMemCopyRangeChecked(byteArr, complexArrA);   // OK ... maybe?? (but differs in no. of dimensions!)

	// Test 7:
	cout << endl << "Test no." << tstCount++ << endl;
	(void)SafeMemCopyRangeChecked(complexArrA, complexArrB);   // OK ... maybe? (but differs in extent/#elements along each dimension!)

	// Test 8:
	cout << endl << "Test no." << tstCount++ << endl;
	(void)SafeMemCopyRangeChecked(complexArrA, complexArrC);   // OK ... maybe? (but differs in dimensions and extent/#elements along each dimension!)

	// Test 9:
	cout << endl << "Test no." << tstCount++ << endl;
	(void)SafeMemCopyRangeChecked(complexArrC, complexArrD);   // OK ... maybe? (but differs in dimensions and extent/#elements along each dimension!)

	return 0;
}
