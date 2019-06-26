#ifndef __NN_ACC_COMBREAD__
#define __NN_ACC_COMBREAD__

#include "params/CombRead.hh"
#include "nn_acc/CombBase.hh"

class CombRead : public CombBase
{
  private:
    void writeData();
  
  public:
    CombRead(CombReadParams *params);
    ~CombRead();
    void startup();
};


#endif // __NN_ACC_COMBREAD__
