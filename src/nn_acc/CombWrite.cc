
#include "nn_acc/CombWrite.hh"
#include "debug/CombWrite.hh"

CombWrite::CombWrite(CombWriteParams *params) :
    CombBase(params),
    n_of_iterations(params->data.size()),
    _writeEvent([this]{ writeData(); }, name() + ".event")
{
	for (int i = 0; i < params->data.size(); i++) {
		_writeDataVector.push_back(params->data[i]);	
	}
}

CombWrite::~CombWrite() {
}

void CombWrite::startup() {	
	if(!_writeEvent.scheduled() && n_of_iterations > 0) {
		schedule(_writeEvent, curTick());
	}
}

CombWrite* CombWriteParams::create() {
    return new CombWrite(this);
}

void CombWrite::writeData(){
	n_of_iterations--;

	DPRINTF(CombWrite, "Master %s writing %d\n", _master[0].name(), _writeDataVector[n_of_iterations]);
	_master[0].newData(_writeDataVector[n_of_iterations]);

	if(n_of_iterations > 0) {
		schedule(_writeEvent, curTick() + _latency[0]);		
	}
}
