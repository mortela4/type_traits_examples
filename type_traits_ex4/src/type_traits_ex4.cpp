//============================================================================
// Name        : type_traits_ex1.cpp
// Author      : ml
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
//
#include "hw_reg.h"
#include "hw_reg.cpp"


using namespace std;
//
using namespace HwDefs;


typedef uint8_t   reg_8bit_t;
typedef uint16_t  reg_16bit_t;
typedef uint32_t  reg_32bit_t;
typedef uint64_t  reg_64bit_t;




int main()
{
	uint32_t myVar1 = 0xBBCCAADD;
	uint32_t& shadow1 = myVar1;
	uint16_t myVar2 = 0xACDC;
	uint16_t& shadow2 = myVar2;

	auto myRegA = HwReg<uint16_t>();		// Use defaults, but specify register size ...

	myRegA.RegInfo();

	myRegA.RegRead(shadow1);
	cout << "shadow1 = " << shadow1 << endl;
	myRegA.RegRead(shadow2);
	cout << "shadow2 = " << shadow2 << endl;

	myRegA.RegWrite((uint16_t)0xACDC);             // Cast will make this OK ...
	myRegA.RegRead(shadow2);
	cout << "shadow2 = " << shadow2 << endl;


	uint8_t byteVal = 0x72;
	myRegA.RegWrite(byteVal);
	myRegA.RegWrite(0x72);
	myRegA.RegRead(shadow2);
	cout << "shadow2 = " << shadow2 << endl;

	uint16_t wordVal = 0x7227;
	myRegA.RegWrite(wordVal);
	myRegA.RegRead(shadow2);
	cout << "shadow2 = " << shadow2 << endl;

	auto myRegB = HwReg<uint32_t>(true, 0x40008C00);		// Use arguments ...

	myRegB.RegInfo();

	myRegB.RegRead(shadow1);
	cout << "shadow1 = " << shadow1 << endl;
	myRegB.RegRead(shadow2);
	cout << "shadow2 = " << shadow2 << endl;

	myRegB.RegWrite((uint32_t)0xACDCBEBE);             // Cast will make this OK ...
	myRegB.RegRead(shadow1);
	cout << "shadow1 = " << shadow1 << endl;

	myRegB.RegWrite(byteVal);
	myRegB.RegWrite(0x72);
	myRegB.RegRead(shadow1);
	cout << "shadow1 = " << shadow1 << endl;

	uint32_t longVal = 0x1234ABCD;
	myRegB.RegWrite(longVal);
	myRegB.RegRead(shadow1);
	cout << "shadow1 = " << shadow1 << endl;

	return 0;
}
