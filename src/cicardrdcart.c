/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                        Copyright (C) 2022 devwizard                        */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "ci.h"

int ci_card_rd_cart(u32 cart, u32 lba, u32 count)
{
    __cart_acs_get();
    __ci_sync();
    __ci_reg_wr(CI_LBA_REG, lba);
    __ci_reg_wr(CI_LENGTH_REG, count);
    __ci_reg_wr(CI_SDRAM_ADDR_REG, (cart & 0x3FFFFFF) >> 1);
    if (__ci_cmd(CI_RD_SDRAM))
    {
        __ci_cmd(CI_ABORT);
        __ci_cmd(CI_SD_RESET);
        __cart_acs_rel();
        return -1;
    }
    __cart_acs_rel();
    return 0;
}
