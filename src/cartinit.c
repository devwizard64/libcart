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
    for (i = 0; i < CART_MAX; i++)
    {
        if (!init[i]()) return cart_type = i;
    }
    return cart_type = CART_NULL;
}
