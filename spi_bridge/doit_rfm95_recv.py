from pwn import *
from rfm95 import *

mode_names = {
    0: "Sleep",
    1: "StdBy",
    2: "FSTx",
    3: "Tx",
    4: "FSRx",
    5: "Rx",
    6: "Reserved",
    7: "Reserved"
}

if __name__ == '__main__':
    r = serialtube("/dev/ttyUSB0", 9600, stopbits=2)
    r.send("?")
    r.recvuntil("EFM32HG309 SPI LEUART BRIDGE\n");
    rfm95 = RFM95(r)
    '''
    rfm95_reset()
    rfm95_write_reg(REG_OPMODE, (1 << 7))
    set_mode(MODE_SLEEP)
    rfm95_dump_regs()
    print 'freq:', hex(rfm95_read_freq())
    # rfm95_write_memory(0, "HELLO, WORLD!")
    # rfm95_dump_memory(0)
    '''

    rfm95.reset()
    rfm95.write_reg(REG_OPMODE, (1 << 7))
    # rfm95_dump_regs()
    rfm95.write_memory(0, 'A' * 16)
    rfm95.recv_packet(868000000, MC1_BW_125kHz, MC1_CR_45, MC2_SF_128)
    for n in range(0, 100000000):
        mem  = rfm95.read_memory(0, 16)
        mode = rfm95.read_reg(REG_OPMODE)
        print n, mem, mode_names[mode & ((1 << 3) - 1)]
