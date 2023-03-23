/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#ifndef sgi
.set gp=64
#endif
.set noreorder

.globl __cart_buf_rd
__cart_buf_rd:
    and     $14, $4, 7
    beqz    $14, 2f
    subu    $29, 24
    sw      $31, 20($29)
    sw      $4, 24($29)
    sw      $6, 32($29)
    lui     $4, %hi(__cart_buf)
    jal     __cart_dma_rd
    addiu   $4, $4, %lo(__cart_buf)
    lw      $15, 24($29)
    lui     $24, %hi(__cart_buf)
    addiu   $24, $24, %lo(__cart_buf)
    lw      $25, 32($29)
    addu    $25, $15
1:
    ld      $8, 0($24)
    ld      $9, 8($24)
    sdl     $8, 0($15)
    sdr     $8, 7($15)
    sdl     $9, 8($15)
    sdr     $9, 15($15)
    addu    $15, 16
    bne     $15, $25, 1b
    addu    $24, 16
    lw      $31, 20($29)
    j       $31
    addu    $29, 24
2:
    j       __cart_dma_rd
    addu    $29, 24

.globl __cart_buf_wr
__cart_buf_wr:
    and     $14, $4, 7
    beqz    $14, 2f
    lui     $15, %hi(__cart_buf)
    addiu   $15, $15, %lo(__cart_buf)
    move    $24, $4
    addu    $25, $15, $6
    move    $4, $15
1:
    ldl     $8, 0($24)
    ldr     $8, 7($24)
    ldl     $9, 8($24)
    ldr     $9, 15($24)
    sd      $8, 0($15)
    sd      $9, 8($15)
    addu    $15, 16
    bne     $15, $25, 1b
    addu    $24, 16
2:
    j       __cart_dma_wr
    nop
