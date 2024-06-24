//============================================================================
// Name        : array_traits_ex3.cpp
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
 * @brief Returns number of bytes copied.
 * If one or both arguments are non-array (declared) type,
 * -1 is returned.
 */
template <typename T1, typename T2>
int SafeMemCopy(T1& dest, T2& src)
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
	uint8_t complexArr[2][3][5];        // x=2, y=3, z=5 --> total size = 2*3*5*sizeof(uint8_t) = 30*1 = 30 bytes
	char *myStr = "abc";				// trigger en fet warning! (ISO C++ forbids conversion of str.constant to ptr)
	char myArr[] = "test";
	array<uint16_t, 10> stlByteArr{};

	// Test 1:
	(void)SafeMemCopy(byteArr, myArr);	// OK: dest > src

	// Test 2:
	(void)SafeMemCopy(myArr, byteArr);	// WARN: dest < src --> partial copy!

	// Test 3:
	(void)SafeMemCopy(byteArr, stlByteArr);  // Nope ...

	// Test 4:
	(void)SafeMemCopy(myStr, byteArr);   // Nope too ...

	// Test 5:
	(void)SafeMemCopy(complexArr, byteArr);   // WARN: dest < src --> partial copy!

	// Test 6:
	(void)SafeMemCopy(byteArr, complexArr);   // OK ... (but differs in no. of dimensions!)

	return 0;
}
