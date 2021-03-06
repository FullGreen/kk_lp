/* linux/arch/arm/plat-samsung/include/plat/regs_ielcd.h
 *
 * Header file for Samsung (IELCD) driver
 *
 * Copyright (c) 2009 Samsung Electronics
 * http://www.samsungsemi.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef _REGS_IELCD_H
#define _REGS_IELCD_H

#define S3C_IELCD_PHY_BASE		0x11C40000
#define S3C_IELCD_MAP_SIZE		SZ_32K

/* Register Offset */
#define IELCD_VIDCON0			(0x0000)
#define IELCD_VIDCON1			(0x0004)

#define IELCD_VIDTCON0		(0x0010)
#define IELCD_VIDTCON1		(0x0014)
#define IELCD_VIDTCON2		(0x0018)

#define IELCD_WINCON0			(0x0020)

#define IELCD_SHADOWCON			(0x0034)

#define IELCD_VIDOSD0A		(0x0040)
#define IELCD_VIDOSD0B		(0x0044)
#define IELCD_VIDOSD0C		(0x0048)
#define IELCD_VIDW00ADD2		(0x0100)

#define IELCD_TRIGCON		(0x01A4)
#define IELCD_I80IFCONA0		(0x01B0)
#define IELCD_I80IFCONA1		(0x01B4)
#define IELCD_I80IFCONB0		(0x01B8)
#define IELCD_I80IFCONB1		(0x01BC)
#define IELCD_AUXCON			(0x0278)

/* Value */
#define IELCD_MAGIC_KEY		(0x2ff47)
#define IELCD_WINDOW0_FIXED		(0x40002d)

/* Register bit */
#define IELCD_VIDTCON2_LINEVAL_FOR_5410(_x)		((_x) << 12)
#define IELCD_VIDTCON2_HOZVAL(_x)			((_x) << 0)

/* IELCD_VIDCON0 */
#define IELCD_SW_SHADOW_UPTRIG		(1 << 14)

/* IELCD_SHADOWCON */
#define IELCD_W0_SW_SHADOW_UPTRIG	(1 << 16)
#endif
