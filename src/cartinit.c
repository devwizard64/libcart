/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                        Copyright (C) 2022 devwizard                        */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"

int cart_type = CART_NULL;

int cart_init(void)
{
    static int (*const init[CART_MAX])(void) =
    {
        ci_init,
        edx_init,
        ed_init,
    };
    int i;
    cart_dom1 = 0x8030FFFF;
    __cart_acs_get();
    cart_dom1 = __cart_rd(0x10000000);
    __cart_acs_rel();
    for (i = 0; i < CART_MAX; i++) if (!init[i]()) return cart_type = i;
    return cart_type = CART_NULL;
}
