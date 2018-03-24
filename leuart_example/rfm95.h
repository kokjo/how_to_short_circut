#ifndef _RFM95_H_
#define _RFM95_H_

#include <stdint.h>

uint8_t rfm95_read_reg(uint8_t reg);
uint8_t rfm95_write_reg(uint8_t reg, uint8_t val);
void rfm95_read_fifo(uint8_t *data, size_t len);
void rfm95_write_fifo(uint8_t *data, size_t len);
void rfm95_read_memory(uint8_t addr, uint8_t *data, size_t len);
void rfm95_write_memory(uint8_t addr, uint8_t *data, size_t len);
void rfm95_dump_regs();
void rfm95_init();

#define RFM95_SS_PIN        (PB11)
#define RFM95_RST_PIN       (PB14)

#define RFM95_FIFO             (0x00)
#define RFM95_OPMODE           (0x01)
#define RFM95_RESERVED0        (0x02)
#define RFM95_RESERVED1        (0x03)
#define RFM95_RESERVED2        (0x04)
#define RFM95_RESERVED3        (0x05)
#define RFM95_FRF_MSB          (0x06)
#define RFM95_FRF_MID          (0x07)
#define RFM95_FRF_LSB          (0x08)
#define RFM95_PACONFIG         (0x09)
#define RFM95_PARAMP           (0x0a)
#define RFM95_OCP              (0x0b)
#define RFM95_LNA              (0x0c)

#define RFM95_FIFO_ADDR          (0x0d)
#define RFM95_RXBASE             (0x0e)
#define RFM95_TXBASE             (0x0f)
#define RFM95_RXCURBASE          (0x10)
#define RFM95_IRQMASK            (0x11)
#define RFM95_IRQ                (0x12)
#define RFM95_RX_BYTES           (0x13)
#define RFM95_VALID_HDR_CNT_MSB  (0x14)
#define RFM95_VALID_HDR_CNT_LSB  (0x15)
#define RFM95_VALID_PKT_CNT_MSB  (0x16)
#define RFM95_VALID_PKT_CNT_LSB  (0x17)
#define RFM95_MODEM_STATUS       (0x18)
#define RFM95_PKT_SNR            (0x19)
#define RFM95_PKT_RSSI           (0x1a)
#define RFM95_RSSI               (0x1b)
#define RFM95_HOPCHANNEL         (0x1c)
#define RFM95_MODEM_CONFIG1      (0x1d)
#define RFM95_MODEM_CONFIG2      (0x1e)
#define RFM95_SYMB_TIMEOUT       (0x1f)
#define RFM95_PREAMBLE_MSB       (0x20)
#define RFM95_PREAMBLE_LSB       (0x21)
#define RFM95_PAYLOAD_LENGTH     (0x22)
#define RFM95_PAYLOAD_MAXLENGTH  (0x23)

#define RFM95_OPMODE_LORA             (1 << 7)
#define RFM95_OPMODE_ACCESS_SHARED    (1 << 6)
#define RFM95_OPMODE_LFMODE           (1 << 3)
#define RFM95_OPMODE_SLEEP            (0 << 0)
#define RFM95_OPMODE_STANDBY          (1 << 0)
#define RFM95_OPMODE_FSTX             (2 << 0)
#define RFM95_OPMODE_TX               (3 << 0)
#define RFM95_OPMODE_FSRX             (4 << 0)
#define RFM95_OPMODE_RXCONTINUOUS     (5 << 0)
#define RFM95_OPMODE_RX               (6 << 0)
#define RFM95_OPMODE_CAD              (7 << 0)

#define RFM95_PACONFIG_BOOST          (1 << 7)
#define RFM95_PACONFIG_MAXPOWER(x)    (((x) & 0x7) << 4)
#define RFM95_PACONFIG_OUTPUTPOWER(x) (((x) & 0xf) << 0)

#define RFM95_PARAMP_3_4MS            (0x00)
#define RFM95_PARAMP_2MS              (0x01)
#define RFM95_PARAMP_1MS              (0x02)
#define RFM95_PARAMP_500US            (0x03)
#define RFM95_PARAMP_250US            (0x04)
#define RFM95_PARAMP_125US            (0x05)
#define RFM95_PARAMP_100US            (0x06)
#define RFM95_PARAMP_62US             (0x07)
#define RFM95_PARAMP_50US             (0x08)
#define RFM95_PARAMP_40US             (0x09)
#define RFM95_PARAMP_31US             (0x0a)
#define RFM95_PARAMP_25US             (0x0b)
#define RFM95_PARAMP_20US             (0x0c)
#define RFM95_PARAMP_15US             (0x0d)
#define RFM95_PARAMP_12US             (0x0e)
#define RFM95_PARAMP_10US             (0x0f)

#define RFM95_OCP_OCP_ON              (1 << 5)
#define RFM95_OCP_OCP_TRIM(x)         (((x) & 0xf) << 0)

#define RFM95_LNA_GAIN(x)             (((x) & 0x7) << 5)
#define RFM95_LNA_BOOST               (3 << 0)

#endif
