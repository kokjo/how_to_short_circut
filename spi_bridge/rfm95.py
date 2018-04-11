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

    0x1d: "REG_MODEMCONFIG1",
    0x1e: "REG_MODEMCONFIG2",
    0x22: "REG_PAYLOAD_LENGTH",
}

OPMODE_LORA = 0x80

OPMODE_MODE_SLEEP = 0
OPMODE_MODE_STDBY = 1
OPMODE_MODE_FS_TX = 2
OPMODE_MODE_TX    = 3
OPMODE_MODE_FS_RX = 4
OPMODE_MODE_RX    = 5

MC1_BW_MASK = 0xf << 4
MC1_BW_7_8kHz = 0 << 4
MC1_BW_10_4kHz = 1 << 4
MC1_BW_15_6kHz = 2 << 4
MC1_BW_20_8kHz = 3 << 4
MC1_BW_31_25kHz = 4 << 4
MC1_BW_41_7kHz = 5 << 4
MC1_BW_62_5kHz = 6 << 4
MC1_BW_125kHz = 7 << 4
MC1_BW_250kHz = 8 << 4
MC1_BW_500kHz = 9 << 4

MC1_CR_MASK = 0x7 << 1
MC1_CR_45 = 1 << 1
MC1_CR_46 = 2 << 1
MC1_CR_47 = 3 << 1
MC1_CR_48 = 4 << 1

MC1_HEADERMODE_IMPLICIT = 1 << 0

MC2_SF_MASK = 0xf << 4
MC2_SF_64 = 6 << 4
MC2_SF_128 = 7 << 4
MC2_SF_256 = 8 << 4 
MC2_SF_512 = 9 << 4
MC2_SF_1024 = 10 << 4 
MC2_SF_2048 = 11 << 4
MC2_SF_4096 = 12 << 4

MC2_TX_CONTINUOUS = 1 << 3  
MC2_RX_PAYLOAD_CRC = 1 << 2

MC2_SYMB_TIMEOUT_MSB_MASK = 0x3 << 0

for key, value in reg_names.items():
    exec "%s = %d" % (value, key)

def reg_to_name(reg):
    return reg_names.get(reg, "REG_%02x" % reg)

class RFM95:
    def __init__(self, serial):
        self.serial = serial

    def reset(self):
        self.serial.send("rR");

    def spi_transfer(self, mosi):
        self.serial.send("\\")
        miso = ""
        for d in flat(mosi, word_size=8):
            self.serial.send(d.encode("hex"))
            miso += self.serial.recvn(2).decode("hex")
        self.serial.send("/")
        return miso

    def read_reg(self, reg):
        return u8(self.spi_transfer([(reg & 0x7f) | 0x00, 0])[1:])

    def write_reg(self, reg, val):
        return u8(self.spi_transfer([(reg & 0x7f) | 0x80, val])[1:])

    def read_fifo(self, size):
        return self.spi_transfer([0x00] + [0]*size)[1:]

    def write_fifo(self, data):
        return self.spi_transfer([0x80, data])[1:]

    def read_memory(self, addr, size):
        self.write_reg(REG_FIFO_ADDR, addr)
        return self.read_fifo(size)

    def write_memory(self, addr, data):
        self.write_reg(REG_FIFO_ADDR, addr)
        return self.write_fifo(data)

    def read_freq(self):
        msb = self.read_reg(REG_FRF_MSB)
        mid = self.read_reg(REG_FRF_MID)
        lsb = self.read_reg(REG_FRF_LSB)
        frf = (msb << 16) | (mid << 8) | (lsb << 0)
        return (frf*32000000)/(2**19)

    def write_freq(self, freq):
        frf = (freq*(2**19))/32000000
        self.write_reg(REG_FRF_MSB, (frf >> 16) & 0xff)
        self.write_reg(REG_FRF_MID, (frf >> 8) & 0xff)
        self.write_reg(REG_FRF_LSB, (frf >> 0) & 0xff)

    def dump_regs(self):
        for reg in reg_names.keys():
            print "%s: 0x%02x" % (reg_to_name(reg), self.read_reg(reg))

    def dump_memory(self, addr=0, size=256):
        print hexdump(self.read_memory(addr, size))

    def send_packet(self, freq, bw, cr, sf, data):
        self.write_reg(REG_OPMODE, (1 << 7) | 1)

        self.write_freq(freq)
        self.write_reg(REG_MODEMCONFIG1, bw | cr)
        self.write_reg(REG_MODEMCONFIG2, sf)

        # todo: setup power
        self.write_reg(REG_PACONFIG, 0xf2)
        self.write_reg(REG_PARAMP, 0x08)

        # todo: setup

        self.write_memory(0, data)
        self.write_reg(REG_TXBASE, 0)
        self.write_reg(REG_PAYLOAD_LENGTH, len(data))
        self.write_reg(REG_OPMODE, OPMODE_LORA | OPMODE_MODE_TX)

    def recv_packet(self, freq, bw, cr, sf):
        self.write_freq(freq)
        self.write_reg(REG_MODEMCONFIG1, bw | cr)
        self.write_reg(REG_MODEMCONFIG2, sf)
        self.write_reg(REG_PACONFIG, 0x83)
        self.write_reg(REG_RXBASE, 0)
        self.write_reg(REG_OPMODE, OPMODE_LORA | OPMODE_MODE_RX)

    
