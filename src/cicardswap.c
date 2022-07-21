/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                        Copyright (C) 2022 devwizard                        */
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
    __ci_cmd(flag ? CI_BYTESWAP_ON : CI_BYTESWAP_OFF);
    __cart_acs_rel();
    return 0;
}
