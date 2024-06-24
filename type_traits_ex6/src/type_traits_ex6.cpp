//============================================================================
// Name        : type_traits_ex6.cpp
// Author      : ml
// Version     :
// Copyright   : 
// Description : HW-register class test w. compile-time assertions.
//               Trying to write non-compatible variable types TO register,
//               or read FROM register into non-compatible variable type,
//               will fail compilation!
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

	auto myRegA = HwReg<uint16_t>();						// Use template and ctor defaults, but MUST specify register size ...
	auto myRegB = HwReg<uint32_t, true>(0x40008C00);		// Use both template and constructor arguments ...
	auto myRegC = HwReg<uint32_t, false>();					// Use ctor defaults - but template argument 'writable' specified = FALSE --> READONLY.

	myRegA.RegInfo();

/* Fails compilation!
	myRegA.RegRead(shadow1);
	cout << "shadow1 = " << shadow1 << endl;
*/

	(void)myRegA.RegRead(shadow2);
	cout << "shadow2 = " << shadow2 << endl;


	myRegA.RegWrite((uint16_t)0xACDC);             // Cast will make this OK ...
	myRegA.RegRead(shadow2);
	cout << "shadow2 = " << shadow2 << endl;

/* Fails compilation!
	uint8_t byteVal = 0x72;
	myRegA.RegWrite(byteVal);                         // Explicitly wrong size!
	myRegA.RegWrite(0x72);                            // Need cast ...
	myRegA.RegRead(shadow2);
	cout << "shadow2 = " << shadow2 << endl;
*/
	uint16_t wordVal = 0x7227;                        // DECLARED as 'uint16_t' - so OK ...
	(void)myRegA.RegWrite(wordVal);
	(void)myRegA.RegRead(shadow2);
	cout << "shadow2 = " << shadow2 << endl;

	/****************** Test with READ/WRITEeable 32-bit register ******************/
	myRegB.RegInfo();

	(void)myRegB.RegRead(shadow1);
	cout << "shadow1 = " << shadow1 << endl;
/*
	myRegB.RegRead(shadow2);							// READ into variable of wrong type - compilation fails!
	cout << "shadow2 = " << shadow2 << endl;
*/

	(void)myRegB.RegWrite((uint32_t)0xACDCBEBE);             // Cast will make this OK ...
	(void)myRegB.RegRead(shadow1);
	cout << "shadow1 = " << shadow1 << endl;

/*
	myRegB.RegWrite(byteVal);							// Explicitly wrong size!
	myRegB.RegWrite(0x72);								// Need cast ...
	myRegB.RegRead(shadow1);
	cout << "shadow1 = " << shadow1 << endl;
*/

	/****************** Test with READONLY 32-bit register ******************/
	myRegC.RegInfo();

	// uint32_t longVal = 0x1234ABCD;
	// (void)myRegC.RegWrite(longVal);					// Won't compile - register is READONLY! (Cannot WRITE ...)
	(void)myRegC.RegRead(shadow1);
	cout << "shadow1 = " << shadow1 << endl;

	return 0;
}
