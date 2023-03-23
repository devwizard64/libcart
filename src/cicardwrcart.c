/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "ci.h"

int ci_card_wr_cart(u32 cart, u32 lba, u32 count)
{
    __cart_acs_get();
    __ci_sync();
    __cart_wr(CI_LBA_REG, lba);
    __cart_wr(CI_LENGTH_REG, count);
    __cart_wr(CI_SDRAM_ADDR_REG, (cart & 0x3FFFFFF) >> 1);
    __cart_wr(CI_COMMAND_REG, CI_WR_SDRAM);
    if (__ci_sync())
    {
        __cart_wr(CI_COMMAND_REG, CI_ABORT);
        __ci_sync();
        __cart_wr(CI_COMMAND_REG, CI_SD_RESET);
        __ci_sync();
        __cart_acs_rel();
        return -1;
    }
    __cart_acs_rel();
    return 0;
}
