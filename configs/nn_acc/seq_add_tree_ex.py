import m5

from m5.objects import *

root = Root(full_system = False)

root.clk_domain = SrcClockDomain()
root.clk_domain.clock = '1GHz'
root.clk_domain.voltage_domain = VoltageDomain()

root.write0 = CombWrite(data = [15,5,6,7],latency = "0.1ns")
root.write1 = CombWrite(data = [30,4,7,8],latency = "0.1ns")
root.write2 = CombWrite(data = [10,3,8,9],latency = "0.1ns")
root.write3 = CombWrite(data = [50,2,9,1],latency = "0.1ns")

root.read = CombRead(latency = '0us')

root.add1 = CombAdd(latency = '0.1ns')
root.add2 = CombAdd(latency = '0.1ns')
root.add3 = SeqAdd(latency = '0.1ns',clock='1ns')

root.add1.slave = root.write0.master
root.add1.slave = root.write1.master

root.add2.slave = root.write2.master
root.add2.slave = root.write3.master

root.add3.slave = root.add1.master
root.add3.slave = root.add2.master

root.read.slave = root.add3.master

m5.instantiate()

print("Beginning simulation!")
exit_event = m5.simulate()
print('Exiting @ tick {} because {}'
      .format(m5.curTick(), exit_event.getCause()))
