/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "edx.h"

int edx_init(void)
{
    u32 dom1 = cart_dom1;
    cart_dom1 = 0x80370C04;
    __cart_acs_get();
    __cart_wr(EDX_KEY_REG, EDX_KEY);
    if (__cart_rd(EDX_EDID_REG) >> 16 != 0xED64)
    {
        cart_dom1 = dom1;
        __cart_acs_rel();
        return -1;
    }
    __cart_wr(EDX_SYS_CFG_REG, EDX_CFG_SDRAM_ON);
    __cart_acs_rel();
    return 0;
}
