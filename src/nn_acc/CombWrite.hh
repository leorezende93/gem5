#ifndef __NN_ACC_COMBWRITE__
#define __NN_ACC_COMBWRITE__

#include "params/CombWrite.hh"
#include "nn_acc/CombBase.hh"

class CombWrite : public CombBase
{
  private:	
	/// Auxiliar list to generate the values to be write
	std::vector<CombBaseData> _writeDataVector;
	
	/// Control used to know the number of elements to be write.		
	int n_of_iterations;
	
	/** 
    * Purelly virtual method coming from the base class.
    * This method write the values in the master port.
    */
	void writeData();
	
	/// Especific write event
	EventFunctionWrapper _writeEvent;
	
  public:
     /** 
     * Constructor.
     */
    CombWrite(CombWriteParams *params);
    
     /** 
     * Destructor.
     */
    ~CombWrite();
    
    /** 
    * Method needed by gem5 to start the simulation.
    */
    void startup();
};


#endif // __NN_ACC_COMBWRITE__
