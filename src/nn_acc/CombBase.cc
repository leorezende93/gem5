
#include "nn_acc/CombBase.hh"
#include "debug/CombBase.hh"

CombBase::CombBase(CombBaseParams *params) :
    MemObject(params),
    _combEvent(* this)
{
    for (int i = 0; i < params->port_master_connection_count; ++i) {
        _master.emplace_back(name() + csprintf(".master[%d]", i), i, this);
    }
    for (int i = 0; i < params->port_slave_connection_count; ++i) {
        _slave.emplace_back(name() + csprintf(".slave[%d]", i), i, this);
    }
    for (int i = 0; i < params->latency.size(); ++i) {
        _latency.push_back(params->latency[i]);
    }
    
    for (int i = 0; i < _slave.size(); i++) {
		_lastData[&_slave[i]] = 0;
	}
	
}

CombBase::~CombBase() {
    /**
    for(int i = 0 ; i < _data.size() ; i++) {
        delete _data[i];
    }
    */
}

Port & CombBase::getPort(const std::string &if_name, PortID idx) {
    // This is the name from the Python SimObject declaration in CombBase.py
    if (if_name == "master" && idx < _master.size()) {
        // We should have already created all of the ports in the constructor
        return _master[idx];
    } else if (if_name == "slave" && idx < _slave.size()) {
        // We should have already created all of the ports in the constructor
        return _slave[idx];
    } else {
        // pass it along to our super class
        return MemObject::getPort(if_name, idx);
    }
}

void CombBase::tryScheduleNext() {   
   int schedule_flag = 0;
   
   for (int i = 0; i < _slave.size(); ++i) {
	   if(_data[&_slave[i]].size() > 0) {
			schedule_flag = 1;
	   }
   }
   
   for (int i = 0; i < _slave.size(); ++i) {
	   if (schedule_flag && !_combEvent.scheduled()) {
		  DPRINTF(CombBase, "Slave %s schduling task\n",_slave[i].name());
		  if ((_data[&_slave[i]].begin()->first + _latency[0]) <= curTick()) {
			schedule(_combEvent, curTick());
		  } else {
			schedule(_combEvent, _data[&_slave[i]].begin()->first + _latency[0]);
		  }
	   }
   }
}

void CombBase::newData(CombSlavePort * slave, CombBaseData data) {
    DPRINTF(CombBase, "Slave %s reading the data %d\n",slave->name(),data);
    for (int i = 0; i < _slave.size(); ++i) {
        if(slave == &_slave[i]) {
            _lastData[slave] = data;
            if ( _data[slave].find(curTick()) == _data[slave].end()) {
				_data[slave].insert(std::make_pair(curTick(),data));
				for (int i = 0; i < _slave.size(); i++) { 
					if (&_slave[i] != slave) {
						_data[&_slave[i]].insert(std::make_pair(curTick(),_lastData[&_slave[i]]));
					}
				}
			} else {
				_data[slave][curTick()] = data;
			}
            break;
        }
    }
	tryScheduleNext();
}

void CombBase::combEvent() {
	writeData();
	tryScheduleNext();
}

bool CombBase::hasData(CombSlavePort * slave) {
	DPRINTF(CombBase, "Slave %s verifying if it has some data\n",slave->name());
	if (_data[slave].size() > 0)
		return true;
	else
		return false;
}

CombBaseData CombBase::getData(CombSlavePort * slave) {
	DPRINTF(CombBase, "Slave %s getting data\n",slave->name());
	return _data[slave].begin()->second;
}

void CombBase::popData(CombSlavePort * slave) {
	DPRINTF(CombBase, "Slave %s erasing data\n",slave->name());
	_data[slave].erase(_data[slave].begin());
}

bool CombBase::hasSlave(CombSlavePort * slave) {
	DPRINTF(CombBase, "verifying if the slave list has the slave %s\n",slave->name());
	for (int i = 0;  i< _slave.size(); i++) {
		if ( &_slave[i] == slave)
			return true;
	}
	return false;
}

void CombSlavePort::newData(CombBaseData data) {
    _owner->newData(this, data);
}

void CombSlavePort::slaveUnbind() {
    _master = nullptr;
    _baseMasterPort = nullptr;
    _connected = false;
}

void CombSlavePort::slaveBind(CombMasterPort& master) {
    _master = &master;
    _baseMasterPort = &master;
    _connected = true;
    DPRINTF(CombBase,"Master %s binding slave\n",master.name());
}

void CombSlavePort::bind(Port &peer) {
}

void CombSlavePort::unbind() {
}

void CombMasterPort::newData(CombBaseData data) {
    _slave->newData(data);
}

void CombMasterPort::bind(Port &peerPort) {
    auto *slave = dynamic_cast<CombSlavePort *>(&peerPort);
    DPRINTF(CombBase,"Binding port %s and port %s\n",name(), peerPort.name());
    if (!slave) {
        panic("Attempt to bind port %s to non-slave port %s.",name(), peerPort.name());
    }
    _slave = slave;
    _baseSlavePort = slave;
    _connected = true;
    _slave->slaveBind(*this);
}

void CombMasterPort::unbind() {
    _slave->slaveUnbind();
    _slave = nullptr;
    _baseSlavePort = nullptr;
    _connected = false;
}

