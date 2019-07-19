
#include "nn_acc/SeqMult.hh"
#include "debug/SeqMult.hh"

SeqMult::SeqMult(SeqMultParams *params) :
	SeqBase(params)
{
}

SeqMult::~SeqMult() {
}

void SeqMult::writeData() {
	CombBaseData result = 1;
    for (int i = 0; i < _slave.size(); i++) {
        if (_lastData.size() > 0) {
			result = result * _lastData[&_slave[i]];
		}
    }
    
    DPRINTF(SeqMult, "Master %s writing the sequential multplier result %d\n", _master[0].name(), result);
    _master[0].newData(result);
}

void SeqMult::startup() {
}

SeqMult* SeqMultParams::create() {
  return new SeqMult(this);
}
