/* arch/arm/mach-exynos4/include/mach/regs-audss.h
 *
 * Copyright (c) 2011 Samsung Electronics
 *		http://www.samsung.com
 *
 * Exynos4 Audio SubSystem clock register definitions
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __PLAT_REGS_AUDSS_H
#define __PLAT_REGS_AUDSS_H __FILE__

#define EXYNOS4_AUDSS_INT_MEM	(0x03000000)

#define EXYNOS_AUDSSREG(x)		(S5P_VA_AUDSS + (x))

#define EXYNOS_CLKSRC_AUDSS_OFFSET	0x0
#define EXYNOS_CLKDIV_AUDSS_OFFSET	0x4
#define EXYNOS_CLKGATE_AUDSS_OFFSET	0x8

#define EXYNOS5260_CLKSRC_AUDSS_SEL_OFFSET	0x200
#define EXYNOS5260_CLKSRC_AUDSS_GATE_OFFSET	0x300
#define EXYNOS5260_CLKDIV_AUDSS_0_OFFSET	0x600
#define EXYNOS5260_CLKDIV_AUDSS_1_OFFSET	0x604
#define EXYNOS5260_CLKGATE_AUDSS_ACLK_OFFSET	0x800
#define EXYNOS5260_CLKGATE_AUDSS_PCLK_OFFSET	0x900
#define EXYNOS5260_CLKGATE_AUDSS_SCLK_OFFSET	0xA00

#define EXYNOS5260_AUDSS_SWRESET_OFFSET		0x8
#define EXYNOS5260_AUDSS_CPU_INTR_OFFSET	0x50
#define EXYNOS5260_AUDSS_INTR_ENABLE_OFFSET	0x58


#define EXYNOS_CLKSRC_AUDSS		EXYNOS_AUDSSREG(EXYNOS_CLKSRC_AUDSS_OFFSET)
#define EXYNOS_CLKDIV_AUDSS		EXYNOS_AUDSSREG(EXYNOS_CLKDIV_AUDSS_OFFSET)
#define EXYNOS_CLKGATE_AUDSS		EXYNOS_AUDSSREG(EXYNOS_CLKGATE_AUDSS_OFFSET)

/* IP Clock Gate 0 Registers */
#define EXYNOS_AUDSS_CLKGATE_RP		(1<<0)
#define EXYNOS_AUDSS_CLKGATE_I2SBUS	(1<<2)
#define EXYNOS_AUDSS_CLKGATE_I2SSPECIAL	(1<<3)
#define EXYNOS_AUDSS_CLKGATE_PCMBUS	(1<<4)
#define EXYNOS_AUDSS_CLKGATE_PCMSPECIAL	(1<<5)
#define EXYNOS_AUDSS_CLKGATE_GPIO	(1<<6)
#define EXYNOS_AUDSS_CLKGATE_UART	(1<<7)
#define EXYNOS_AUDSS_CLKGATE_TIMER	(1<<8)

/* IP Clock Gate for exynos5260 */
#define EXYNOS_LPAUDSS_CLKGATE_AUDPLLUSER	(1<<0)
#define EXYNOS_LPAUDSS_CLKGATE_I2SSEL		(1<<4)
#define EXYNOS_LPAUDSS_CLKGATE_PCMSEL		(1<<8)

#define EXYNOS_LPAUDSS_CLKGATE_ACLK_DMAC	(1<<0)
#define EXYNOS_LPAUDSS_CLKGATE_ACLK_SRAM	(1<<1)
#define EXYNOS_LPAUDSS_CLKGATE_ACLK_AUDNP	(1<<2)
#define EXYNOS_LPAUDSS_CLKGATE_ACLK_AUDND	(1<<3)
#define EXYNOS_LPAUDSS_CLKGATE_ACLK_XIULPASS	(1<<4)
#define EXYNOS_LPAUDSS_CLKGATE_ACLK_AXI2APB	(1<<5)
#define EXYNOS_LPAUDSS_CLKGATE_ACLK_AXIDS	(1<<6)

#define EXYNOS_LPAUDSS_CLKGATE_PCLK_DMAC	(1<<0)
#define EXYNOS_LPAUDSS_CLKGATE_PCLK_SFRCTRL	(1<<1)
#define EXYNOS_LPAUDSS_CLKGATE_PCLK_I2S		(1<<2)
#define EXYNOS_LPAUDSS_CLKGATE_PCLK_PCM		(1<<3)
#define EXYNOS_LPAUDSS_CLKGATE_PCLK_UART	(1<<4)
#define EXYNOS_LPAUDSS_CLKGATE_PCLK_SYSREG	(1<<5)
#define EXYNOS_LPAUDSS_CLKGATE_PCLK_PMU		(1<<6)
#define EXYNOS_LPAUDSS_CLKGATE_PCLK_GPIO	(1<<7)

#define EXYNOS_LPAUDSS_CLKGATE_SCLK_I2S		(1<<0)
#define EXYNOS_LPAUDSS_CLKGATE_SCLK_PCM		(1<<1)
#define EXYNOS_LPAUDSS_CLKGATE_SCLK_UART	(1<<2)

#endif /* _PLAT_REGS_AUDSS_H */
