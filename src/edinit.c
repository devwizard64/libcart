/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "ed.h"

int ed_init(void)
{
    int ver;
    u32 dom2 = cart_dom2;
    cart_dom2 = 0x80370404;
    __cart_acs_get();
    __cart_wr(ED_KEY_REG, ED_KEY);
    ver = __cart_rd(ED_VER_REG) & 0xFFFF;
    if (ver < 0x100 || ver >= 0x400)
    {
        cart_dom2 = dom2;
        __cart_acs_rel();
        return -1;
    }
    __cart_wr(ED_CFG_REG, ED_CFG_SDRAM_ON);
    __cart_acs_rel();
    return 0;
}
