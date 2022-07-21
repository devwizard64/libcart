/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                        Copyright (C) 2022 devwizard                        */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#ifndef __ED_H__
#define __ED_H__

#define ED_BASE_REG             0x08040000

#define ED_CFG_REG              0x0000
#define ED_STATUS_REG           0x0004
#define ED_DMA_LEN_REG          0x0008
#define ED_DMA_ADDR_REG         0x000C
#define ED_MSG_REG              0x0010
#define ED_DMA_CFG_REG          0x0014
#define ED_SPI_REG              0x0018
#define ED_SPI_CFG_REG          0x001C
#define ED_KEY_REG              0x0020
#define ED_SAV_CFG_REG          0x0024
#define ED_SEC_REG              0x0028
#define ED_VER_REG              0x002C

#define ED_CFG_CNT_REG          0x0040
#define ED_CFG_DAT_REG          0x0044
#define ED_MAX_MSG_REG          0x0048
#define ED_CRC_REG              0x004C

#define ED_DMA_SD_TO_RAM        1
#define ED_DMA_RAM_TO_SD        2
#define ED_DMA_FIFO_TO_RAM      3
#define ED_DMA_RAM_TO_FIFO      4

#define ED_CFG_SDRAM_OFF        (0 << 0)
#define ED_CFG_SDRAM_ON         (1 << 0)
#define ED_CFG_SWAP             (1 << 1)

#define ED_STATE_DMA_BUSY       (1 << 0)
#define ED_STATE_DMA_TOUT       (1 << 1)
#define ED_STATE_TXE            (1 << 2)
#define ED_STATE_RXF            (1 << 3)
#define ED_STATE_SPI            (1 << 4)

#define ED_SPI_SPD_50           (0 << 0)
#define ED_SPI_SPD_25           (1 << 0)
#define ED_SPI_SPD_LO           (2 << 0)
#define ED_SPI_SS               (1 << 2)
#define ED_SPI_WR               (0 << 3)
#define ED_SPI_RD               (1 << 3)
#define ED_SPI_CMD              (0 << 4)
#define ED_SPI_DAT              (1 << 4)
#define ED_SPI_8BIT             (0 << 5)
#define ED_SPI_1BIT             (1 << 5)

#define ED_KEY                  0x1234

#define __ed_reg_rd(reg)        __cart_rd(ED_BASE_REG|(reg))
#define __ed_reg_wr(reg, val)   __cart_wr(ED_BASE_REG|(reg), val)

#endif /* __ED_H__ */
