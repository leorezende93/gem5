
from m5.params import *
from m5.objects.CombBase import CombBase

class SeqBase(CombBase):
    type = 'SeqBase'
    abstract = True
    cxx_header = "nn_acc/SeqBase.hh"

    clock = Param.Latency('1ns',"Clock period of this object")
