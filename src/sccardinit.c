/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "sc.h"

int sc_card_init(void)
{
    __cart_acs_get();
    __sc_sync();
    __cart_wr(SC_DATA1_REG, SC_SD_INIT);
    __cart_wr(SC_COMMAND_REG, SC_SD_OP);
    if (__sc_sync())
    {
        __cart_acs_rel();
        return -1;
    }
    __cart_acs_rel();
    return 0;
}
