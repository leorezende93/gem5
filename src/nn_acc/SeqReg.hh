#ifndef __NN_ACC_SEQREG__
#define __NN_ACC_SEQREG__

#include "params/SeqReg.hh"
#include "nn_acc/SeqBase.hh"

class SeqReg : public SeqBase
{
  private:
	PacketPtr pkt;
	
  public:
    /** 
    * Constructor.
    */
    SeqReg(SeqRegParams *params);
    
    /** 
    * Desstructor.
    */
    ~SeqReg();
    
     /** 
     * Method needed by gem5 to start the simulation.
     */
    void startup();
    void readPkt(PacketPtr pkt);

};

#endif // __NN_ACC_SEQREG__
