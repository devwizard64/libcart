/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "ci.h"

int ci_card_swap(int flag)
{
    __cart_acs_get();
    __ci_sync();
    __cart_wr(CI_COMMAND_REG, flag ? CI_BYTESWAP_ON : CI_BYTESWAP_OFF);
    __ci_sync();
    __cart_acs_rel();
    return 0;
}
