
#include "nn_acc/CombAdd.hh"
#include "debug/CombAdd.hh"

CombAdd::CombAdd(CombAddParams *params) :
	CombBase(params)
{
}

CombAdd::~CombAdd() {
}

void CombAdd::writeData() {
	CombBaseData result = 0;
    for (int i = 0; i < _slave.size(); i++) {
        if (hasData(&_slave[i])) {
			result = result + getData(&_slave[i]);
			popData(&_slave[i]);
		}
    }
    
    DPRINTF(CombAdd, "Master %s writing the sum result %d\n", _master[0].name(), result);
    _master[0].newData(result);
}

void CombAdd::startup() {
}

CombAdd* CombAddParams::create() {
  return new CombAdd(this);
}
