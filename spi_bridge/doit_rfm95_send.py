from pwn import *
from rfm95 import *


r = serialtube("/dev/ttyUSB0", 9600, stopbits=2)
r.send("?")
r.recvuntil("EFM32HG309 SPI LEUART BRIDGE\n");


rfm95 = RFM95(r)
rfm95.reset()
rfm95.write_reg(REG_OPMODE, (1 << 7))
rfm95.dump_regs()
for i in range(100):
    rfm95.send_packet(868000000, MC1_BW_125kHz, MC1_CR_45, MC2_SF_128, "Hello %d" % i) 
    rfm95.dump_regs()
    rfm95.dump_memory(0, 16)
