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


template <class T>
class HwReg
{
    T regVal;
    uint32_t regAddr;
    bool isReadonly;

  public:
    HwReg(bool writable=true, uint32_t addr=0xFFFFFFFF)
    {
    	isReadonly = !writable;
    	regAddr = addr;
    	regVal = (T)0U;
    }
    ~HwReg(){}

    void RegInfo(void)
    {
    	cout << "Register of size " << sizeof(T) << " bytes, at address=0x" << hex << regAddr << endl;

    	if (isReadonly)
    	{
    		cout << "Register is READONLY!" << endl;
    	}
    	else
    	{
    		cout << "Register is writable." << endl;
    	}
    }

    bool RegRead(auto& outval)
    {
    	if (std::is_same<typeof(outval), T>::value)
    	{
    		cout << "Same type - assignment is OK" << endl;
    		outval = regVal;

    		return true;
    	}
    	else
    	{
    		cout << "Wrong type - assignment will fail!" << endl;

    		return false;
    	}
    }

    bool RegWrite(auto inval)
    {
    	if (isReadonly)
    	{
    		cout << "Register is READONLY - cannot WRITE to it!" << endl;

    		return false;
    	}

    	if (std::is_same<typeof(inval), T>::value)
    	{
    		cout << "Same type - setting value to register is OK" << endl;
    		regVal = inval;
    		cout << "WRITE: regVal is now = 0x" << hex << regVal << endl;

    		return true;
    	}
    	else
    	{
    		cout << "Wrong type - WRITE to register will cause ERROR!" << endl;

    		return false;
    	}
    }

};


int main()
{
	uint32_t myVar1 = 0xBBCCAADD;
	uint32_t& shadow1 = myVar1;
	uint16_t myVar2 = 0xACDC;
	uint16_t& shadow2 = myVar2;

	HwReg<uint16_t> myRegA = HwReg<uint16_t>();		// Use defaults, but specify register size ...

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
