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

int edx_card_wr_cart(u32 cart, u32 lba, u32 count)
{
    int i;
    int n;
    int resp;
    __cart_acs_get();
    if (!__sd_flag) lba *= 512;
    if (sd_cmd(CMD25, lba) < 0) {__cart_acs_rel(); return -1;}
    while (count-- > 0)
    {
        sd_mode(SD_DAT_WR, SD_DAT_8b);
        sd_dat_wr(0xFF);
        sd_dat_wr(0xF0);
        sd_mode(SD_DAT_WR, SD_DAT_16b);
        __cart_dma_rd(__cart_buf, cart, 512);
        __cart_dma_wr(__cart_buf, EDX_BASE_REG|EDX_SDIO_ARD_REG, 512);
        __sd_crc16((void *)__cart_buf, (void *)__cart_buf);
        __cart_dma_wr(__cart_buf, EDX_BASE_REG|EDX_SDIO_ARD_REG, 8);
        sd_mode(SD_DAT_WR, SD_DAT_4b);
        sd_dat_wr(0xFF);
        sd_mode(SD_DAT_RD, SD_DAT_4b);
        n = 1024;
        do
        {
            if (--n == 0) {__cart_acs_rel(); return -1;}
        }
        while (sd_dat_rd() & 1);
        resp = 0;
        for (i = 0; i < 3; i++) resp = resp << 1 | (sd_dat_rd() & 1);
        if (resp != 2) {__cart_acs_rel(); return -1;}
        n = 65536;
        do
        {
            if (--n == 0) {__cart_acs_rel(); return -1;}
        }
        while ((sd_dat_rd() & 0xFF) != 0xFF);
        cart += 512;
    }
    if (sd_close(1)) {__cart_acs_rel(); return -1;}
    __cart_acs_rel();
    return 0;
}
