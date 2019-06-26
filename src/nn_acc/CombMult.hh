#ifndef __NN_ACC_COMBMULT__
#define __NN_ACC_COMBMULT__

#include "params/CombMult.hh"
#include "nn_acc/CombBase.hh"

class CombMult : public CombBase
{
  private:
	void writeData();
  
	std::map<CombSlavePort*, CombBaseData> _lastData;
  
  public:
    CombMult(CombMultParams *params);
    ~CombMult();
    void startup();
};

#endif // __NN_ACC_COMBMULT__
