#ifndef HW_REG_H_
#define HW_REG_H_


namespace HwDefs
{

using namespace std;

template <class T>
class HwReg
{
    T regVal;
    uint32_t regAddr;
    bool isReadonly;

  public:
    HwReg(bool writable=true, uint32_t addr=0xFFFFFFFF);

    void RegInfo(void);

    bool RegRead(auto& outval);

    bool RegWrite(auto inval);

};


}


#endif /* HW_REG_H_ */
