//============================================================================
// Name        : array_traits_ex1.cpp
// Author      : ml
// Version     :
// Copyright   : 
// Description : Demonstrate 'std::is_array<T>' from STL (#include <type_traits>)
//============================================================================

#include <iostream>
#include <array>
#include <type_traits>
//
#include <stdint.h>

using namespace std;


uint8_t byteArr[10];
char *myStr = "abc";				// trigger en fet warning! (ISO C++ forbids conversion of str.constant to ptr)
char myArr[] = "test";
array<uint8_t, 10> stlByteArr{};


int main()
{
	bool chk = false;

	// Test 1:
	chk = std::is_array<typeof(byteArr)>::value;		// TRUE!

	cout << "'byteArr' is " << (chk?" ":"not") << " an array type" << endl;   // True

	// Test 2:
	chk = std::is_array<typeof(myStr)>::value;			// FALSE - is a <class> type!

	cout << "'myStr' is " << (chk?" ":"not") << " an array type" << endl;

	// Test 3:
	chk = std::is_array<typeof(myArr)>::value;		// TRUE!

	cout << "'myArr' is " << (chk?" ":"not") << " an array type" << endl;

	// Test 4:
	chk = std::is_array<typeof(stlByteArr)>::value;		// FALSE - is a <class> type!

	cout << "'stlByteArr' is " << (chk?" ":"not") << " an array type" << endl;

	return 0;
}
