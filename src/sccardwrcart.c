/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "sc.h"

int sc_card_wr_cart(u32 cart, u32 lba, u32 count)
{
    __cart_acs_get();
    __sc_sync();
    __cart_wr(SC_DATA0_REG, lba);
        __cart_wr(SC_COMMAND_REG, SC_SD_SECTOR_SET);
    if (__sc_sync())
    {
        __cart_acs_rel();
        return -1;
    }
    __cart_wr(SC_DATA0_REG, cart);
    __cart_wr(SC_DATA1_REG, count);
        __cart_wr(SC_COMMAND_REG, SC_SD_WRITE);
    if (__sc_sync())
    {
        __cart_acs_rel();
        return -1;
    }
    __cart_acs_rel();
    return 0;
}
