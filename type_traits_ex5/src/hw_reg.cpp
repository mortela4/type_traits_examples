#include <iostream>
//
#include <type_traits>
//
#include "hw_reg.h"


namespace HwDefs
{
	using namespace std;

	template <class T>
	HwReg<T>::HwReg(bool writable, uint32_t addr)
    {
    	isReadonly = !writable;
    	regAddr = addr;
    	regVal = (T)0U;
    }


	template <class T>
    void HwReg<T>::RegInfo(void)
    {
    	cout << "Register of size " << sizeof(T) << " bytes, at address=0x" << hex << regAddr << endl;

    	if (isReadonly)
    	{
    		cout << "Register is READONLY!" << endl;
    	}
    	else
    	{
    		cout << "Register is writeable." << endl;
    	}
    }

	template <class T>
    bool HwReg<T>::RegRead(auto& outval)
    {
    	if (std::is_same<decltype(outval), T>::value)
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

	template <class T>
    bool HwReg<T>::RegWrite(auto inval)
    {
    	if (isReadonly)
    	{
    		cout << "Register is READONLY - cannot WRITE to it!" << endl;

    		return false;
    	}

    	if (std::is_same<decltype(inval), T>::value)
    	{
    		cout << "Same type - setting value to register is OK" << endl;
    		HwReg::regVal = inval;
    		cout << "WRITE: regVal is now = 0x" << hex << HwReg::regVal << endl;

    		return true;
    	}
    	else
    	{
    		cout << "Wrong type - WRITE to register will cause ERROR!" << endl;

    		return false;
    	}
    }


}
