#ifndef __NN_ACC_SEQMULT__
#define __NN_ACC_SEQMULT__

#include "params/SeqMult.hh"
#include "nn_acc/SeqBase.hh"

class SeqMult : public SeqBase
{
  private:
  	/** 
    * Purelly virtual method coming from the base class.
    * This method perform the sequential multiplier operation.
    */
	void writeData();
  
  public:
    /** 
    * Constructor.
    */
    SeqMult(SeqMultParams *params);
    
    /** 
    * Desstructor.
    */
    ~SeqMult();
    
     /** 
     * Method needed by gem5 to start the simulation.
     */
    void startup();
};

#endif // __NN_ACC_SEQMULT__
