/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "ci.h"

int ci_init(void)
{
    __cart_acs_get();
    if (__cart_rd(CI_MAGIC_REG) != CI_MAGIC)
    {
        __cart_acs_rel();
        return -1;
    }
    __ci_sync();
    __cart_wr(CI_COMMAND_REG, CI_CARTROM_WR_ON);
    __ci_sync();
    __cart_wr(CI_COMMAND_REG, CI_BYTESWAP_OFF);
    __ci_sync();
    __cart_acs_rel();
    return 0;
}
