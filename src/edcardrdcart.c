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

int ed_card_rd_cart(u32 cart, u32 lba, u32 count)
{
    int i;
    int n;
    u32 resp;
    __cart_acs_get();
    if (!__sd_flag) lba *= 512;
    if (sd_cmd(CMD18, lba) < 0) {__cart_acs_rel(); return -1;}
    if (cart & 0x7FF)
    {
        while (count-- > 0)
        {
            sd_mode(SD_DAT_RD, SD_DAT_1b);
            n = 65536;
            do
            {
                if (--n == 0) {__cart_acs_rel(); return -1;}
            }
            while (sd_dat_rd() & 1);
            sd_mode(SD_DAT_RD, SD_DAT_8b);
            for (i = 0; i < 512; i++) ((char *)__cart_buf)[i] = sd_dat_rd();
            n = !__sd_type ? 2 : 8;
            for (i = 0; i < n; i++) sd_dat_rd();
            __cart_dma_wr(__cart_buf, cart, 512);
            cart += 512;
        }
    }
    else
    {
        sd_mode(SD_DAT_RD, SD_DAT_8b);
        __cart_wr(ED_DMA_LEN_REG, count-1);
        __cart_wr(ED_DMA_ADDR_REG, (cart & 0x3FFFFFF) >> 11);
        __cart_wr(ED_DMA_CFG_REG, ED_DMA_SD_TO_RAM);
        while ((resp = __cart_rd(ED_STATUS_REG)) & ED_STATE_DMA_BUSY)
        {
            if (resp & ED_STATE_DMA_TOUT) {__cart_acs_rel(); return -1;}
        }
    }
    if (sd_close(0)) {__cart_acs_rel(); return -1;}
    __cart_acs_rel();
    return 0;
}
