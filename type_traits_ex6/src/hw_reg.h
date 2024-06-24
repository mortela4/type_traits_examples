#ifndef HW_REG_H_
#define HW_REG_H_


namespace HwDefs
{

using namespace std;

/**
 * @brief Templated HW-register class.
 * Static property and type-compatibility check at compile-time,
 * via 'std::static_assert(<condition>, <optional: error message>)'
 * @note Both TEMPLATE and CONSTRUCTOR *default* arguments
 * are specified here! (and NOT in the implementation)
 */
template <class T, bool writable = true>
class HwReg
{
    T regVal;
    uint32_t regAddr;
    bool isReadonly;

  public:
    HwReg(uint32_t addr=0xFFFFFFFF);

    void RegInfo(void);

    bool RegRead(auto& outval);

    bool RegWrite(auto inval);

};


}


#endif /* HW_REG_H_ */
