
from m5.params import *
from m5.objects.SeqBase import SeqBase

class SeqReg(SeqBase):
    type = 'SeqReg'
    cxx_header = "nn_acc/SeqReg.hh"    
    
