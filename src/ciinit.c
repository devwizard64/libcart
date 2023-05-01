#include <cart.h>
#include "cartint.h"
#include "ci.h"

int ci_init(void)
{
    __cart_acs_get();
    /* Check if using extended addressing */
    __ci_base_reg = CI_EXT_BASE_REG;
    if (__cart_rd(CI_MAGIC_REG) != CI_MAGIC)
    {
        /* Check if using regular addressing */
        __ci_base_reg = CI_BASE_REG;
        if (__cart_rd(CI_MAGIC_REG) != CI_MAGIC) CART_ABORT();
        /* If HW2, switch to extended addressing */
        if ((__cart_rd(CI_VARIANT_REG) & 0xFFFF) >= CI_VARIANT_HW2)
        {
            __ci_sync();
            __cart_wr(CI_COMMAND_REG, CI_EXT_ADDR_ON);
            __ci_base_reg = CI_EXT_BASE_REG;
            cart_size = 0xF000000; /* 240 MiB */
        }
        else
        {
            cart_size = 0x4000000; /* 64 MiB */
        }
    }
    __ci_sync();
    __cart_wr(CI_COMMAND_REG, CI_CARTROM_WR_ON);
    __ci_sync();
    __cart_wr(CI_COMMAND_REG, CI_BYTESWAP_OFF);
    __ci_sync();
    __cart_acs_rel();
    return 0;
}
