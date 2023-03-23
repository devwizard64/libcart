/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"

int cart_card_init(void)
{
    static int (*const card_init[CART_MAX])(void) =
    {
        ci_card_init,
        edx_card_init,
        ed_card_init,
        sc_card_init,
    };
    if (cart_type < 0) return -1;
    return card_init[cart_type]();
}
