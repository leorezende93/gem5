import m5

from m5.objects import *

root = Root(full_system = False)

root.clk_domain = SrcClockDomain()
root.clk_domain.clock = '1GHz'
root.clk_domain.voltage_domain = VoltageDomain()

root.write0 = CombWrite(data = 15,latency = '0.1us')
root.write1 = CombWrite(data = 30,latency = '0.1us')
root.read = CombRead(latency = '0.1us')
root.mult = CombMult(latency = '2us')
root.read.slave = root.mult.master
root.mult.slave = root.write0.master
root.mult.slave = root.write1.master

m5.instantiate()

print("Beginning simulation!")
exit_event = m5.simulate()
print('Exiting @ tick {} because {}'
      .format(m5.curTick(), exit_event.getCause()))
