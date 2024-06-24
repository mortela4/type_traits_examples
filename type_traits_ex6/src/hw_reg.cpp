#include <iostream>
//
#include <type_traits>
//
#include "hw_reg.h"


namespace HwDefs
{
	using namespace std;

	template <class T, bool writable>
	HwReg<T, writable>::HwReg(uint32_t addr)
    {
    	isReadonly = !writable;
    	regAddr = addr;
    	regVal = (T)0U;
    }


	template <class T, bool writable>
    void HwReg<T, writable>::RegInfo(void)
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

	template <class T, bool writable>
    bool HwReg<T, writable>::RegRead(auto& outval)
    {
    	// static_assert(sizeof(T) == sizeof(outval), "Size of 'outval' type does not match size of register!");            // OK
    	// static_assert(std::is_same<__typeof__(outval), T>::value, "Type of 'outval' does not match type of register!");     // Better (??)
    	// static_assert (std::is_same<decltype(inval), T>::value);    // Won't work --> 'is_same<int&, int>::value = FALSE' !!

    	static_assert (std::is_same<std::remove_reference_t<decltype(outval)>, T>::value);    // Best!! (no??)

		cout << "Same type - assignment is OK" << endl;
		outval = regVal;

		return true;
    }

	template <class T, bool writable>
    bool HwReg<T, writable>::RegWrite(auto inval)
    {
		static_assert(writable, "Register is READONLY - cannot WRITE to it!");		// First test: WRITABLE register?

		static_assert (std::is_same<decltype(inval), T>::value);					// Second test: WRITE-variable of same type as register?

		HwReg::regVal = inval;
    	cout << "WRITE: regVal is now = 0x" << hex << HwReg::regVal << endl;

    	return true;
    }


}
