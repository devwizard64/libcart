/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#ifndef __EDCARD_H__
#define __EDCARD_H__

#define SD_CMD_RD       (ED_SPI_CMD|ED_SPI_RD)
#define SD_CMD_WR       (ED_SPI_CMD|ED_SPI_WR)
#define SD_DAT_RD       (ED_SPI_DAT|ED_SPI_RD)
#define SD_DAT_WR       (ED_SPI_DAT|ED_SPI_WR)

#define SD_CMD_8b       ED_SPI_8BIT
#define SD_CMD_1b       ED_SPI_1BIT
#define SD_DAT_8b       ED_SPI_8BIT
#define SD_DAT_1b       ED_SPI_1BIT

#define sd_mode(reg, val)   __cart_wr(ED_SPI_CFG_REG, __sd_cfg|(reg)|(val))
#define sd_cmd_rd(val)      __ed_spi((val) & 0xFF)
#define sd_cmd_wr(val)      __ed_spi((val) & 0xFF)
#define sd_dat_rd()         __ed_spi(0xFF)
#define sd_dat_wr(val)      __ed_spi((val) & 0xFF)
#define sd_cmd(cmd, arg)    __ed_sd_cmd(cmd, arg)
#define sd_close(flag)      __ed_sd_close(flag)

extern int __ed_spi(int val);
extern int __ed_sd_cmd(int cmd, u32 arg);
extern int __ed_sd_close(int flag);

#endif /* __EDCARD_H__ */
