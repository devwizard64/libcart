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

int ed_card_rd_dram(void *dram, u32 lba, u32 count)
{
    char *addr = dram;
    int i;
    int n;
    __cart_acs_get();
    if (!__sd_flag) lba *= 512;
    if (sd_cmd(CMD18, lba) < 0) {__cart_acs_rel(); return -1;}
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
        for (i = 0; i < 512; i++) addr[i] = sd_dat_rd();
        n = !__sd_type ? 2 : 8;
        for (i = 0; i < n; i++) sd_dat_rd();
        addr += 512;
    }
    if (sd_close(0)) {__cart_acs_rel(); return -1;}
    __cart_acs_rel();
    return 0;
}
