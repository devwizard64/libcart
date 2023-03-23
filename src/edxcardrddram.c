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

int edx_card_rd_dram(void *dram, u32 lba, u32 count)
{
    char *addr = dram;
    int n;
    __cart_acs_get();
    if (!__sd_flag) lba *= 512;
    if (sd_cmd(CMD18, lba) < 0) {__cart_acs_rel(); return -1;}
    while (count-- > 0)
    {
        sd_mode(SD_DAT_RD, SD_DAT_4b);
        n = 65536;
        do
        {
            if (--n == 0) {__cart_acs_rel(); return -1;}
        }
        while (sd_dat_rd() & 0xF);
        sd_mode(SD_DAT_RD, SD_DAT_16b);
        __cart_buf_rd(addr, EDX_BASE_REG|EDX_SDIO_ARD_REG, 512);
        __cart_dma_rd(__cart_buf, EDX_BASE_REG|EDX_SDIO_ARD_REG, 8);
        addr += 512;
    }
    if (sd_close(0)) {__cart_acs_rel(); return -1;}
    __cart_acs_rel();
    return 0;
}
