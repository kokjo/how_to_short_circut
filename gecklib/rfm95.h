#ifndef __HEADER_RFM95__
#define __HEADER_RFM95__

#include <stdint.h>
#include <stdlib.h>

struct rfm95_t {

    // frequency

    uint32_t freq;

    // modem config

    uint8_t  bw;
    uint8_t  cr;
    uint8_t  sf;
    uint8_t  power;

    // pins

    uint8_t  pin_ss;
    uint8_t  pin_rst;
};

void rfm95_update_config(struct rfm95_t *c);
uint8_t rfm95_recv(struct rfm95_t *c, uint8_t* msg);
void rfm95_send(struct rfm95_t *c, uint8_t* msg, uint8_t len);

uint8_t rfm95_read_reg(struct rfm95_t *c, uint8_t reg);
void rfm95_read_memory(struct rfm95_t *c, uint8_t addr, uint8_t *data, size_t len);

#define MC1_BW_MASK     (0xf << 4)
#define MC1_BW_7_8kHz   (0 << 4)
#define MC1_BW_10_4kHz  (1 << 4)
#define MC1_BW_15_6kHz  (2 << 4)
#define MC1_BW_20_8kHz  (3 << 4)
#define MC1_BW_31_25kHz (4 << 4)
#define MC1_BW_41_7kHz  (5 << 4)
#define MC1_BW_62_5kHz  (6 << 4)
#define MC1_BW_125kHz   (7 << 4)
#define MC1_BW_250kHz   (8 << 4)
#define MC1_BW_500kHz   (9 << 4)

#define MC1_CR_MASK  (0x7 << 1)
#define MC1_CR_45    (1 << 1)
#define MC1_CR_46    (2 << 1)
#define MC1_CR_47    (3 << 1)
#define MC1_CR_48    (4 << 1)

#define MC1_HEADERMODE_IMPLICIT (1 << 0)
#define MC2_SF_MASK (0xf << 4)
#define MC2_SF_64   (6 << 4)
#define MC2_SF_128  (7 << 4)
#define MC2_SF_256  (8 << 4)
#define MC2_SF_512  (9 << 4)
#define MC2_SF_1024 (10 << 4)
#define MC2_SF_2048 (11 << 4)
#define MC2_SF_4096 (12 << 4)

#define MC2_TX_CONTINUOUS         (1 << 3)
#define MC2_RX_PAYLOAD_CRC        (1 << 2)
#define MC2_SYMB_TIMEOUT_MSB_MASK (0x3 << 0)

// #define RFM95_SS_PIN        (PB11)
// #define RFM95_RST_PIN       (PB14)

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
#define RFM95_TXBASE             (0x0e)
#define RFM95_RXBASE             (0x0f)
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

#define RFM95_IRQMASK_RX_TIMEOUT_MASK          (1 << 7)
#define RFM95_IRQMASK_RX_DONE_MASK             (1 << 6)
#define RFM95_IRQMASK_PAYLOAD_CRC_ERROR_MASK   (1 << 5)
#define RFM95_IRQMASK_VALID_HEADER_MASK        (1 << 4)
#define RFM95_IRQMASK_TX_DONE_MASK             (1 << 3)
#define RFM95_IRQMASK_CAD_DONE_MASK            (1 << 2)
#define RFM95_IRQMASK_FHSS_CHANGE_CHANNEL_MASK (1 << 1)
#define RFM95_IRQMASK_CAD_DETECTED_MASK        (1 << 0)

#define RFM95_IRQ_RX_TIMEOUT          (1 << 7)
#define RFM95_IRQ_RX_DONE             (1 << 6)
#define RFM95_IRQ_PAYLOAD_CRC_ERROR   (1 << 5)
#define RFM95_IRQ_VALID_HEADER        (1 << 4)
#define RFM95_IRQ_TX_DONE             (1 << 3)
#define RFM95_IRQ_CAD_DONE            (1 << 2)
#define RFM95_IRQ_FHSS_CHANGE_CHANNEL (1 << 1)
#define RFM95_IRQ_CAD_DETECTED        (1 << 0)

#define RFM95_OPMODE_LONG_RANGE_MODE_MASK (1 << 7)
#define RFM95_OPMODE_MODE_MASK            ((1 << 3) - 1)

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
