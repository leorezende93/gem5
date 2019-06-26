
from m5.params import *
from m5.objects.CombBase import CombBase

class CombWrite(CombBase):
    type = 'CombWrite'
    cxx_header = "nn_acc/CombWrite.hh"

    data = VectorParam.Int("Data to be written")

