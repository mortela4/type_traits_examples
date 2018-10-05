#ifndef MEM_ACCESS_H_
#define MEM_ACCESS_H_

#include <stdint.h>


namespace MemDefs
{

using namespace std;

template <class T>
class MemAccess
{
    T memVal;
    uint32_t memAddr;
    bool isReadonly;

  public:
    MemAccess(bool writable=true, uint32_t addr=0xFFFFFFFF);

    void MemInfo(void);

    bool MemRead(auto& outval);

    bool MemWrite(auto inval);

};


}


#endif /* MEM_ACCESS_H_ */
