#include <cart.h>
#include "cartint.h"

int cart_exit(void)
{
	static int (*const exit[CART_MAX])(void) =
	{
		ci_exit,
		edx_exit,
		ed_exit,
		sc_exit,
	};
	int result = -1;
	if (cart_type >= 0)
	{
		result = exit[cart_type]();
	}
	cart_type = CART_UNDEFINED;
	return result;
}
