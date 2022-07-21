/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                        Copyright (C) 2022 devwizard                        */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "ci.h"

int ci_card_wr_dram(const void *dram, u32 lba, u32 count)
{
    const char *addr = dram;
    __cart_acs_get();
    __ci_sync();
    while (count-- > 0)
    {
        __cart_buf_wr(addr, CI_BASE_REG|CI_BUFFER_REG, 512);
        __ci_reg_wr(CI_LBA_REG, lba);
        if (__ci_cmd(CI_WR_BUFFER))
        {
            __ci_cmd(CI_ABORT);
            __ci_cmd(CI_SD_RESET);
            __cart_acs_rel();
            return -1;
        }
        addr += 512;
        lba++;
    }
    __cart_acs_rel();
    return 0;
}
