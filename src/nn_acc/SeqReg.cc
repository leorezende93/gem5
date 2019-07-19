
#include "nn_acc/SeqReg.hh"
#include "debug/SeqReg.hh"

#include "mem/abstract_mem.hh"

SeqReg::SeqReg(SeqRegParams *params) :
	SeqBase(params)
{
}

SeqReg::~SeqReg() {
}

void SeqReg::startup() {
	readPkt(pkt);
}

void SeqReg::readPkt(PacketPtr pkt) {
	DPRINTF(SeqReg,"Received address %x",pkt->getAddr());
}

SeqReg* SeqRegParams::create() {
  return new SeqReg(this);
}
