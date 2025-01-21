#include <cart.h>
#include "cartint.h"

#define MI_VERSION ((volatile uint32_t*)0xA4300004)
#define cart_bbplayer() ((*MI_VERSION & 0xF0) == 0xB0)

int cart_type = CART_NULL;

int cart_init(void)
{
	static int (*const init[CART_MAX])(void) =
	{
		ci_init,
		edx_init,
		ed_init,
		sc_init,
	};
	int i;
	int result;
	// On iQue, touching PI addresses outside mapped ROM triggers a bus error
	if (cart_bbplayer())
	{
		return -1;
	}
	if (!__cart_dom1)
	{
		__cart_dom1 = 0x8030FFFF;
		__cart_acs_get();
		__cart_dom1 = __cart_rd(0x10000000);
		__cart_acs_rel();
	}
	if (!__cart_dom2) __cart_dom2 = __cart_dom1;
	if (cart_type < 0)
	{
		for (i = 0; i < CART_MAX; i++)
		{
			if ((result = init[i]()) >= 0)
			{
				cart_type = i;
				return result;
			}
		}
		return -1;
	}
	return init[cart_type]();
}
