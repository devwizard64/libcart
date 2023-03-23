/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "edx.h"

int edx_exit(void)
{
    __cart_acs_get();
    __cart_wr(EDX_KEY_REG, 0);
    __cart_acs_rel();
    return 0;
}
