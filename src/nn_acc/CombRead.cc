
#include "nn_acc/CombRead.hh"
#include "debug/CombRead.hh"

CombRead::CombRead(CombReadParams *params) :
    CombBase(params)
{
}

CombRead::~CombRead() {
}

void CombRead::startup() {
}

CombRead* CombReadParams::create() {
  return new CombRead(this);
}

void CombRead::writeData(){
	for (int i = 0; i < _slave.size(); i++) {
		if(hasData(&_slave[i])) {
			DPRINTF(CombRead, "Reading %d from slave %s\n", getData(&_slave[i]),_slave[i].name());
			popData(&_slave[i]);
		}
	}
}
