
from m5.params import *
from m5.objects.SeqBase import SeqBase

class SeqMult(SeqBase):
    type = 'SeqMult'
    cxx_header = "nn_acc/SeqMult.hh"    
    
