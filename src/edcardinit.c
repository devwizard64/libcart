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

int ed_card_init(void)
{
    int i;
    int n;
    u32 rca;
    __cart_acs_get();
    __sd_type = 0;
    if ((__cart_rd(ED_VER_REG) & 0xFFFF) >= 0x116)
    {
        __cart_wr(ED_CFG_REG, ED_CFG_SDRAM_OFF);
        if (__cart_rd(0x10000024) == 0x20534420) __sd_type = 1;
        __cart_wr(ED_CFG_REG, ED_CFG_SDRAM_ON);
    }
    __sd_cfg = ED_SPI_SPD_LO;
    if (__sd_type) __sd_cfg |= ED_SPI_SS;
    sd_mode(SD_CMD_WR, SD_CMD_8b);
    for (i = 0; i < 10; i++) sd_cmd_wr(0xFF);
    sd_cmd(CMD0, 0);
    if (sd_cmd(CMD8, 0x1AA))
    {
        if (!__sd_type)
        {
            if (sd_cmd(CMD55, 0) < 0) {__cart_acs_rel(); return -1;}
            if (sd_cmd(ACMD41, 0x40300000) < 0)
            {
                n = 1024;
                do
                {
                    if (--n == 0) {__cart_acs_rel(); return -1;}
                    if (sd_cmd(CMD1, 0) < 0) {__cart_acs_rel(); return -1;}
                }
                while (__sd_resp[0] != 0);
            }
            else
            {
                n = 1024;
                do
                {
                    if (--n == 0) {__cart_acs_rel(); return -1;}
                    if (sd_cmd(CMD55, 0) < 0) {__cart_acs_rel(); return -1;}
                    if (__sd_resp[0] != 1) continue;
                    if (sd_cmd(ACMD41, 0x40300000) < 0)
                    {
                        __cart_acs_rel();
                        return -1;
                    }
                }
                while (__sd_resp[0] != 0);
            }
        }
        else
        {
            n = 1024;
            do
            {
                if (--n == 0) {__cart_acs_rel(); return -1;}
                if (sd_cmd(CMD55, 0) < 0) {__cart_acs_rel(); return -1;}
                if (sd_cmd(ACMD41, 0x40300000) < 0)
                {
                    __cart_acs_rel();
                    return -1;
                }
            }
            while (__sd_resp[1] == 0);
        }
        __sd_flag = 0;
    }
    else
    {
        if (!__sd_type)
        {
            n = 1024;
            do
            {
                if (--n == 0) {__cart_acs_rel(); return -1;}
                if (sd_cmd(CMD55, 0) < 0) {__cart_acs_rel(); return -1;}
                if (__sd_resp[0] != 1) continue;
                if (sd_cmd(ACMD41, 0x40300000) < 0)
                {
                    __cart_acs_rel();
                    return -1;
                }
            }
            while (__sd_resp[0] != 0);
            if (sd_cmd(CMD58, 0) < 0) {__cart_acs_rel(); return -1;}
        }
        else
        {
            n = 1024;
            do
            {
                if (--n == 0) {__cart_acs_rel(); return -1;}
                if (sd_cmd(CMD55, 0) < 0) {__cart_acs_rel(); return -1;}
                if (!(__sd_resp[3] & 1)) continue;
                sd_cmd(ACMD41, 0x40300000);
            }
            while (!(__sd_resp[1] & 0x80));
        }
        __sd_flag = __sd_resp[1] & 0x40;
    }
    if (!__sd_type)
    {
        __sd_cfg = ED_SPI_SPD_25;
    }
    else
    {
        if (sd_cmd(CMD2, 0) < 0) {__cart_acs_rel(); return -1;}
        if (sd_cmd(CMD3, 0) < 0) {__cart_acs_rel(); return -1;}
        rca =
            __sd_resp[1] << 24 |
            __sd_resp[2] << 16 |
            __sd_resp[3] <<  8 |
            __sd_resp[4] <<  0;
        if (sd_cmd(CMD9, rca) < 0) {__cart_acs_rel(); return -1;}
        if (sd_cmd(CMD7, rca) < 0) {__cart_acs_rel(); return -1;}
        if (sd_cmd(CMD55, rca) < 0) {__cart_acs_rel(); return -1;}
        if (sd_cmd(ACMD6, 2) < 0) {__cart_acs_rel(); return -1;}
        __sd_cfg = ED_SPI_SPD_50|ED_SPI_SS;
    }
    __cart_acs_rel();
    return 0;
}
