/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                        Copyright (C) 2022 devwizard                        */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "ci.h"

int ci_card_rd_dram(void *dram, u32 lba, u32 count)
{
    char *addr = dram;
    __cart_acs_get();
    __ci_sync();
    while (count-- > 0)
    {
        __ci_reg_wr(CI_LBA_REG, lba);
        if (__ci_cmd(CI_RD_BUFFER))
        {
            __ci_cmd(CI_ABORT);
            __ci_cmd(CI_SD_RESET);
            __cart_acs_rel();
            return -1;
        }
        __cart_buf_rd(addr, CI_BASE_REG|CI_BUFFER_REG, 512);
        addr += 512;
        lba++;
    }
    __cart_acs_rel();
    return 0;
}
