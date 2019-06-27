#ifndef __NN_ACC_COMBMULT__
#define __NN_ACC_COMBMULT__

#include "params/CombMult.hh"
#include "nn_acc/CombBase.hh"

class CombMult : public CombBase
{
  private:
  
	 /** 
     * Purelly virtual method coming from the base class.
     * This method perform the multiplier operation.
     */
	void writeData();
  
  public:
     /** 
     * Constructor.
     */
    CombMult(CombMultParams *params);
    
     /** 
     * Destructor.
     */
    ~CombMult();
    
     /** 
     * Method needed by gem5 to start the simulation.
     */
    void startup();
};

#endif // __NN_ACC_COMBMULT__
