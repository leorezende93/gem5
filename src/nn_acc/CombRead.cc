
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
		if(_data[&_slave[i]].size() > 0) {
			DPRINTF(CombRead, "Reading %d\n", _data[&_slave[i]].begin()->second);
			_data[&_slave[i]].erase(_data[&_slave[i]].begin());
		}
	}
}
