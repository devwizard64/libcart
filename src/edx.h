/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#ifndef __EDX_H__
#define __EDX_H__

#define EDX_BASE_REG            0x1F800000
#define EDX_EDID_REG            (EDX_BASE_REG+0x0014)

#define EDX_SYS_CFG_REG         (EDX_BASE_REG+0x8000)
#define EDX_KEY_REG             (EDX_BASE_REG+0x8004)
#define EDX_DMA_STA_REG         (EDX_BASE_REG+0x8008)
#define EDX_DMA_ADDR_REG        (EDX_BASE_REG+0x8008)
#define EDX_DMA_LEN_REG         (EDX_BASE_REG+0x800C)
#define EDX_SDIO_REG            (EDX_BASE_REG+0x8020)
#define EDX_SDIO_ARD_REG        (EDX_BASE_REG+0x8200)
#define EDX_SD_CMD_RD_REG       (EDX_BASE_REG+0x8020)
#define EDX_SD_CMD_WR_REG       (EDX_BASE_REG+0x8024)
#define EDX_SD_DAT_RD_REG       (EDX_BASE_REG+0x8028)
#define EDX_SD_DAT_WR_REG       (EDX_BASE_REG+0x802C)
#define EDX_SD_STATUS_REG       (EDX_BASE_REG+0x8030)

#define EDX_DMA_STA_BUSY        0x0001
#define EDX_DMA_STA_ERROR       0x0002
#define EDX_DMA_STA_LOCK        0x0080

#define EDX_SD_CFG_BITLEN       0x000F
#define EDX_SD_CFG_SPD          0x0010
#define EDX_SD_STA_BUSY         0x0080

#define EDX_CFG_SDRAM_ON        0x0000
#define EDX_CFG_SDRAM_OFF       0x0001
#define EDX_CFG_REGS_OFF        0x0002
#define EDX_CFG_SWAP            0x0004

#define EDX_KEY                 0xAA55

#endif /* __EDX_H__ */
