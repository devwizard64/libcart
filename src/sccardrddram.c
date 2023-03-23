/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "sc.h"

int sc_card_rd_dram(void *dram, u32 lba, u32 count)
{
    char *addr = dram;
    int i;
    int n;
    __cart_acs_get();
    __sc_sync();
    while (count > 0)
    {
        n = count < 16 ? count : 16;
        __cart_wr(SC_DATA0_REG, lba);
        __cart_wr(SC_COMMAND_REG, SC_SD_SECTOR_SET);
        if (__sc_sync())
        {
            __cart_acs_rel();
            return -1;
        }
        __cart_wr(SC_DATA0_REG, SC_BUFFER_REG);
        __cart_wr(SC_DATA1_REG, n);
        __cart_wr(SC_COMMAND_REG, SC_SD_READ);
        if (__sc_sync())
        {
            __cart_acs_rel();
            return -1;
        }
        for (i = 0; i < n; i++)
        {
            __cart_buf_rd(addr, SC_BUFFER_REG+512*i, 512);
            addr += 512;
        }
        lba += n;
        count -= n;
    }
    __cart_acs_rel();
    return 0;
}
