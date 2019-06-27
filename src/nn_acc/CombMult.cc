
#include "nn_acc/CombMult.hh"
#include "debug/CombMult.hh"

CombMult::CombMult(CombMultParams *params) :
	CombBase(params)
{
}

CombMult::~CombMult() {
}

void CombMult::writeData() {
	CombBaseData result = 1;
    for (int i = 0; i < _slave.size(); i++) {
        if (hasData(&_slave[i])) {
			result = result * getData(&_slave[i]);
			popData(&_slave[i]);
		}
    }
    
    DPRINTF(CombMult, "Master %s writing the multplier result %d\n", _master[0].name(), result);
    _master[0].newData(result);
}

void CombMult::startup() {
}

CombMult* CombMultParams::create() {
  return new CombMult(this);
}
