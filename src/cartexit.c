/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                        Copyright (C) 2022 devwizard                        */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"

int cart_exit(void)
{
    static int (*const exit[CART_MAX])(void) =
    {
        ci_exit,
        edx_exit,
        ed_exit,
    };
#ifdef DEBUG
    if (cart_type < 0 || cart_type >= CART_MAX) return -1;
#endif
    return exit[cart_type]();
}
