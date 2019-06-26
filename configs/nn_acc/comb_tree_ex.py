import m5

from m5.objects import *

root = Root(full_system = False)

root.clk_domain = SrcClockDomain()
root.clk_domain.clock = '1GHz'
root.clk_domain.voltage_domain = VoltageDomain()

root.write0 = CombWrite(data = [15,5,6,7],latency = "0.1us")
root.write1 = CombWrite(data = [30,4,7,8],latency = "0.1us")
root.write2 = CombWrite(data = [10,3,8,9],latency = "0.1us")
root.write3 = CombWrite(data = [50,2,9,1],latency = "0.1us")

root.read = CombRead(latency = '0us')

root.mult1 = CombMult(latency = '2us')
root.mult2 = CombMult(latency = '2us')
root.mult3 = CombMult(latency = '2us')

root.mult1.slave = root.write0.master
root.mult1.slave = root.write1.master

root.mult2.slave = root.write2.master
root.mult2.slave = root.write3.master

root.mult3.slave = root.mult1.master
root.mult3.slave = root.mult2.master

root.read.slave = root.mult3.master


m5.instantiate()

print("Beginning simulation!")
exit_event = m5.simulate()
print('Exiting @ tick {} because {}'
      .format(m5.curTick(), exit_event.getCause()))
