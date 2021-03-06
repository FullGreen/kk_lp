/* linux/arch/arm/mach-exynos/include/mach/asv-exynos3472.h
*
* Copyright (c) 2012 Samsung Electronics Co., Ltd.
*              http://www.samsung.com/
*
* EXYNOS3472 - Adoptive Support Voltage Header file
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*/

#ifndef __ASM_ARCH_EXYNOS3472_ASV_H
#define __ASM_ARCH_EXYNOS3472_ASV_H __FILE__

#define ARM_DVFS_LEVEL_NR		(14)
#define ARM_ASV_GRP_NR			(16)
#define ARM_MAX_VOLT			(1300000)

#define INT_DVFS_LEVEL_NR		(3)
#define INT_ASV_GRP_NR			(16)
#define INT_MAX_VOLT			(1150000)

#define MIF_DVFS_LEVEL_NR		(5)
#define MIF_ASV_GRP_NR			(16)
#define MIF_MAX_VOLT			(937500)

#define G3D_DVFS_LEVEL_NR		(4)
#define G3D_ASV_GRP_NR			(16)
#define G3D_MAX_VOLT			(1050000)

static unsigned int refer_table_get_asv[2][ARM_ASV_GRP_NR] = {
	/*0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15*/
	{ 0,  2,  2,  2,  3,  4,  6,  8, 10, 13, 16, 20, 25, 33, 40, 999},
	{ 0, 17, 19, 24, 27, 30, 32, 34, 36, 38, 40, 42, 44, 48, 49, 999},
};
/* ABB setting value */
static unsigned int arm_asv_abb_info[ARM_DVFS_LEVEL_NR][ARM_ASV_GRP_NR + 1] = {
	/*  FREQ   ASV0(reserved) ASV1        ASV2        ASV3        ASV4        ASV5        ASV6        ASV7        ASV8        ASV9       ASV10       ASV11       ASV12       ASV13       ASV14       ASV15(reserved) */
	{ 1400000, ABB_BYPASS,  ABB_X060,   ABB_X060,   ABB_X060,   ABB_X060,   ABB_X070,   ABB_X070,  ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS },	/* L0: 1400MHz */
	{ 1300000, ABB_BYPASS,  ABB_X060,   ABB_X060,   ABB_X060,   ABB_X060,   ABB_X070,   ABB_X070,  ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS },	/* L1: 1300MHz */
	{ 1200000, ABB_BYPASS,  ABB_X070,   ABB_X070,   ABB_X070,   ABB_X070,  ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS },	/* L2: 1200MHz */
	{ 1100000, ABB_BYPASS,  ABB_X070,   ABB_X070,   ABB_X070,   ABB_X070,  ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS },	/* L3: 1100MHz */
	{ 1000000, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS },	/* L4: 1000MHz */
	{  900000, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS },	/* L5:  900MHz */
	{  800000, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS },	/* L6:  800MHz */
	{  700000, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS,  ABB_X130,   ABB_X130,  ABB_BYPASS },	/* L7:  700MHz */
	{  600000, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS,  ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,  ABB_BYPASS },	/* L8:  600MHz */
	{  500000, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS,  ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,  ABB_BYPASS },	/* L9:  500MHz */
	{  400000, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS,  ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,  ABB_BYPASS },	/* L10: 400MHz */
	{  300000, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS, ABB_BYPASS,  ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,  ABB_BYPASS },	/* L11: 300MHz */
	{  200000, ABB_BYPASS, ABB_BYPASS,  ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,  ABB_BYPASS },	/* L12: 200MHz */
	{  100000, ABB_BYPASS,	ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,   ABB_X130,  ABB_BYPASS },	/* L13: 100MHz */
};

/* ASV setting value */
static unsigned int arm_asv_volt_info[ARM_DVFS_LEVEL_NR][ARM_ASV_GRP_NR + 1] = {
	/*  FREQ ASV0(rsvd)  ASV1    ASV2     ASV3     ASV4     ASV5     ASV6     ASV7     ASV8     ASV9     ASV10    ASV11    ASV12    ASV13    ASV14    ASV15(rsvd) */
	{ 1400000, 850000, 1300000, 1300000, 1300000, 1300000, 1300000, 1300000, 1275000, 1275000, 1250000, 1250000, 1225000, 1225000, 1200000, 1200000, 850000 },	/* L0: 1400MHz */
	{ 1300000, 850000, 1300000, 1300000, 1300000, 1250000, 1250000, 1225000, 1212500, 1212500, 1187500, 1187500, 1162500, 1162500, 1137500, 1137500, 850000 },	/* L1: 1300MHz */
	{ 1200000, 850000, 1300000, 1237500, 1225000, 1200000, 1200000, 1175000, 1150000, 1150000, 1125000, 1125000, 1100000, 1100000, 1075000, 1075000, 850000 },	/* L2: 1200MHz */
	{ 1100000, 850000, 1300000, 1187500, 1175000, 1150000, 1137500, 1112500, 1087500, 1087500, 1062500, 1062500, 1037500, 1037500, 1012500, 1012500, 850000 },	/* L3: 1100MHz */
	{ 1000000, 850000, 1300000, 1137500, 1125000, 1100000, 1075000, 1050000, 1025000, 1025000, 1000000, 1000000,  975000,  975000,  950000,  950000, 850000 },	/* L4: 1000MHz */
	{  900000, 850000, 1300000, 1100000, 1087500, 1062500, 1037500, 1012500,  987500,  987500,  962500,  962500,  937500,  937500,  912500,  912500, 850000 },	/* L5:  900MHz */
	{  800000, 850000, 1300000, 1062500, 1050000, 1025000, 1000000,  975000,  950000,  950000,  925000,  925000,  900000,  900000,  875000,  875000, 850000 },	/* L6:  800MHz */
	{  700000, 850000, 1300000, 1025000, 1012500,  987500,  962500,  937500,  912500,  912500,  887500,  887500,  875000,  875000,  850000,  850000, 850000 },	/* L7:  700MHz */
	{  600000, 850000, 1300000,  987500,  975000,  950000,  925000,  900000,  875000,  875000,  862500,  862500,  850000,  850000,  850000,  850000, 850000 },	/* L8:  600MHz */
	{  500000, 850000, 1300000,  950000,  937500,  912500,  887500,  875000,  850000,  850000,  850000,  850000,  850000,  850000,  850000,  850000, 850000 },	/* L9:  500MHz */
	{  400000, 850000, 1300000,  912500,  900000,  875000,  862500,  850000,  850000,  850000,  850000,  850000,  850000,  850000,  850000,  850000, 850000 },	/* L10: 400MHz */
	{  300000, 850000, 1300000,  875000,  875000,  850000,  850000,  850000,  850000,  850000,  850000,  850000,  850000,  850000,  850000,  850000, 850000 },	/* L11: 300MHz */
	{  200000, 850000, 1300000,  850000,  850000,  850000,  850000,  850000,  850000,  850000,  850000,  850000,  850000,  850000,  850000,  850000, 850000 },	/* L12: 200MHz */
	{  100000, 850000, 1300000,  850000,  850000,  850000,  850000,  850000,  850000,  850000,  850000,  850000,  850000,  850000,  850000,  850000, 850000 },	/* L13: 100MHz */
};

static unsigned int int_asv_volt_info[INT_DVFS_LEVEL_NR][INT_ASV_GRP_NR + 1] = {
	/*  FREQ  ASV0(rsvd)ASV1     ASV2     ASV3     ASV4     ASV5     ASV6     ASV7     ASV8     ASV9     ASV10    ASV11    ASV12    ASV13   ASV14   ASV15  */
	{ 400000,  850000, 1050000, 1025000, 1025000, 1000000, 1000000,  975000,  950000,  950000,  925000,  925000,  900000,  900000, 875000, 875000, 850000 },	/* L0: 400MHz */
	{ 200000,  850000, 1050000,  962500,  950000,  937500,  912500,  900000,  887500,  875000,  862500,  862500,  862500,  850000, 850000, 850000, 850000 },	/* L1: 200MHz */
	{ 100000,  850000, 1050000,  962500,  950000,  937500,  912500,  900000,  887500,  875000,  862500,  862500,  862500,  850000, 850000, 850000, 850000 },	/* L2: 100MHz */
};

static unsigned int mif_asv_volt_info[MIF_DVFS_LEVEL_NR][MIF_ASV_GRP_NR + 1] = {
	/* FREQ    ASV0    ASV1    ASV2    ASV3    ASV4    ASV5    ASV6    ASV7    ASV8    ASV9    ASV10   ASV11   ASV12   ASV13   ASV14   ASV15(rsvd) */
	{ 533000, 850000, 937500, 912500, 900000, 887500, 875000, 862500, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000},	/* L0: 533MHz */
	{ 400000, 850000, 937500, 925000, 912500, 900000, 887500, 875000, 862500, 862500, 862500, 862500, 850000, 850000, 850000, 850000, 850000},	/* L1: 400MHz */
	{ 266000, 850000, 937500, 862500, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000},	/* L2: 266MHz */
	{ 200000, 850000, 937500, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000},	/* L3: 200MHz */
	{ 100000, 850000, 937500, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000},	/* L4: 100MHz */
};

static unsigned int g3d_asv_volt_info[G3D_DVFS_LEVEL_NR][G3D_ASV_GRP_NR + 1] = {
	/*  FREQ  ASV0(rsvd)ASV1     ASV2     ASV3     ASV4     ASV5     ASV6    ASV7    ASV8    ASV9    ASV10   ASV11   ASV12   ASV13   ASV14   ASV15  */
	{ 440000,  850000, 1050000, 1037500, 1025000, 1012500, 1000000, 975000, 950000, 950000, 950000, 925000, 925000, 925000, 900000, 900000, 850000 },	/* L0: 440MHz */
	{ 350000,  850000, 1050000,  962500,  950000,  937500,  925000, 900000, 875000, 875000, 875000, 850000, 850000, 850000, 850000, 850000, 850000 },	/* L1: 350MHz */
	{ 266000,  850000, 1050000,  937500,  925000,  912500,  900000, 875000, 862500, 862500, 862500, 850000, 850000, 850000, 850000, 850000, 850000 },	/* L2: 266MHz */
	{ 160000,  850000, 1050000,  912500,  900000,  887500,  875000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000, 850000 },	/* L3: 160MHz */
};
#endif /* EXYNOS3472_ASV_H */
