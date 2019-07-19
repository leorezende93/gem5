
#include "nn_acc/SeqAdd.hh"
#include "debug/SeqAdd.hh"

SeqAdd::SeqAdd(SeqAddParams *params) :
	SeqBase(params)
{
}

SeqAdd::~SeqAdd() {
}

void SeqAdd::writeData() {
	CombBaseData result = 0;
    for (int i = 0; i < _slave.size(); i++) {
        if (_lastData.size() > 0) {
			result = result + _lastData[&_slave[i]];
		}
    }
    
    DPRINTF(SeqAdd, "Master %s writing the sequential sum result %d\n", _master[0].name(), result);
    _master[0].newData(result);
}

void SeqAdd::startup() {
}

SeqAdd* SeqAddParams::create() {
  return new SeqAdd(this);
}
