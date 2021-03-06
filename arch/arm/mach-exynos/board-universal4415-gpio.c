/* linux/arch/arm/mach-exynos/board-universal5420-gpio.c
 *
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/gpio.h>
#include <plat/gpio-cfg.h>
#include <asm/system_info.h>
#include <mach/gpio-exynos.h>

#include "board-universal4415.h"

#define GPIO_LV_L	0	/* GPIO level low */
#define GPIO_LV_H	1	/* GPIO level high */
#define GPIO_LV_N	2	/* GPIO level none */

struct gpio_init_data {
	u32 num;
	u32 cfg;
	u32 val;
	u32 pud;
};

struct gpio_sleep_data {
	u32 num;
	u32 cfg;
	u32 pud;
};

struct sleep_gpio_table {
	struct gpio_sleep_data *table;
	u32 arr_size;
};

#define GPIO_TABLE(_ptr) \
	{.table = _ptr, \
	.arr_size = ARRAY_SIZE(_ptr)} \

#define GPIO_TABLE_NULL \
	{.table = NULL, \
	.arr_size = 0} \

static struct gpio_init_data __initdata init_gpio_table[] = {
        { EXYNOS4_GPA1(0), S3C_GPIO_INPUT, GPIO_LV_N, S3C_GPIO_PULL_DOWN }, /* NC */
        { EXYNOS4_GPA1(1), S3C_GPIO_INPUT, GPIO_LV_N, S3C_GPIO_PULL_DOWN }, /* NC */

        { EXYNOS4_GPD0(2), S3C_GPIO_INPUT, GPIO_LV_N, S3C_GPIO_PULL_NONE }, /* NFC_SDA_1.8V */
        { EXYNOS4_GPD0(3), S3C_GPIO_INPUT, GPIO_LV_N, S3C_GPIO_PULL_NONE }, /* NFC_SCL_1.8V */

	{ EXYNOS4_GPK1(2), S3C_GPIO_INPUT, GPIO_LV_N, S3C_GPIO_PULL_DOWN }, /* NC */

        { EXYNOS4_GPK3(0), S3C_GPIO_OUTPUT, GPIO_LV_L, S3C_GPIO_PULL_NONE }, /* AP_DUMP_INT */
        { EXYNOS4_GPK3(4), S3C_GPIO_OUTPUT, GPIO_LV_L, S3C_GPIO_PULL_NONE }, /* CAM_SENSOR_CORE_EN */

        { EXYNOS4_GPY0(0), S3C_GPIO_INPUT, GPIO_LV_N, S3C_GPIO_PULL_DOWN }, /* NC */
        { EXYNOS4_GPY0(1), S3C_GPIO_INPUT, GPIO_LV_N, S3C_GPIO_PULL_DOWN }, /* NC */
        { EXYNOS4_GPY0(4), S3C_GPIO_INPUT, GPIO_LV_N, S3C_GPIO_PULL_DOWN }, /* NC */
        { EXYNOS4_GPY0(5), S3C_GPIO_INPUT, GPIO_LV_N, S3C_GPIO_PULL_DOWN }, /* NC */

        { EXYNOS4_GPY1(3), S3C_GPIO_INPUT, GPIO_LV_N, S3C_GPIO_PULL_DOWN }, /* NC */

        { EXYNOS4_GPY6(3), S3C_GPIO_INPUT, GPIO_LV_N, S3C_GPIO_PULL_NONE }, /* e_FUSE_ON */

        { EXYNOS4_GPM0(1), S3C_GPIO_OUTPUT, GPIO_LV_L, S3C_GPIO_PULL_NONE },    /* MOTOR_EN */

        { EXYNOS4_GPM0(3), S3C_GPIO_OUTPUT, GPIO_LV_L, S3C_GPIO_PULL_NONE },    /* CAM_VT_nRST*/
        { EXYNOS4_GPM0(4), S3C_GPIO_OUTPUT, GPIO_LV_L, S3C_GPIO_PULL_NONE },    /* 8M_CAM_RST */
        { EXYNOS4_GPM4(0), S3C_GPIO_OUTPUT, GPIO_LV_L, S3C_GPIO_PULL_NONE },    /* 8M_CAM_SCL_1.8V */
        { EXYNOS4_GPM4(1), S3C_GPIO_OUTPUT, GPIO_LV_L, S3C_GPIO_PULL_NONE },    /* 8M_CAM_SDA_1.8V */

        { EXYNOS4_GPF0(0), S3C_GPIO_INPUT, GPIO_LV_N, S3C_GPIO_PULL_UP },    /* LCD_ESD_DETECT */

        { EXYNOS4_GPF1(0), S3C_GPIO_OUTPUT, GPIO_LV_N, S3C_GPIO_PULL_NONE },    /* PM_DS2 */
        { EXYNOS4_GPF1(1), S3C_GPIO_OUTPUT, GPIO_LV_N, S3C_GPIO_PULL_NONE },    /* PM_DS3 */
        { EXYNOS4_GPF1(2), S3C_GPIO_OUTPUT, GPIO_LV_N, S3C_GPIO_PULL_NONE },    /* PM_DS4 */
        { EXYNOS4_GPF1(3), S3C_GPIO_OUTPUT, GPIO_LV_N, S3C_GPIO_PULL_NONE },    /* PM_DVS1 */
        { EXYNOS4_GPF1(4), S3C_GPIO_OUTPUT, GPIO_LV_N, S3C_GPIO_PULL_NONE },    /* PM_DVS2   */
        { EXYNOS4_GPF1(5), S3C_GPIO_OUTPUT, GPIO_LV_N, S3C_GPIO_PULL_NONE },    /* PM_DVS3   */
        { EXYNOS4_GPF1(6), S3C_GPIO_OUTPUT, GPIO_LV_H, S3C_GPIO_PULL_NONE }, /* COVER_ID */

        { EXYNOS4_GPX1(2), S3C_GPIO_INPUT, GPIO_LV_N, S3C_GPIO_PULL_DOWN }, /* CP_DUMP_INT */

        { EXYNOS4_GPX3(6), S3C_GPIO_INPUT, GPIO_LV_N, S3C_GPIO_PULL_NONE }, /* 3.5PI_DET_BB */
#ifdef CONFIG_MACH_MEGA2LTE_USA_ATT
        { EXYNOS4_GPX3(7), S3C_GPIO_INPUT, GPIO_LV_N, S3C_GPIO_PULL_DOWN }, /* NC  TP5009 */
#else
        { EXYNOS4_GPX3(7), S3C_GPIO_INPUT, GPIO_LV_N, S3C_GPIO_PULL_NONE }, /* EAR_SNED */
#endif
};


/*EVT1 Rev0.0 (HW_REV 00) */
static struct gpio_sleep_data sleep_gpio_table_01[] = {
        { EXYNOS4_GPF2(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* BTP_OCP_EN (NC)  */
#ifdef CONFIG_MACH_MEGA2LTE_USA_ATT
        { EXYNOS4_GPK3(1), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* CODEC_LDO_EN */
        { EXYNOS4_GPM0(6), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },   /* MAIN_MIC_BIAS_EN  */
#endif
};

static struct gpio_sleep_data sleep_gpio_table_03[] = {
        { EXYNOS4_GPK1(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC */
        { EXYNOS4_GPM0(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },    /* FUEL_SCL */
        { EXYNOS4_GPM0(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },    /* SVC_LED_SCL_1.8V   */
        { EXYNOS4_GPM0(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },    /* SVC_LED_SDA_1.8V   */
        { EXYNOS4_GPM0(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE }, /*LED_BACKLIGHT_SCL_1.8V*/
        { EXYNOS4_GPM1(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC */
        { EXYNOS4_GPM1(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },   /*FUEL_SDA  */
        { EXYNOS4_GPM3(0), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE }, /* CAM_VT_nRST */
        { EXYNOS4_GPM3(1), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE },    /* 8M_CAM_RST */
        { EXYNOS4_GPF0(1), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* UART_SEL */
};

static struct gpio_sleep_data sleep_gpio_table_05[] = {
#ifdef CONFIG_MACH_MEGA2LTE_USA_ATT
        { EXYNOS4_GPB(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },	/* NC*/
        { EXYNOS4_GPC0(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },	/* NC*/
        { EXYNOS4_GPC0(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },	/* NC*/
	{ EXYNOS4_GPK1(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },    /* SVC_LED_SDA_1.8V   */
	{ EXYNOS4_GPF0(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },    /* SVC_LED_SCL_1.8V  */
#else

#endif
};

static struct gpio_sleep_data sleep_gpio_table_06[] = {
#ifdef CONFIG_MACH_MEGA2LTE_USA_ATT

#else
        { EXYNOS4_GPB(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },	/* NC*/
        { EXYNOS4_GPC0(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },	/* NC*/
        { EXYNOS4_GPC0(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },	/* NC*/
	{ EXYNOS4_GPK1(2), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* SVC_LED_SDA_1.8V   */
	{ EXYNOS4_GPF0(1), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* SVC_LED_SCL_1.8V  */
#endif
};

static struct gpio_sleep_data sleep_gpio_table_latest[] = {
        { EXYNOS4_GPA0(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },	/* BT_UART_RXD */
        { EXYNOS4_GPA0(1), S5P_GPIO_PD_OUTPUT1, S5P_GPIO_PD_UPDOWN_DISABLE },	/* BT_UART_TXD */
        { EXYNOS4_GPA0(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },	/* BT_UART_CTS */
        { EXYNOS4_GPA0(3), S5P_GPIO_PD_OUTPUT1, S5P_GPIO_PD_UPDOWN_DISABLE },/* BT_UART_RTS */
        { EXYNOS4_GPA0(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },	/* GPS_UART_RXD */
        { EXYNOS4_GPA0(5), S5P_GPIO_PD_OUTPUT1, S5P_GPIO_PD_UPDOWN_DISABLE },	/* GPS_UART_TXD */
        { EXYNOS4_GPA0(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },	/* GPS_UART_CTS */
        { EXYNOS4_GPA0(7), S5P_GPIO_PD_OUTPUT1, S5P_GPIO_PD_UPDOWN_DISABLE },/* GPS_UART_RTS */

        { EXYNOS4_GPA1(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },	/* NC*/
        { EXYNOS4_GPA1(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },	/* NC*/
        { EXYNOS4_GPA1(2), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE},	        /* TSP_SDA */
        { EXYNOS4_GPA1(3), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE },	/* TSP_SCL */
        { EXYNOS4_GPA1(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },        /* AP_UART_RXD */
        { EXYNOS4_GPA1(5), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE },        /* AP_UART_TXD */

        { EXYNOS4_GPB(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },	/* 8M_EEP_SDA*/
        { EXYNOS4_GPB(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },	/* 8M_EEP_SCL*/
        { EXYNOS4_GPB(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },	/* SENSOR_SDA_1.8V */
        { EXYNOS4_GPB(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },	/* SENSOR_SCL_1.8V */
        { EXYNOS4_GPB(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },	/* NC*/
        { EXYNOS4_GPB(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },	/* NC*/
        { EXYNOS4_GPB(6), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },	/* SVC_LED_PWR_ON*/
        { EXYNOS4_GPB(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },	/* NC*/

        { EXYNOS4_GPC0(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },	/* SVC_LED_SCL_1.8V  */
        { EXYNOS4_GPC0(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },	/* SVC_LED_SDA_1.8V  */
        { EXYNOS4_GPC0(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },	/* NC*/
        { EXYNOS4_GPC0(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },	/* NC*/
        { EXYNOS4_GPC0(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },	/* NC*/

        { EXYNOS4_GPC1(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },	/* NC*/
        { EXYNOS4_GPC1(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },	/* NC*/
        { EXYNOS4_GPC1(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },	/* NC*/
        { EXYNOS4_GPC1(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },	/* GYRO_SDA_1.8V*/
        { EXYNOS4_GPC1(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },	/* GYRO_SCL_1.8V*/

        { EXYNOS4_GPD0(0), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE }, /* PANEL_ENP */
        { EXYNOS4_GPD0(1), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE }, /* PANEL_ENN */
        { EXYNOS4_GPD0(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE }, /* NFC_SDA */
        { EXYNOS4_GPD0(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE }, /* NFC_SCL */

        { EXYNOS4_GPD1(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE }, /* AP_PMIC_SDA */
        { EXYNOS4_GPD1(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE }, /* AP_PMIC_SCL */
        { EXYNOS4_GPD1(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE }, /* CODEC_SDA_1.8V */
        { EXYNOS4_GPD1(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE }, /* CODEC_SCL_1.8V */

        { EXYNOS4_GPK0(0), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE }, /* EMMC_CLK */
        { EXYNOS4_GPK0(1), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE }, /* EMMC_CMD */
        { EXYNOS4_GPK0(2), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE }, /* EMMC_EN */
        { EXYNOS4_GPK0(3), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE }, /* EMMC_D(0)  */
        { EXYNOS4_GPK0(4), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE }, /* EMMC_D(1)  */
        { EXYNOS4_GPK0(5), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE }, /* EMMC_D(2)  */
        { EXYNOS4_GPK0(6), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE }, /* EMMC_D(3)  */
        { EXYNOS4_GPK0(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE }, /* eMMC5.0_RCLK (for Emm 5.0) */

        { EXYNOS4_GPL0(0), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE }, /* EMMC_D(4) */
        { EXYNOS4_GPL0(1), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE }, /* EMMC_D(5) */
        { EXYNOS4_GPL0(2), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE }, /* EMMC_D(6) */
        { EXYNOS4_GPL0(3), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE }, /* EMMC_D(7) */

        { EXYNOS4_GPK1(0), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE }, /* WLAN_SDIO_CLK */
        { EXYNOS4_GPK1(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE }, /* WLAN_SDIO_CMD */
        { EXYNOS4_GPK1(2), S5P_GPIO_PD_INPUT,  S5P_GPIO_PD_DOWN_ENABLE },    /* NC */
        { EXYNOS4_GPK1(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },    /* WLAN_SDIO_DAT0  */
        { EXYNOS4_GPK1(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },    /* WLAN_SDIO_DAT1  */
        { EXYNOS4_GPK1(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },    /* WLAN_SDIO_DAT2  */
        { EXYNOS4_GPK1(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },   /*WLAN_SDIO_DAT3  */

        { EXYNOS4_GPK2(0), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE }, /* T_flash_clk */
        { EXYNOS4_GPK2(1), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE }, /* T_flash_CMd */
        { EXYNOS4_GPK2(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC */
        { EXYNOS4_GPK2(3), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE },    /* T_FLASH_D_0  */
        { EXYNOS4_GPK2(4), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE },    /* T_FLASH_D_1  */
        { EXYNOS4_GPK2(5), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE },    /* T_FLASH_D_2  */
        { EXYNOS4_GPK2(6), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE },   /*T_FLASH_D_3  */

        { EXYNOS4_GPK3(0), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE }, /* AP_DUMP_INT */
#ifdef CONFIG_MACH_MEGA2LTE_USA_ATT
        { EXYNOS4_GPK3(1), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* CODEC_LDO_EN */
#else
        { EXYNOS4_GPK3(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC */
#endif
        { EXYNOS4_GPK3(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC */
        { EXYNOS4_GPK3(3), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE },    /* LCD_BLIC_ON  */
        { EXYNOS4_GPK3(4), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE },    /* CAM_SENSOR_CORE_EN  */
        { EXYNOS4_GPK3(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */
        { EXYNOS4_GPK3(6), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE },   /*LCD_nRST  */

        { EXYNOS4_GPY0(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC */
        { EXYNOS4_GPY0(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC */
        { EXYNOS4_GPY0(2), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE },    /* MMC2_EN */
        { EXYNOS4_GPY0(3), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* TF_EN  */
        { EXYNOS4_GPY0(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */
        { EXYNOS4_GPY0(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */

        { EXYNOS4_GPY1(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */

        { EXYNOS4_GPY3(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC */
        { EXYNOS4_GPY3(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC */
        { EXYNOS4_GPY3(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC */
        { EXYNOS4_GPY3(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */
        { EXYNOS4_GPY3(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */
        { EXYNOS4_GPY3(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */
        { EXYNOS4_GPY3(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */
        { EXYNOS4_GPY3(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */

        { EXYNOS4_GPY4(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC */
        { EXYNOS4_GPY4(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC */
        { EXYNOS4_GPY4(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC */
        { EXYNOS4_GPY4(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */
        { EXYNOS4_GPY4(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */
        { EXYNOS4_GPY4(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */
        { EXYNOS4_GPY4(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */
        { EXYNOS4_GPY4(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */

        { EXYNOS4_GPY5(0), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* WLAN_EN */
        { EXYNOS4_GPY5(1), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE },    /* KEY_LED_EN */
        { EXYNOS4_GPY5(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC */
        { EXYNOS4_GPY5(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */
        { EXYNOS4_GPY5(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */
        { EXYNOS4_GPY5(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */
        { EXYNOS4_GPY5(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */
        { EXYNOS4_GPY5(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */

        { EXYNOS4_GPY6(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC */
        { EXYNOS4_GPY6(1), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* BT_EN */
        { EXYNOS4_GPY6(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC */
        { EXYNOS4_GPY6(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },    /* e_FUSE_ON  */
        { EXYNOS4_GPY6(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */
        { EXYNOS4_GPY6(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */
        { EXYNOS4_GPY6(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */
        { EXYNOS4_GPY6(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */

        { EXYNOS4_GPM0(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE }, /* IF_PMIC_SCL_1.8V */
        { EXYNOS4_GPM0(1), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE },    /* MOTOR_EN */
        { EXYNOS4_GPM0(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC */
        { EXYNOS4_GPM0(3), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE }, /* CAM_VT_nRST */
        { EXYNOS4_GPM0(4), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE },    /* 8M_CAM_RST */
        { EXYNOS4_GPM0(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },   /*IF_PMIC_SDA_1.8V  */
#ifdef CONFIG_MACH_MEGA2LTE_USA_ATT
        { EXYNOS4_GPM0(6), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },   /* MAIN_MIC_BIAS_EN  */
#else
        { EXYNOS4_GPM0(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },   /*NC  */
#endif
        { EXYNOS4_GPM0(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },   /*NC  */

        { EXYNOS4_GPM1(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE }, /* LED_BACKLIGHT_SDA_1.8V */
        { EXYNOS4_GPM1(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE }, /* LED_BACKLIGHT_SCL_1.8V */
        { EXYNOS4_GPM1(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC */
        { EXYNOS4_GPM1(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },    /* TSP_ID   */
        { EXYNOS4_GPM1(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC   */
        { EXYNOS4_GPM1(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */
        { EXYNOS4_GPM1(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC  */

        { EXYNOS4_GPM2(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE }, /* MUIC_SCL */
        { EXYNOS4_GPM2(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },    /* MUIC_SDA */
        { EXYNOS4_GPM2(2), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE },    /* VT_CAM_MCLK */
        { EXYNOS4_GPM2(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC   */
        { EXYNOS4_GPM2(4), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE },    /* CAM_VT_nSTBY   */

        { EXYNOS4_GPM3(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },   /*FUEL_SCL  */
        { EXYNOS4_GPM3(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },   /*FUEL_SDA  */
        { EXYNOS4_GPM3(2), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* CAM_FLASH_EN */
        { EXYNOS4_GPM3(3), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* CAM_TORCH_EN*/
        { EXYNOS4_GPM3(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },    /* HW_REV0   */
        { EXYNOS4_GPM3(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },    /* HW_REV1   */
        { EXYNOS4_GPM3(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },    /* HW_REV2  */
        { EXYNOS4_GPM3(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },    /* HW_REV3 */

        { EXYNOS4_GPM4(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* 8M_CAM_SCL_1.8V */
        { EXYNOS4_GPM4(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* 8M_CAM_SDA_1.8V */
        { EXYNOS4_GPM4(2), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* VT_CAM_SCL_1.8V */
        { EXYNOS4_GPM4(3), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* VT_CAM_SDA_1.8V*/
        { EXYNOS4_GPM4(4), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC   */
        { EXYNOS4_GPM4(5), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC   */
        { EXYNOS4_GPM4(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC   */
        { EXYNOS4_GPM4(7), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC   */

        { EXYNOS4_GPF0(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UP_ENABLE },    /* LCD_ESD_DETECT */
        { EXYNOS4_GPF0(1), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC   */
        { EXYNOS4_GPF0(2), S5P_GPIO_PD_OUTPUT0, S5P_GPIO_PD_UPDOWN_DISABLE },    /* GPS_EN */
        { EXYNOS4_GPF0(3), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* CP_ON */
        { EXYNOS4_GPF0(4), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* NFC_EN   */
        { EXYNOS4_GPF0(5), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* NFC_FIRMWARE  */
        { EXYNOS4_GPF0(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC   */
        { EXYNOS4_GPF0(7), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* HSIC_wake_AC  */

        { EXYNOS4_GPF1(0), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* PM_DS2 */
        { EXYNOS4_GPF1(1), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* PM_DS3 */
        { EXYNOS4_GPF1(2), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* PM_DS4 */
        { EXYNOS4_GPF1(3), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* PM_DVS1 */
        { EXYNOS4_GPF1(4), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* PM_DVS2   */
        { EXYNOS4_GPF1(5), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* PM_DVS3   */

        { EXYNOS4_GPF1(6), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_UPDOWN_DISABLE },    /* COVER_ID   */
        { EXYNOS4_GPF1(7), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* HSIC_RESUME_AC  */
#ifdef CONFIG_MACH_MEGA2LTE_USA_ATT
        { EXYNOS4_GPF2(0), S5P_GPIO_PD_INPUT, S5P_GPIO_PD_DOWN_ENABLE },    /* NC   */
#else
        { EXYNOS4_GPF2(0), S5P_GPIO_PD_PREV_STATE, S5P_GPIO_PD_UPDOWN_DISABLE },    /* EAR_MICBIAS_EN */
#endif

	/********** GPX not contorled by sleep table ***************************************/

};
/***********************
ATT
REV04   : 0x5
************************/

/************************
EUR
REV00 1G : 0x0
REV00 2G : 0x1
REV01 2G : 0x2
REV01 1.5G :  0x3
REV02 1.5G :  0x4
REV03   : 0x5
REV03   : 0x6
REV04   : 0x7
*************************/
static struct sleep_gpio_table gpio_sleep_tables[] = {
        GPIO_TABLE_NULL,                    /*(0x0)*/
        GPIO_TABLE(sleep_gpio_table_01), /*(0x1) */
        GPIO_TABLE_NULL,                    /*(0x2)*/
        GPIO_TABLE(sleep_gpio_table_03), /* Rev01 1.5G (0x03) */
        GPIO_TABLE_NULL,                    /* Rev02 1.5G (0x04) */
        GPIO_TABLE(sleep_gpio_table_05),  /*(0x5)*/
        GPIO_TABLE(sleep_gpio_table_06),  /*(0x6)*/
        GPIO_TABLE(sleep_gpio_table_latest),/* Rev04 (0x07) */
};

static void __init config_init_gpio(void)
{
	u32 i;

	for (i = 0; i < ARRAY_SIZE(init_gpio_table); i++) {
		u32 gpio = init_gpio_table[i].num;
		s3c_gpio_setpull(gpio, init_gpio_table[i].pud);
		s3c_gpio_cfgpin(gpio, init_gpio_table[i].cfg);

		if (init_gpio_table[i].cfg == S3C_GPIO_OUTPUT)
			gpio_set_value(gpio, init_gpio_table[i].val);
	}
}


static void config_sleep_gpio(struct gpio_sleep_data *table, u32 arr_size)
{
	u32 i;

	for (i = 0; i < arr_size; i++) {
		s5p_gpio_set_pd_pull(table[i].num, table[i].pud);
		s5p_gpio_set_pd_cfg(table[i].num, table[i].cfg);
	}
}

static void config_sleep_gpio_tables(void)
{
        int i;
        int gpio_rev;

        i = ARRAY_SIZE(gpio_sleep_tables) - 1;

        gpio_rev = system_rev;

        if (i < gpio_rev) {
                pr_err("%s: Need sleep table : i %d - gpio_rev %d \n",
                        __func__, i, gpio_rev );
                config_sleep_gpio(sleep_gpio_table_latest,
                                ARRAY_SIZE(sleep_gpio_table_latest));
                return;
        }

        for (; i >= gpio_rev ; i--) {
                if (gpio_sleep_tables[i].table == NULL || gpio_sleep_tables[i].arr_size == 0)
                        continue;

                config_sleep_gpio(gpio_sleep_tables[i].table,
                                gpio_sleep_tables[i].arr_size);
        }

}

void (*exynos_config_sleep_gpio)(void);

void __init board_universal4415_gpio_init(void)
{
	config_init_gpio();

	exynos_config_sleep_gpio = config_sleep_gpio_tables;
}
