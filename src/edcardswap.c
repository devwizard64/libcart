/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "ed.h"

int ed_card_swap(int flag)
{
    __cart_acs_get();
    __cart_wr(ED_CFG_REG, flag ?
        (ED_CFG_SDRAM_ON|ED_CFG_SWAP) : (ED_CFG_SDRAM_ON)
    );
    __cart_acs_rel();
    return 0;
}
