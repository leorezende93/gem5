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
    std::vector<CombSlavePort> _slave;
    std::vector<CombMasterPort> _master;
    std::vector<Tick> _latency;
	std::map<CombSlavePort*, std::map<Tick, CombBaseData>> _data;
	std::map<CombSlavePort*, CombBaseData> _lastData;
	
	void combEvent();
	EventWrapper<CombBase, &CombBase::combEvent> _combEvent;
	
  public:

    /** constructor
     */
    CombBase(CombBaseParams *params);
    ~CombBase();
    Port &getPort(const std::string &if_name,
                  PortID idx=InvalidPortID) override;
    void newData(CombSlavePort * slave, CombBaseData data);
    void tryScheduleNext();
    virtual void writeData() = 0;
};


#endif // __NN_ACC_COMBBASE__
