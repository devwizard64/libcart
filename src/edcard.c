/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "sd.h"
#include "ed.h"
#include "edcard.h"

int __ed_spi(int val)
{
    __cart_wr(ED_SPI_REG, val);
    while (__cart_rd(ED_STATUS_REG) & ED_STATE_SPI);
    return __cart_rd(ED_SPI_REG);
}

int __ed_sd_cmd(int cmd, u32 arg)
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
    __sd_resp[0] = 0xFF;
    sd_mode(SD_CMD_RD, SD_CMD_1b);
    n = 2048;
    while (__sd_resp[0] & 0xC0)
    {
        if (--n == 0) return -1;
        __sd_resp[0] = sd_cmd_rd(__sd_resp[0]);
    }
    n = !__sd_type ?
        cmd == CMD8 || cmd == CMD58 ? 5 : 1 :
        cmd == CMD2 || cmd == CMD9 ? 17 : 6;
    sd_mode(SD_CMD_RD, SD_CMD_8b);
    for (i = 1; i < n; i++) __sd_resp[i] = sd_cmd_rd(0xFF);
    return !__sd_type ? (__sd_resp[0] & 4) : 0;
}

int __ed_sd_close(int flag)
{
    int n;
    if (!__sd_type && flag)
    {
        sd_mode(SD_DAT_WR, SD_DAT_8b);
        sd_dat_wr(0xFD);
        sd_dat_wr(0xFF);
    }
    else
    {
        if (sd_cmd(CMD12, 0) < 0) return -1;
    }
    sd_mode(SD_DAT_RD, SD_DAT_8b);
    n = 65536;
    do
    {
        if (--n == 0) break;
    }
    while ((sd_dat_rd() & 0xFF) != 0xFF);
    return 0;
}
