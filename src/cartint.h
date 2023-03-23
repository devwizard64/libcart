/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#ifndef __CARTINT_H__
#define __CARTINT_H__

#ifdef _ULTRA64

extern u32 __cart_rd(u32 addr);
extern void __cart_wr(u32 addr, u32 data);

#else /* _ULTRA64 */

typedef uint64_t u64;

#define PI_BASE_REG             0x04600000
#define PI_DRAM_ADDR_REG        (PI_BASE_REG+0x00)
#define PI_CART_ADDR_REG        (PI_BASE_REG+0x04)
#define PI_RD_LEN_REG           (PI_BASE_REG+0x08)
#define PI_WR_LEN_REG           (PI_BASE_REG+0x0C)
#define PI_STATUS_REG           (PI_BASE_REG+0x10)
#define PI_BSD_DOM1_LAT_REG     (PI_BASE_REG+0x14)
#define PI_BSD_DOM1_PWD_REG     (PI_BASE_REG+0x18)
#define PI_BSD_DOM1_PGS_REG     (PI_BASE_REG+0x1C)
#define PI_BSD_DOM1_RLS_REG     (PI_BASE_REG+0x20)
#define PI_BSD_DOM2_LAT_REG     (PI_BASE_REG+0x24)
#define PI_BSD_DOM2_PWD_REG     (PI_BASE_REG+0x28)
#define PI_BSD_DOM2_PGS_REG     (PI_BASE_REG+0x2C)
#define PI_BSD_DOM2_RLS_REG     (PI_BASE_REG+0x30)
#define PI_STATUS_IO_BUSY       0x02
#define PI_STATUS_DMA_BUSY      0x01

#define IO_READ(addr)       (*(volatile u32 *)PHYS_TO_K1(addr))
#define IO_WRITE(addr,data) (*(volatile u32 *)PHYS_TO_K1(addr) = (u32)(data))

#define PHYS_TO_K1(x)   ((u32)(x)|0xA0000000)

#define __cart_rd(addr)         io_read(addr)
#define __cart_wr(addr, data)   io_write(addr, data)

#endif /* _ULTRA64 */

extern void __cart_acs_get(void);
extern void __cart_acs_rel(void);
extern void __cart_dma_rd(void *dram, u32 cart, u32 size);
extern void __cart_dma_wr(const void *dram, u32 cart, u32 size);
extern void __cart_buf_rd(void *dram, u32 cart, u32 size);
extern void __cart_buf_wr(const void *dram, u32 cart, u32 size);
extern u64 __cart_buf[512/8];

#endif /* __CARTINT_H__ */
