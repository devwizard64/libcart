/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                        Copyright (C) 2022 devwizard                        */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "ci.h"

int __ci_sync(void)
{
    int n = 65536;
    do
    {
        if (--n == 0) return -1;
    }
    while ((__ci_reg_rd(CI_STATUS_REG) & CI_STATUS_MASK) != CI_IDLE);
    return 0;
}
