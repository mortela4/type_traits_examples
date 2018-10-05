#include "mem_access.h"

#include <iostream>
//
#include <type_traits>
//


namespace MemDefs
{
	using namespace std;

	template <class T>
	MemAccess<T>::MemAccess(bool writable, uint32_t addr)
    {
    	isReadonly = !writable;
    	memAddr = addr;
    	memVal = (T)0U;
    }


	template <class T>
    void MemAccess<T>::MemInfo(void)
    {
		if (sizeof(T) == 1)
		{
	    	cout << "Memory location of size " << sizeof(T) << " bytes, at address=0x" << hex << memAddr << endl;
		}
		else
		{
	    	cout << "Memory location of size " << sizeof(T) << " bytes, at address=0x" << hex << int(memAddr) << endl;
		}

    	if (isReadonly)
    	{
    		cout << "Memory location is READONLY!" << endl;
    	}
    	else
    	{
    		cout << "Memory location is writable." << endl;
    	}
    }

	template <class T>
    bool MemAccess<T>::MemRead(auto& outval)
    {
		bool status = true;

    	if (std::is_same<typeof(outval), T>::value)
    	{
    		cout << "Same type - assignment is OK" << endl;
    		outval = memVal;
    	}
    	else
    	{
    		if (sizeof(typeof(outval)) <= sizeof(T))
    		{
    			cout << "WARNING: variable has type smaller than memory location - will cause TRUNCATED READ!" << endl;
    			outval = memVal;
    		}
    		else
    		{
        		cout << "Wrong type (variable larger than location) - READ to memory location will cause ALIGNMENT ERROR!" << endl;
        		status = false;
    		}
    	}

    	return status;
    }

	template <class T>
    bool MemAccess<T>::MemWrite(auto inval)
    {
		bool status = true;

    	if (isReadonly)
    	{
    		cout << "Memory-location is READONLY - cannot WRITE to it!" << endl;
    		status = false;
    	}
    	else
    	{
        	if (std::is_same<typeof(inval), T>::value)
        	{
        		cout << "Same type - setting value to memister is OK" << endl;
        		MemAccess::memVal = inval;
        		cout << "WRITE: memVal is now = 0x" << hex << MemAccess::memVal << endl;
        	}
        	else
        	{
        		if (sizeof(typeof(inval)) <= sizeof(T))
        		{
        			cout << "WARNING: variable has type smaller than memory location - will cause PARTIAL WRITE!" << endl;
        			MemAccess::memVal = inval;
        		}
        		else
        		{
            		cout << "Wrong type - WRITE to memory location will cause OVERLAP (=alignment) ERROR!" << endl;
            		status = false;
        		}
        	}
    	}

    	return status;
    }


}
