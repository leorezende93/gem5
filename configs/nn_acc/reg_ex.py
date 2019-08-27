import m5

from m5.objects import *

root = Root(full_system = False)

root.clk_domain = SrcClockDomain()
root.clk_domain.clock = '1GHz'
root.clk_domain.voltage_domain = VoltageDomain()

root.write = CombWrite(data = [10,20,30,40,50,60,70,80,90,100],latency = '4ns')
root.reg = SeqReg(latency = '0.1ns',clock='2ns')
root.read = CombRead(latency = '0ns')

root.read.slave = root.reg.master

root.reg.slave = root.write.master

m5.instantiate()

print("Beginning simulation!")
exit_event = m5.simulate()
print('Exiting @ tick {} because {}'
      .format(m5.curTick(), exit_event.getCause()))
