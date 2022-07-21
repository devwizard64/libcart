/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                        Copyright (C) 2022 devwizard                        */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "ci.h"

int ci_exit(void)
{
    __cart_acs_get();
    __ci_sync();
    __ci_cmd(CI_CARTROM_WR_OFF);
    __cart_acs_rel();
    return 0;
}
