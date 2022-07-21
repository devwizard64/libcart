/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                        Copyright (C) 2022 devwizard                        */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"

int cart_card_rd_cart(u32 cart, u32 lba, u32 count)
{
    static int (*const card_rd_cart[CART_MAX])(u32 cart, u32 lba, u32 count) =
    {
        ci_card_rd_cart,
        edx_card_rd_cart,
        ed_card_rd_cart,
    };
#ifdef DEBUG
    if (cart_type < 0 || cart_type >= CART_MAX) return -1;
#endif
    return card_rd_cart[cart_type](cart, lba, count);
}
