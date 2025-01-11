#include <cart.h>
#include "cartint.h"
#include "edx.h"
#include <string.h>

static const char edx_bootx[20] = "EverDrive bootloader";
static const char edx_boot3[12] = "ED64 SD boot";

int edx_init(void)
{
	__cart_acs_get();
	__cart_wr(EDX_KEY_REG, EDX_KEY);
	__cart_wr(EDX_SYS_CFG_REG, EDX_CFG_SDRAM_OFF);
	/* Check bootloader ROM label */
	__cart_dma_rd(__cart_buf, 0x10000020, 20);
	if (memcmp(__cart_buf, edx_bootx, 20) && memcmp(__cart_buf, edx_boot3, 12))
	{
		CART_ABORT();
	}
	__cart_wr(EDX_SYS_CFG_REG, EDX_CFG_SDRAM_ON);
	__cart_dom1 = 0x80370C04;
	cart_size = 0x4000000; /* 64 MiB */
	__cart_acs_rel();
	return 0;
}
