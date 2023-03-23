/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#ifndef __EDXCARD_H__
#define __EDXCARD_H__

#define SD_CMD_RD       EDX_SD_CMD_RD_REG
#define SD_CMD_WR       EDX_SD_CMD_WR_REG
#define SD_DAT_RD       EDX_SD_DAT_RD_REG
#define SD_DAT_WR       EDX_SD_DAT_WR_REG

#define SD_CMD_8b       8
#define SD_CMD_1b       1
#define SD_DAT_32b      8
#define SD_DAT_16b      4
#define SD_DAT_8b       2
#define SD_DAT_4b       1
#define SD_DAT_1b       1

#define sd_mode(reg, val)   __edx_sd_mode(reg, val)
#define sd_cmd_rd(val)      __edx_sd_cmd_rd()
#define sd_cmd_wr(val)      __edx_sd_cmd_wr((val) & 0xFF)
#define sd_dat_rd()         __edx_sd_dat_rd()
#define sd_dat_wr(val)      __cart_wr(EDX_SD_DAT_WR_REG, (val) << 8 | 0xFF)
#define sd_cmd(cmd, arg)    __edx_sd_cmd(cmd, arg)
#define sd_close(flag)      __edx_sd_close()

extern void __edx_sd_mode(u32 reg, int val);
extern int __edx_sd_cmd_rd(void);
extern void __edx_sd_cmd_wr(int val);
extern int __edx_sd_dat_rd(void);
extern int __edx_sd_cmd(int cmd, u32 arg);
extern int __edx_sd_close(void);

#endif /* __EDXCARD_H__ */
