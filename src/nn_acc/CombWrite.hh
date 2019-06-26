#ifndef __NN_ACC_COMBWRITE__
#define __NN_ACC_COMBWRITE__

#include "params/CombWrite.hh"
#include "nn_acc/CombBase.hh"

class CombWrite : public CombBase
{
  private:	
	std::vector<CombBaseData> _writeDataVector;
			
	int n_of_iterations;
	
	void writeData();
		
	EventFunctionWrapper _writeEvent;
	
  public:
    CombWrite(CombWriteParams *params);
    ~CombWrite();
    void startup();
};


#endif // __NN_ACC_COMBWRITE__
