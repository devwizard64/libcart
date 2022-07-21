/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                        Copyright (C) 2022 devwizard                        */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#ifndef __CI_H__
#define __CI_H__

#define CI_BASE_REG             0x18000000

#define CI_BUFFER_REG           0x0000
#define CI_SDRAM_ADDR_REG       0x0004

#define CI_STATUS_REG           0x0200
#define CI_COMMAND_REG          0x0208
#define CI_LBA_REG              0x0210
#define CI_LENGTH_REG           0x0218
#define CI_RESULT_REG           0x0220

#define CI_MAGIC_REG            0x02EC
#define CI_VARIANT_REG          0x02F0
#define CI_REVISION_REG         0x02FC

#define CI_STATUS_MASK          0xF000
#define CI_IDLE                 0x0000
#define CI_BUSY                 0x1000

#define CI_RD_BUFFER            0x01
#define CI_RD_SDRAM             0x03
#define CI_WR_BUFFER            0x10
#define CI_WR_SDRAM             0x13
#define CI_SD_RESET             0x1F
#define CI_BYTESWAP_OFF         0xE0
#define CI_BYTESWAP_ON          0xE1
#define CI_CARTROM_WR_ON        0xF0
#define CI_CARTROM_WR_OFF       0xF1
#define CI_ABORT                0xFF

#define CI_MAGIC                0x55444556  /* UDEV */

#define __ci_reg_rd(reg)        __cart_rd(CI_BASE_REG|(reg))
#define __ci_reg_wr(reg, val)   __cart_wr(CI_BASE_REG|(reg), val)

extern int __ci_sync(void);
#define __ci_cmd(cmd) (__ci_reg_wr(CI_COMMAND_REG, cmd), __ci_sync())

#endif /* __CI_H__ */
