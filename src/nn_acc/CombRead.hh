#ifndef __NN_ACC_COMBREAD__
#define __NN_ACC_COMBREAD__

#include "params/CombRead.hh"
#include "nn_acc/CombBase.hh"

class CombRead : public CombBase
{
  private:
	/** 
    * Purelly virtual method coming from the base class.
    * This method print the value coming from a master port.
    */
    void writeData();
  
  public:
     /** 
     * Constructor.
     */
    CombRead(CombReadParams *params);
    
     /** 
     * Destructor.
     */
    ~CombRead();
    
     /** 
     * Method needed by gem5 to start the simulation.
     */
    void startup();
};


#endif // __NN_ACC_COMBREAD__
