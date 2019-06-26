
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
        if (_data[&_slave[i]].size() > 0) {
			result = result * _data[&_slave[i]].begin()->second;
			_data[&_slave[i]].erase(_data[&_slave[i]].begin());
		}
    }
    
    DPRINTF(CombMult, "Multiplying %d\n", result);
    _master[0].newData(result);
}

void CombMult::startup() {
}

CombMult* CombMultParams::create() {
  return new CombMult(this);
}
