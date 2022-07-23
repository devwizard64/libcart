/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                        Copyright (C) 2022 devwizard                        */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"

u64 __cart_buf[512/8];

#ifdef _ULTRA64

u32 __cart_rd(u32 addr)
{
    while (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY|PI_STATUS_IO_BUSY));
    return IO_READ(addr);
}

void __cart_wr(u32 addr, u32 data)
{
    while (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY|PI_STATUS_IO_BUSY));
    IO_WRITE(addr, data);
}

typedef struct
{
    OSMesgQueue *messageQueue;
    OSMesg message;
}
__OSEventState;
extern __OSEventState __osEventStateTab[OS_NUM_EVENTS];

void __cart_dma_rd(void *dram, u32 cart, u32 size)
{
    osInvalDCache(dram, size);
    while (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY|PI_STATUS_IO_BUSY));
    IO_WRITE(PI_DRAM_ADDR_REG, osVirtualToPhysical(dram));
    IO_WRITE(PI_CART_ADDR_REG, cart);
    IO_WRITE(PI_WR_LEN_REG, size-1);
    osRecvMesg(
        __osEventStateTab[OS_EVENT_PI].messageQueue, NULL, OS_MESG_BLOCK
    );
}

void __cart_dma_wr(const void *dram, u32 cart, u32 size)
{
    osWritebackDCache((void *)dram, size);
    while (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY|PI_STATUS_IO_BUSY));
    IO_WRITE(PI_DRAM_ADDR_REG, osVirtualToPhysical((void *)dram));
    IO_WRITE(PI_CART_ADDR_REG, cart);
    IO_WRITE(PI_RD_LEN_REG, size-1);
    osRecvMesg(
        __osEventStateTab[OS_EVENT_PI].messageQueue, NULL, OS_MESG_BLOCK
    );
}

#else /* _ULTRA64 */

void __cart_dma_rd(void *dram, u32 cart, u32 size)
{
    data_cache_hit_writeback_invalidate(dram, size);
    disable_interrupts();
    while (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY|PI_STATUS_IO_BUSY));
    IO_WRITE(PI_DRAM_ADDR_REG, PhysicalAddr(dram));
    IO_WRITE(PI_CART_ADDR_REG, cart);
    IO_WRITE(PI_WR_LEN_REG, size-1);
    while (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY|PI_STATUS_IO_BUSY));
    enable_interrupts();
}

void __cart_dma_wr(const void *dram, u32 cart, u32 size)
{
    data_cache_hit_writeback(dram, size);
    disable_interrupts();
    while (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY|PI_STATUS_IO_BUSY));
    IO_WRITE(PI_DRAM_ADDR_REG, PhysicalAddr(dram));
    IO_WRITE(PI_CART_ADDR_REG, cart);
    IO_WRITE(PI_RD_LEN_REG, size-1);
    while (IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY|PI_STATUS_IO_BUSY));
    enable_interrupts();
}

#endif /* _ULTRA64 */
