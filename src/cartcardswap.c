/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"

int cart_card_swap(int flag)
{
    static int (*const card_swap[CART_MAX])(int flag) =
    {
        ci_card_swap,
        edx_card_swap,
        ed_card_swap,
        sc_card_swap,
    };
    if (cart_type < 0) return -1;
    return card_swap[cart_type](flag);
}
