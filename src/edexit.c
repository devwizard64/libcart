/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                        Copyright (C) 2022 devwizard                        */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "ed.h"

int ed_exit(void)
{
    __cart_acs_get();
    __ed_reg_wr(ED_KEY_REG, 0);
    __cart_acs_rel();
    return 0;
}
