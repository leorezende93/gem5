#ifndef __NN_ACC_COMBADD__
#define __NN_ACC_COMBADD__

#include "params/CombAdd.hh"
#include "nn_acc/CombBase.hh"

class CombAdd : public CombBase
{
  private:
  
	 /** 
     * Purelly virtual method coming from the base class.
     * This method perform the adder operation.
     */
	void writeData();
  
  public:
     /** 
     * Constructor.
     */
    CombAdd(CombAddParams *params);
    
     /** 
     * Destructor.
     */
    ~CombAdd();
    
     /** 
     * Method needed by gem5 to start the simulation.
     */
    void startup();
};

#endif // __NN_ACC_COMBADD__
