/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "sc.h"

int __sc_sync(void)
{
    while (__cart_rd(SC_STATUS_REG) & SC_CMD_BUSY);
    if (__cart_rd(SC_STATUS_REG) & SC_CMD_ERROR) return -1;
    return 0;
}
