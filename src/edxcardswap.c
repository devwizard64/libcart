/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "edx.h"

int edx_card_swap(int flag)
{
    __cart_acs_get();
    __cart_wr(EDX_SYS_CFG_REG, flag ?
        (EDX_CFG_SDRAM_ON|EDX_CFG_SWAP) : (EDX_CFG_SDRAM_ON)
    );
    __cart_acs_rel();
    return 0;
}
