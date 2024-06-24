#ifndef SCALER_H_
#define SCALER_H_

#include <variant>
#include <string>

namespace HwDefs
{

using namespace std;

template <class T>
class Scaler
{
  private:
    std::variant<long,double> raw;
    string unitOfMeasure;
    float scaleFactor;
    float fullRange;

    unsigned int PowerOfTwo(unsigned int exp)
    {
    	unsigned int result = 1;

        while(exp)
        {
        	result *= 2;
        	--exp;
        }

        return result;
    }

  public:
    Scaler(const string uom, const float factor=1.0F, const float range=1.0F);   // Factor is [unit/V]
    ~Scaler() = default;
    float Scale(const T inval, const int numBits=0);
    T GetRaw(void);
};


}


#endif /* SCALER_H_ */
