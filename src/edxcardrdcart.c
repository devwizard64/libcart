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

int edx_card_rd_cart(u32 cart, u32 lba, u32 count)
{
    u32 resp;
    __cart_acs_get();
    if (!__sd_flag) lba *= 512;
    if (sd_cmd(CMD18, lba) < 0) {__cart_acs_rel(); return -1;}
    __cart_wr(EDX_DMA_ADDR_REG, cart & 0x3FFFFFF);
    __cart_wr(EDX_DMA_LEN_REG, count);
    sd_mode(SD_DAT_RD, SD_DAT_16b);
    while ((resp = __cart_rd(EDX_DMA_STA_REG)) & EDX_DMA_STA_BUSY)
    {
        if (resp & EDX_DMA_STA_ERROR) {__cart_acs_rel(); return -1;}
    }
    if (sd_close(0)) {__cart_acs_rel(); return -1;}
    __cart_acs_rel();
    return 0;
}
