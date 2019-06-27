#ifndef __NN_ACC_COMBBASE__
#define __NN_ACC_COMBBASE__

#include "params/CombBase.hh"
#include "mem/mem_object.hh"

typedef unsigned int CombBaseData;

class CombBase;
class CombSlavePort;
class CombMasterPort;

class CombSlavePort : public BaseSlavePort
{
  private:
    /// The object that owns this object
    CombBase *_owner;
    /// The port connected to this port
    CombMasterPort *_master;

  public:
    /**
     * Constructor. Just calls the superclass constructor.
     */
    CombSlavePort(const std::string& name, int id, CombBase *owner) :
        BaseSlavePort(name, id), _owner(owner) { }

    void newData(CombBaseData data);
    void slaveUnbind();
    void slaveBind(CombMasterPort& master);
    void bind(Port &peer) override;
    void unbind() override;
};

class CombMasterPort : public BaseMasterPort
{
  private:
    /// The object that owns this object
    CombBase *_owner;
    /// The port connected to this port
    CombSlavePort *_slave;

  public:
    /**
     * Constructor. Just calls the superclass constructor.
     */
    CombMasterPort(const std::string& name, int id, CombBase *owner) :
        BaseMasterPort(name, id), _owner(owner) { }

    void newData(CombBaseData data);
    void bind(Port &peerPort) override;
    void unbind() override;
};

class CombBase : public MemObject
{
  protected:
    /// List of slaves
    std::vector<CombSlavePort> _slave;
    
    /// List of masters
    std::vector<CombMasterPort> _master;
    
    /// List of latencies
    std::vector<Tick> _latency;
	
	/// Map of tuple formed by the data and its tick indexed by the slaves
	std::map<CombSlavePort*, std::map<Tick, CombBaseData>> _data;
	
	/// Map of data indexed by the slaves
	std::map<CombSlavePort*, CombBaseData> _lastData;
	
	/**
    * Method wrappered by the event. This method is used to
    * scheduled the tasks.
    */
	void combEvent();
	
	/// Event to schedule
	EventWrapper<CombBase, &CombBase::combEvent> _combEvent;
	
  public:

    /** 
     * Constructor.
     */
    CombBase(CombBaseParams *params);
    
    /** 
     * Destructor.
     */
    ~CombBase();
    
    /**
    * Method to get the port.
    * 
    * @param if_name Name of the port.
    * @param idx Id of the poert.
    * @return A master or slave port.
    */
    Port &getPort(const std::string &if_name,
                  PortID idx=InvalidPortID) override;
    
    /**
    * Polimorphic method. This method must be implemented
    * to slave can read a data.
    * 
    * @param slave Pointer to slave.
    * @param data Data to be read by the slave.
    * @return A data from a slave.
    */
    virtual void newData(CombSlavePort * slave, CombBaseData data);
    
    /**
    * Method that perfomr tasks schedule. This method verify 
    * if the slaves have some data. Case yes, the method
    * perform the data schedule. 
    */
    void tryScheduleNext();
    
    /**
    * Helper method to verify if a slave has some data.
    *
    * @param slave Pointer to slave.
    * @return A boolean value indicating if the Slave presents some data.
    */
    bool hasData(CombSlavePort * slave);
    
    /**
    * Method to obtain a data from a slave
    *
    * @param slave Pointer to slave.
    * @return A data from a slave.
    */
    CombBaseData getData(CombSlavePort * slave);
    
    /**
    * Method to remove a data from a slave
    *
    * @param slave Pointer to slave.
    */
    void popData(CombSlavePort * slave);
    
    /**
    * Helper method to verify if a slave is present in the Slave
    * list.
    *
    * @param slave Pointer to slave.
    * @return A boolean value indicating if the Slave is present in the slave list.
    */
    bool hasSlave(CombSlavePort * slave);
    
    /**
    * Purelly virtual method. This method must be implemented to 
    * process the data comming from the Slaves.
    */
    virtual void writeData() = 0;
};


#endif // __NN_ACC_COMBBASE__
