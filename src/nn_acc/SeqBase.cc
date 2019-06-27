
#include "nn_acc/CombBase.hh"
#include "nn_acc/SeqBase.hh"
#include "debug/SeqBase.hh"

SeqBase::SeqBase (SeqBaseParams *params) :
	CombBase(params),
	_clockPeriod(params->clock),
	_seqEvent(* this)
{
	for (int i = 0; i < _slave.size(); i++) { 
		_lastData[&_slave[i]] = 0;	
	}	
}

SeqBase::~SeqBase() {
}

void SeqBase::newData(CombSlavePort * slave, CombBaseData data) {
	DPRINTF(SeqBase, "Slave %s reading the data %d\n",slave->name(),data);
	_lastData[slave] = data;
	scheduleSeqEvent();
}

void SeqBase::scheduleSeqEvent() {
	if (!_seqEvent.scheduled()) {
		  schedule(_seqEvent, nextClock());
	}
}

Tick SeqBase::nextClock() {
	Tick nextClock;
	
	DPRINTF(SeqBase, "Obtaining next clock edge\n");
	nextClock = (ceil((curTick() / _clockPeriod)) + 1)*_clockPeriod;
	return nextClock;
}

void SeqBase::seqEvent() {
	writeData();
}

void SeqBase::writeData() {
	for (int i = 0; i < _slave.size(); i++) {
		DPRINTF(SeqBase, "Slave %s wrinting data\n",_slave[i].name()); 
		_master[0].newData(_lastData[&_slave[i]]);	
	}	    
}

void SeqBase::startup() {
}
