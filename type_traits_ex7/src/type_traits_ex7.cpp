//============================================================================
// Name        : type_traits_ex1.cpp
// Author      : ml
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdint.h>
//
#include "scaler.h"
#include "scaler.cpp"    // Hmm - because of template class (kan like gjerne ha implementasjon i .h-fila) ...

using namespace std;
//
using namespace HwDefs;


typedef uint8_t   reg_8bit_t;
typedef uint16_t  reg_16bit_t;
typedef uint32_t  reg_32bit_t;
typedef uint64_t  reg_64bit_t;


typedef struct
{
	int value;
} int_struct_t;


int main()
{
	auto scalerA = Scaler<int>("Volt");

	uint16_t intVal = 512U;
	scalerA.Scale(intVal, 12);
	scalerA.Scale(intVal, 10);
	scalerA.Scale(intVal, 8);    // Triggers warning (and exception possibly) ...

	auto scalerB = Scaler<float>("Fahrenheit");

	scalerB.Scale(0.25F);
	scalerB.Scale(1.5F);    	// Triggers warning (and exception possibly) ...

	auto scalerC = Scaler<float>("Celcius", 23.5F);		// Arg#2 for ctor is 'factor'(=scale factor) - range argument not supplied ...

	scalerC.Scale(0.25F);
	scalerC.Scale(1.5F);    	// Triggers warning (and exception possibly) ...

/*
	auto scalerD = Scaler<int_struct_t>("Ampere");  //  Does NOT compile!

	auto scalerE = Scaler<string>("Ampere");  // Does NOT compile!
*/

	auto scalerF = Scaler<float>("Celcius", 23.5F, 2.5F);		// Arg#2 for ctor is 'factor'(=scale factor), Arg#3 is range argument
	scalerF.Scale(0.25F);
	scalerF.Scale(1.5F);    	// Triggers warning (and exception possibly) ...

	return 0;
}
