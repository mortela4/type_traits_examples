//============================================================================
// Name        : array_traits_ex1.cpp
// Author      : ml
// Version     :
// Copyright   : 
// Description : Demonstrate 'std::is_array<T>' from STL (#include <type_traits>)
//============================================================================

#include <iostream>
#include <array>
#include <utility>
#include <type_traits>
//
#include <stdint.h>

using namespace std;


uint8_t byteArr[10];
char *myStr = "abc";				// trigger en fet warning! (ISO C++ forbids conversion of str.constant to ptr)
char myArr[] = "test";
array<uint8_t, 10> stlByteArr{};


template <typename T>
bool IsArray(T& mayBeArray)
{
	bool chk = std::is_array<typeof(mayBeArray)>::value;

	cout << "'byteArr' is " << (chk?" ":"not") << " an array type" << endl;

	return chk;
}

template <typename T>
int GetArraySize(T& mayBeArray)
{
	if ( IsArray(mayBeArray) )
	{
		return (int)sizeof(mayBeArray);
	}
	else
	{
		return -1;	// = No size ...
	}
}


int main()
{
	int arrSize = 0;

	// Test 1:
	arrSize = GetArraySize(byteArr);
	cout << "'byteArr' has size " << arrSize  << endl;   // True

	// Test 2:
	arrSize = GetArraySize(myStr);
	cout << "'myStr' has size " << arrSize << endl;   // True

	// Test 3:
	arrSize = GetArraySize(myArr);
	cout << "'myArr' has size " << arrSize << endl;   // True

	// Test 4:
	arrSize = GetArraySize(stlByteArr);
	cout << "'stlByteArr' has size " << arrSize << endl;   // True

	return 0;
}
