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
