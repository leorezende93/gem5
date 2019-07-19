#ifndef __NN_ACC_SEQADD__
#define __NN_ACC_SEQADD__

#include "params/SeqAdd.hh"
#include "nn_acc/SeqBase.hh"

class SeqAdd : public SeqBase
{
  private:
  	/** 
    * Purelly virtual method coming from the base class.
    * This method perform the sequential adder operation.
    */
	void writeData();
  
  public:
    /** 
    * Constructor.
    */
    SeqAdd(SeqAddParams *params);
    
    /** 
    * Desstructor.
    */
    ~SeqAdd();
    
     /** 
     * Method needed by gem5 to start the simulation.
     */
    void startup();
};

#endif // __NN_ACC_SEQADD__
