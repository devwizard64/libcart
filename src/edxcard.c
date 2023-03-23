/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "sd.h"
#include "edx.h"
#include "edxcard.h"

void __edx_sd_mode(u32 reg, int val)
{
    static u32 mode;
    if (mode != reg)
    {
        mode = reg;
        __cart_wr(EDX_SD_STATUS_REG, __sd_cfg);
        __cart_wr(reg, 0xFFFF);
        while (__cart_rd(EDX_SD_STATUS_REG) & EDX_SD_STA_BUSY);
    }
    __cart_wr(EDX_SD_STATUS_REG, __sd_cfg | val);
}

int __edx_sd_cmd_rd(void)
{
    __cart_wr(EDX_SD_CMD_RD_REG, 0xFFFF);
    while (__cart_rd(EDX_SD_STATUS_REG) & EDX_SD_STA_BUSY);
    return __cart_rd(EDX_SD_CMD_RD_REG);
}

void __edx_sd_cmd_wr(int val)
{
    __cart_wr(EDX_SD_CMD_WR_REG, val);
    while (__cart_rd(EDX_SD_STATUS_REG) & EDX_SD_STA_BUSY);
}

int __edx_sd_dat_rd(void)
{
    __cart_wr(EDX_SD_DAT_RD_REG, 0xFFFF);
    return __cart_rd(EDX_SD_DAT_RD_REG);
}

int __edx_sd_cmd(int cmd, u32 arg)
{
    int i;
    int n;
    char buf[6];
    buf[0] = cmd;
    buf[1] = arg >> 24;
    buf[2] = arg >> 16;
    buf[3] = arg >>  8;
    buf[4] = arg >>  0;
    buf[5] = __sd_crc7(buf);
    sd_mode(SD_CMD_WR, SD_CMD_8b);
    sd_cmd_wr(0xFF);
    for (i = 0; i < 6; i++) sd_cmd_wr(buf[i]);
    if (cmd == CMD18) return 0;
    sd_mode(SD_CMD_RD, SD_CMD_8b);
    __sd_resp[0] = sd_cmd_rd(0xFF);
    sd_mode(SD_CMD_RD, SD_CMD_1b);
    n = 2048;
    while (__sd_resp[0] & 0xC0)
    {
        if (--n == 0) return -1;
        __sd_resp[0] = sd_cmd_rd(__sd_resp[0]);
    }
    sd_mode(SD_CMD_RD, SD_CMD_8b);
    n = cmd == CMD2 || cmd == CMD9 ? 17 : 6;
    for (i = 1; i < n; i++) __sd_resp[i] = sd_cmd_rd(0xFF);
    return 0;
}

int __edx_sd_close(void)
{
    int n;
    if (sd_cmd(CMD12, 0) < 0) return -1;
    sd_mode(SD_DAT_RD, SD_DAT_4b);
    sd_dat_rd();
    sd_mode(SD_DAT_RD, SD_DAT_8b);
    sd_dat_rd();
    n = 65536;
    do
    {
        if (--n == 0) break;
    }
    while ((sd_dat_rd() & 0xFF) != 0xFF);
    return 0;
}
