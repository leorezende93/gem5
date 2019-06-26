
from m5.params import *
from m5.objects.MemObject import MemObject

class CombBase(MemObject):
    type = 'CombBase'
    abstract = True
    cxx_header = "nn_acc/CombBase.hh"

    slave = VectorSlavePort("Slave ports of this object")
    master = VectorMasterPort("Master ports of this object")

    latency = VectorParam.Latency([],"Latency of this object")
