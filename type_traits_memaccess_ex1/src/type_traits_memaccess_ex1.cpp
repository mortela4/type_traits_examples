//============================================================================
// Name        : type_traits_ex1.cpp
// Author      : ml
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
//
#include "mem_access.cpp"
#include "mem_access.h"


using namespace std;
//
using namespace MemDefs;


typedef uint8_t   mem_8bit_t;
typedef uint16_t  mem_16bit_t;
typedef uint32_t  mem_32bit_t;
typedef uint64_t  mem_64bit_t;




int main()
{
	uint32_t myVar1 = 0xBBCCAADD;
	uint32_t& shadow1 = myVar1;
	//
	uint16_t myVar2 = 0xACDC;
	uint16_t& shadow2 = myVar2;
	//
	uint8_t myVar3 = 0x58;
	uint8_t& shadow3 = myVar3;



	auto myMemA = MemAccess<uint16_t>();		// Use defaults, but specify register size ...

	myMemA.MemInfo();

	myMemA.MemRead(shadow1);
	cout << "shadow1 = " << shadow1 << endl;
	myMemA.MemRead(shadow2);
	cout << "shadow2 = " << shadow2 << endl;

	myMemA.MemWrite((uint16_t)0xACDC);             // Cast will make this OK ...
	myMemA.MemRead(shadow2);
	cout << "shadow2 = " << shadow2 << endl;


	uint8_t byteVal = 0x72;
	myMemA.MemWrite(byteVal);
	myMemA.MemWrite(0x72);
	myMemA.MemRead(shadow2);
	cout << "shadow2 = " << shadow2 << endl;

	uint16_t wordVal = 0x7227;
	myMemA.MemWrite(wordVal);
	myMemA.MemRead(shadow2);
	cout << "shadow2 = " << shadow2 << endl;

	auto myMemB = MemAccess<uint32_t>(true, 0x40008C00);		// Use arguments ...

	myMemB.MemInfo();

	myMemB.MemRead(shadow1);
	cout << "shadow1 = " << shadow1 << endl;
	myMemB.MemRead(shadow2);
	cout << "shadow2 = " << shadow2 << endl;

	myMemB.MemWrite((uint32_t)0xACDCBEBE);             // Cast will make this OK ...
	myMemB.MemRead(shadow1);
	cout << "shadow1 = " << shadow1 << endl;

	myMemB.MemWrite(byteVal);
	myMemB.MemWrite(0x72);
	myMemB.MemRead(shadow1);
	cout << "shadow1 = " << shadow1 << endl;

	uint32_t longVal = 0x1234ABCD;
	myMemB.MemWrite(longVal);
	myMemB.MemRead(shadow1);
	cout << "shadow1 = " << shadow1 << endl;

	auto myMemC = MemAccess<uint8_t>();		// Use defaults, but specify register size ...

	myMemC.MemInfo();

	myMemC.MemRead(shadow3);
	cout << "shadow3 = " << int(shadow3) << endl;
	myMemC.MemWrite(byteVal);
	myMemC.MemRead(shadow3);
	cout << "shadow3 = " << int(shadow3) << endl;

	myMemC.MemWrite((uint8_t)0xA6);		// Need explicit cast to make this OK ...
	myMemC.MemWrite(shadow1);
	myMemC.MemRead(shadow2);
	myMemC.MemRead(shadow3);
	cout << "shadow3 = " << int(shadow3) << endl;

	return 0;
}
