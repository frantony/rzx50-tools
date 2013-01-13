/*
 Macros from ftp://ftp.ingenic.cn/3sw/01linux/02kernel/linux-2.6.31/linux-2.6.31.3-jz-20110719-tag-r1198.patch.tar.bz2

 see file arch/mips/include/asm/mach-jz4750d/regs.h
*/

#ifndef _JZ4750D_GPIO_H_
#define _JZ4750D_GPIO_H_

#define GPIO_BASE 0x10010000
#define GPIO_SIZE 0x00010000

#define GPIO_PORTA 0
#define GPIO_PORTB 1
#define GPIO_PORTC 2
#define GPIO_PORTD 3
#define GPIO_PORTE 4
#define GPIO_PORTF 5

#define GPIO_PXPIN(n)	((0x00 + (n)*0x100) >> 2) /* PIN Level Register */
#define GPIO_PXDAT(n)	((0x10 + (n)*0x100) >> 2) /* Port Data Register */
#define GPIO_PXDATS(n)	((0x14 + (n)*0x100) >> 2) /* Port Data Set Register */
#define GPIO_PXDATC(n)	((0x18 + (n)*0x100) >> 2) /* Port Data Clear Register */
#define GPIO_PXIM(n)	((0x20 + (n)*0x100) >> 2) /* Interrupt Mask Register */
#define GPIO_PXIMS(n)	((0x24 + (n)*0x100) >> 2) /* Interrupt Mask Set Reg */
#define GPIO_PXIMC(n)	((0x28 + (n)*0x100) >> 2) /* Interrupt Mask Clear Reg */
#define GPIO_PXPE(n)	((0x30 + (n)*0x100) >> 2) /* Pull Enable Register */
#define GPIO_PXPES(n)	((0x34 + (n)*0x100) >> 2) /* Pull Enable Set Reg. */
#define GPIO_PXPEC(n)	((0x38 + (n)*0x100) >> 2) /* Pull Enable Clear Reg. */
#define GPIO_PXFUN(n)	((0x40 + (n)*0x100) >> 2) /* Function Register */
#define GPIO_PXFUNS(n)	((0x44 + (n)*0x100) >> 2) /* Function Set Register */
#define GPIO_PXFUNC(n)	((0x48 + (n)*0x100) >> 2) /* Function Clear Register */
#define GPIO_PXSEL(n)	((0x50 + (n)*0x100) >> 2) /* Select Register */
#define GPIO_PXSELS(n)	((0x54 + (n)*0x100) >> 2) /* Select Set Register */
#define GPIO_PXSELC(n)	((0x58 + (n)*0x100) >> 2) /* Select Clear Register */
#define GPIO_PXDIR(n)	((0x60 + (n)*0x100) >> 2) /* Direction Register */
#define GPIO_PXDIRS(n)	((0x64 + (n)*0x100) >> 2) /* Direction Set Register */
#define GPIO_PXDIRC(n)	((0x68 + (n)*0x100) >> 2) /* Direction Clear Register */
#define GPIO_PXTRG(n)	((0x70 + (n)*0x100) >> 2) /* Trigger Register */
#define GPIO_PXTRGS(n)	((0x74 + (n)*0x100) >> 2) /* Trigger Set Register */
#define GPIO_PXTRGC(n)	((0x78 + (n)*0x100) >> 2) /* Trigger Set Register */
#define GPIO_PXFLG(n)	((0x80 + (n)*0x100) >> 2) /* Port Flag Register */
#define GPIO_PXFLGC(n)	((0x14 + (n)*0x100) >> 2) /* Port Flag Clear Register */

#endif
