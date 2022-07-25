/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                        Copyright (C) 2022 devwizard                        */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "edx.h"

int edx_init(void)
{
    __cart_acs_get();
    __edx_reg_wr(EDX_KEY_REG, EDX_KEY);
    if (__edx_reg_rd(EDX_EDID_REG) >> 16 != 0xED64)
    {
        __cart_acs_rel();
        return -1;
    }
    __edx_reg_wr(EDX_SYS_CFG_REG, EDX_CFG_SDRAM_ON);
    cart_dom1 = 0x80370C04;
    __cart_acs_rel();
    return 0;
}
