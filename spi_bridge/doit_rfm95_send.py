from pwn import *

reg_names = {
    0: "REG_FIFO",
    1: "REG_OPMODE",
#    2: "REG_RESERVED0",
#    3: "REG_RESERVED1",
#    4: "REG_RESERVED2",
#    5: "REG_RESERVED3",
    6: "REG_FRF_MSB",
    7: "REG_FRF_MID",
    8: "REG_FRF_LSB",
    9: "REG_PACONFIG",
    10: "REG_PARAMP",
    11: "REG_OCP",
    12: "REG_LNA",
    13: "REG_FIFO_ADDR",
    14: "REG_TXBASE",
    15: "REG_RXBASE",
    16: "REG_RXCURBASE",
    17: "REG_IRQMASK",
    18: "REG_IRQ",
    19: "REG_RXBYTES",
}

for key, value in reg_names.items():
    exec "%s = %d" % (value, key)

r = serialtube("/dev/ttyUSB0", 9600)
r.send("?")
r.recvuntil("EFM32HG309 SPI LEUART BRIDGE\n");

def rfm95_reset():
    r.send("rR");

def reg_to_name(reg):
    return reg_names.get(reg, "REG_%02x" % reg)

def spi_transfer(mosi):
    r.send("\\")
    miso = ""
    for d in flat(mosi, word_size=8):
        r.send(d.encode("hex"))
        miso += r.recvn(2).decode("hex")
    r.send("/")
    return miso

def rfm95_read_reg(reg):
    return u8(spi_transfer([(reg & 0x7f) | 0x00, 0])[1:])

def rfm95_write_reg(reg, val):
    return u8(spi_transfer([(reg & 0x7f) | 0x80, val])[1:])

def rfm95_read_fifo(size):
    return spi_transfer([0x00] + [0]*size)[1:]

def rfm95_write_fifo(data):
    return spi_transfer([0x80, data])[1:]

def rfm95_dump_regs():
    for reg in reg_names.keys():
        print "%s: 0x%02x" % (reg_to_name(reg), rfm95_read_reg(reg))

def rfm95_read_freq():
    msb = rfm95_read_reg(REG_FRF_MSB)
    mid = rfm95_read_reg(REG_FRF_MID)
    lsb = rfm95_read_reg(REG_FRF_LSB)
    return (msb << 16) | (mid << 8) | (lsb << 0)

def rfm95_read_memory(addr, size):
    rfm95_write_reg(REG_FIFO_ADDR, addr)
    return rfm95_read_fifo(size)

def rfm95_write_memory(addr, data):
    rfm95_write_reg(REG_FIFO_ADDR, addr)
    return rfm95_write_fifo(data)

def rfm95_dump_memory(addr=0, size=256):
    print hexdump(rfm95_read_memory(addr, size))

rfm95_reset()
rfm95_write_reg(REG_OPMODE, (1 << 7))
print hex(rfm95_read_freq())
#rfm95_dump_regs()
rfm95_write_memory(0, "HELLO, WORLD!")
rfm95_dump_memory(16)
        
