/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                        Copyright (C) 2022 devwizard                        */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "ed.h"

int ed_init(void)
{
    int status = -1;
    int ver;
    __cart_acs_get();
    __ed_reg_wr(ED_KEY_REG, ED_KEY);
    ver = __ed_reg_rd(ED_VER_REG) & 0xFFFF;
    if (ver >= 0x100 && ver < 0x400)
    {
        IO_WRITE(PI_BSD_DOM2_LAT_REG, 0x04);
        IO_WRITE(PI_BSD_DOM2_PWD_REG, 0x04);
        status = 0;
    }
    __cart_acs_rel();
    return status;
}
