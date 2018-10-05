//============================================================================
// Name        : type_traits_ex1.cpp
// Author      : ml
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
//
#include <type_traits>

using namespace std;


typedef uint8_t   reg_8bit_t;
typedef uint16_t  reg_16bit_t;
typedef uint32_t  reg_32bit_t;
typedef uint64_t  reg_64bit_t;


template<typename R>
R RegRead(auto& outval)
{
	auto regVal = 0x55CCU;

	if (std::is_same<typeof(outval), R>::value)
	{
		cout << "Same type - assignment is OK" << endl;

		return regVal;
	}
	else
	{
		cout << "Wrong type - assignment will fail!" << endl;

		return 0U;
	}
}

uint16_t RegRead16bit(auto& outval)
{
	uint16_t regVal = 0xABCDU;

	if (std::is_same<uint16_t, typeof(outval)>::value)
	{
		cout << "Same type - assignment is OK" << endl;
		outval = regVal;
		return regVal;
	}
	else
	{
		cout << "Wrong type - assignment will fail!" << endl;
		outval = 0;
		return 0U;
	}
}

uint16_t RegRead32bit(auto& outval)
{
	uint32_t regVal = 0xABCDU;

	if (std::is_same<typeof(regVal), typeof(outval)>::value)
	{
		cout << "Same type - assignment is OK" << endl;
		outval = regVal;
		return regVal;
	}
	else
	{
		cout << "Wrong type - assignment will fail!" << endl;
		outval = 0;
		return 0U;
	}
}


int main()
{
	uint32_t myVar1 = 0xBBCCAADD;
	uint32_t& shadow1 = myVar1;
	uint16_t myVar2 = 0xACDC;
	uint16_t& shadow2 = myVar2;

	RegRead<uint16_t>(shadow1);
	cout << "shadow1 = " << shadow1 << endl;
	RegRead<uint16_t>(shadow2);
	cout << "shadow2 = " << shadow2 << endl;

	// Simpler? More expressive??
	RegRead16bit(shadow1);
	cout << "shadow1 = " << shadow1 << endl;
	RegRead32bit(shadow2);
	cout << "shadow2 = " << shadow2 << endl;
	RegRead16bit(shadow2);
	cout << "shadow2 = " << shadow2 << endl;

	return 0;
}
