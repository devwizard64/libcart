/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "sc.h"

int sc_init(void)
{
    __cart_acs_get();
    __cart_wr(SC_KEY_REG, SC_KEY_RESET);
    __cart_wr(SC_KEY_REG, SC_KEY_UNL);
    __cart_wr(SC_KEY_REG, SC_KEY_OCK);
    if (__cart_rd(SC_VERSION_REG) != SC_VERSION)
    {
        __cart_acs_rel();
        return -1;
    }
    __sc_sync();
    __cart_wr(SC_DATA0_REG, SC_CFG_ROM_WRITE);
    __cart_wr(SC_DATA1_REG, 1);
    __cart_wr(SC_COMMAND_REG, SC_CONFIG_SET);
    __sc_sync();
    __cart_acs_rel();
    return 0;
}
