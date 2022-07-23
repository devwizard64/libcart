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
    int status = -1;
    __cart_acs_get();
    __edx_reg_wr(EDX_KEY_REG, EDX_KEY);
    if (__edx_reg_rd(EDX_EDID_REG) >> 16 == 0xED64)
    {
        IO_WRITE(PI_BSD_DOM1_LAT_REG, 0x04);
        IO_WRITE(PI_BSD_DOM1_PWD_REG, 0x0C);
        __edx_reg_wr(EDX_SYS_CFG_REG, EDX_CFG_SDRAM_ON);
        status = 0;
    }
    __cart_acs_rel();
    return status;
}