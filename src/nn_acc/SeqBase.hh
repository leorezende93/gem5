#ifndef __NN_ACC_SEQBASE__
#define __NN_ACC_SEQBASE__

#include "params/SeqBase.hh"
#include "params/CombMult.hh"
#include "nn_acc/CombBase.hh"
#include "nn_acc/SeqBase.hh"
#include "mem/mem_object.hh"

class SeqBase : public CombBase
{
  protected:
    /// Clock period
    Tick _clockPeriod;
	
	/**
    * Method wrappered by the event. This method is used to
    * scheduled the sequential tasks.
    */
	void seqEvent();
	
	/// Especific sequential event
	EventWrapper<SeqBase, &SeqBase::seqEvent> _seqEvent;
	
  public:

    /** 
    * Constructor.
    */
    SeqBase(SeqBaseParams *params);
    
    /** 
    * Desstructor.
    */
    ~SeqBase();
    
    /**
    * Polimorphic method coming from base class. 
    * This method must be implemented to slave can read a data.
    * 
    * @param slave Pointer to slave.
    * @param data Data to be read by the slave.
    * @return A data from a slave.
    */
    void newData(CombSlavePort * slave, CombBaseData data);
    
     /** 
     * Method needed by gem5 to start the simulation.
     */
    void startup();
    
    /**
    * Purelly virtual method coming from base class. 
    * This method write the data in the master port.
    */
    void writeData();
    
    /**
    * Method to schedule sequential eventes
    */
    void scheduleSeqEvent();
    
    /**
    * Method used to discover the next clock edge.
    *
    * @return The next clock edge.
    */
    Tick nextClock();
};

#endif // __NN_ACC_SEQBASE__
