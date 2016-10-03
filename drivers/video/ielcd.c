/* linux/drivers/video/ielcd.c
 *
 * Register interface file for Samsung IELCD driver
 *
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/poll.h>
#include <linux/wait.h>
#include <linux/fs.h>
#include <linux/irq.h>
#include <linux/mm.h>
#include <linux/device.h>
#include <linux/ctype.h>
#include <linux/delay.h>
#include <linux/fb.h>
#include <plat/clock.h>
#include <plat/regs-fb.h>
#include <plat/regs-fb-v4.h>
#include <plat/regs-ielcd.h>
#include <plat/regs-mdnie.h>
#include <mach/gpio.h>
#include <mach/regs-clock.h>

#include "mdnie.h"

#define FIMD_REG_BASE			S5P_PA_FIMD1
#ifdef CONFIG_FB_EXYNOS_FIMD_V8
#define FIMD_MAP_SIZE			SZ_256K
#else
#define FIMD_MAP_SIZE			SZ_32K
#endif

#define s3c_ielcd_readl(addr)		readl(s3c_ielcd_base + addr)
#define s3c_ielcd_writel(addr, val)	writel(val, s3c_ielcd_base + addr)

static void __iomem *fimd_reg;
static void __iomem *mdnie_reg;
static struct resource *s3c_ielcd_mem;
static void __iomem *s3c_ielcd_base;

int s3c_ielcd_hw_init(void)
{
	s3c_ielcd_mem = request_mem_region(S3C_IELCD_PHY_BASE, S3C_IELCD_MAP_SIZE, "ielcd");
	if (IS_ERR_OR_NULL(s3c_ielcd_mem)) {
		pr_err("%s: fail to request_mem_region\n", __func__);
		return -ENOENT;
	}

	s3c_ielcd_base = ioremap(S3C_IELCD_PHY_BASE, S3C_IELCD_MAP_SIZE);
	if (IS_ERR_OR_NULL(s3c_ielcd_base)) {
		pr_err("%s: fail to ioremap\n", __func__);
		return -ENOENT;
	}

	fimd_reg = ioremap(FIMD_REG_BASE, FIMD_MAP_SIZE);
	if (fimd_reg == NULL) {
		pr_err("%s: fail to ioremap - fimd\n", __func__);
		return -ENOENT;
	}

	mdnie_reg = ioremap(S3C_MDNIE_PHY_BASE, S3C_IELCD_MAP_SIZE);
	if (mdnie_reg == NULL) {
		pr_err("%s: fail to ioremap - mdnie\n", __func__);
		return -ENOENT;
	}

	return 0;
}

static int s3c_set_dp_mie_clkcon(int mode)
{
	void __iomem *base_reg = fimd_reg;

	writel(mode, base_reg + S3C_DP_MIE_CLKCON);

	return 0;
}

int s3c_fimd1_display_on(void)
{
	u32 cfg;
	void __iomem *base_reg = fimd_reg;

	cfg = readl(base_reg + VIDCON0);
	cfg |= (VIDCON0_ENVID | VIDCON0_ENVID_F);
	writel(cfg, base_reg + VIDCON0);

	return 0;
}

int s3c_fimd1_display_off(void)
{
	u32 cfg, active = 0, fimd_count = 0;
	void __iomem *base_reg = fimd_reg;

	/* check active area */
	cfg = readl(base_reg + VIDCON1);
	cfg &= VIDCON1_VSTATUS_MASK;
	if (cfg == VIDCON1_VSTATUS_ACTIVE)
		active = 1;

	/* FIMD per frame off in active area and direct off in non active area */
	cfg = readl(base_reg + VIDCON0);
	if (active)
		cfg &= ~(VIDCON0_ENVID_F);
	else
		cfg &= ~(VIDCON0_ENVID | VIDCON0_ENVID_F);
	writel(cfg, base_reg + VIDCON0);

	do {
		if (++fimd_count > 2000000) {
			printk(KERN_ERR "fimd off fail\n");
			return 1;
		}

		if (!(readl(base_reg + VIDCON0) & VIDCON0_ENVID_F))
			break;
	} while (1);

	return 0;
}

static void get_lcd_size(unsigned int *xres, unsigned int *yres)
{
	unsigned int cfg;
	void __iomem *base_reg = fimd_reg;

	/* LCD size setting */
	cfg = readl(base_reg + VIDTCON2);
	*xres = ((cfg & VIDTCON2_HOZVAL_MASK) >> VIDTCON2_HOZVAL_SHIFT) + 1;
	*yres = ((cfg & VIDTCON2_LINEVAL_MASK) >> VIDTCON2_LINEVAL_SHIFT) + 1;
}

static int ielcd_logic_start(void)
{
	s3c_ielcd_writel(IELCD_AUXCON, IELCD_MAGIC_KEY);

	return 0;
}

static void ielcd_set_polarity(void)
{
	unsigned int cfg;
	void __iomem *base_reg = fimd_reg;

	cfg = readl(base_reg + VIDCON1);
	cfg &= (VIDCON1_INV_VCLK | VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC | VIDCON1_INV_VDEN);
	s3c_ielcd_writel(IELCD_VIDCON1, cfg);
}

static void ielcd_set_timing(void)
{
	unsigned int cfg;
	void __iomem *base_reg = fimd_reg;

	/*LCD verical porch setting*/
	cfg = readl(base_reg + VIDTCON0);
	s3c_ielcd_writel(IELCD_VIDTCON0, cfg);

	/*LCD horizontal porch setting*/
	cfg = readl(base_reg + VIDTCON1);
	s3c_ielcd_writel(IELCD_VIDTCON1, cfg);
}

static void ielcd_set_lcd_size(unsigned int xres, unsigned int yres)
{
	unsigned int cfg;
	void __iomem *base_reg = fimd_reg;

	cfg = readl(base_reg + VIDTCON2);
	s3c_ielcd_writel(IELCD_VIDTCON2, cfg);
}

int s3c_ielcd_display_on(void)
{
	unsigned int cfg;

	cfg = s3c_ielcd_readl(IELCD_VIDCON0);
	cfg |= (VIDCON0_ENVID | VIDCON0_ENVID_F);
	s3c_ielcd_writel(IELCD_VIDCON0, cfg);

	return 0;
}

int s3c_ielcd_display_off(void)
{
	unsigned int cfg, ielcd_count = 0;

	cfg = s3c_ielcd_readl(IELCD_VIDCON0);
	cfg &= ~(VIDCON0_ENVID | VIDCON0_ENVID_F);

	s3c_ielcd_writel(IELCD_VIDCON0, cfg);

	do {
		if (++ielcd_count > 2000000) {
			pr_err("ielcd off fail\n");
			return 1;
		}

		if (!(s3c_ielcd_readl(IELCD_VIDCON1) & VIDCON1_LINECNT_MASK))
			return 0;
	} while (1);
}

static void s3c_ielcd_config_rgb(void)
{
	unsigned int cfg;
	void __iomem *base_reg = fimd_reg;

	/* vclock divider setting , same as FIMD */
	cfg = readl(base_reg + VIDCON0);
	cfg &= ~(VIDCON0_VIDOUT_MASK | VIDCON0_VCLK_MASK);
	cfg |= VIDCON0_VIDOUT_RGB;
	cfg |= VIDCON0_VCLK_NORMAL;

	s3c_ielcd_writel(IELCD_VIDCON0, cfg);
}

#ifdef CONFIG_FB_I80IF
static void s3c_ielcd_config_i80(void)
{
	unsigned int cfg;

	cfg = VIDCON0_DSI_EN;
	cfg |= VIDCON0_VIDOUT_I80_LDI0;
	cfg |= VIDCON0_CLKVALUP;
	cfg |= VIDCON0_CLKVAL_F(0);
	s3c_ielcd_writel(IELCD_VIDCON0, cfg);

	cfg = I80IFCON_CS_SETUP(1 - 1)
			| I80IFCON_WR_SETUP(0)
			| I80IFCON_WR_ACT(1)
			| I80IFCON_WR_HOLD(0)
			| I80IFCON_RS_POL(0);
	cfg |= I80IFCON_EN;
	s3c_ielcd_writel(IELCD_I80IFCONA0, cfg);
}

void s3c_ielcd_fimd_instance_off(void)
{
	unsigned int cfg;
	void __iomem *base_reg = fimd_reg;

	cfg = readl(base_reg + VIDCON0);
	cfg &= ~(VIDCON0_ENVID | VIDCON0_ENVID_F);
	writel(cfg, base_reg + VIDCON0);

	cfg = s3c_ielcd_readl(IELCD_VIDCON0);
	cfg &= ~(VIDCON0_ENVID | VIDCON0_ENVID_F);
	s3c_ielcd_writel(IELCD_VIDCON0, cfg);
}

void s3c_ielcd_hw_trigger_set(void)
{
	unsigned int cfg;
	void __iomem *base_reg = fimd_reg;
	void __iomem *temp_base_reg = mdnie_reg;

	writel(0x77, temp_base_reg+0x4);
	writel(0x0, temp_base_reg+0x3fc);

	writel(0x80000008, base_reg + TRIGCON);

	cfg = readl(base_reg + VIDCON0);
	cfg |= (VIDCON0_ENVID | VIDCON0_ENVID_F);
	writel(cfg, base_reg + VIDCON0);

	cfg = s3c_ielcd_readl(IELCD_TRIGCON);
	cfg |= (SWTRGCMD_I80_RGB | TRGMODE_I80_RGB);
	s3c_ielcd_writel(IELCD_TRIGCON, cfg);

	cfg = s3c_ielcd_readl(IELCD_VIDCON0);
	cfg |= (VIDCON0_ENVID | VIDCON0_ENVID_F);
	s3c_ielcd_writel(IELCD_VIDCON0, cfg);

	cfg = s3c_ielcd_readl(IELCD_SHADOWCON);
	cfg |= IELCD_W0_SW_SHADOW_UPTRIG;
	s3c_ielcd_writel(IELCD_SHADOWCON, cfg);

	cfg = s3c_ielcd_readl(IELCD_VIDCON0);
	cfg |= IELCD_SW_SHADOW_UPTRIG;
	s3c_ielcd_writel(IELCD_VIDCON0, cfg);

	cfg = s3c_ielcd_readl(IELCD_TRIGCON);
	cfg &= ~(SWTRGCMD_I80_RGB | TRGMODE_I80_RGB);
	cfg |= (HWTRGMASK_I80_RGB | HWTRGEN_I80_RGB);
	s3c_ielcd_writel(IELCD_TRIGCON, cfg);
}
#endif

int s3c_ielcd_setup(void)
{
	unsigned int cfg, xres, yres;
	void __iomem *base_reg = fimd_reg;

	cfg = readl(base_reg + VIDCON0);
	cfg |= VIDCON0_VCLKFREE;
	writel(cfg, base_reg + VIDCON0);

	s3c_set_dp_mie_clkcon(S3C_DP_MIE_CLKCON_MDNIE);

	get_lcd_size(&xres, &yres);

	ielcd_logic_start();

	ielcd_set_polarity();
	ielcd_set_timing();
	ielcd_set_lcd_size(xres, yres);

	/* window0 setting , fixed */
	cfg = WINCONx_ENLOCAL | WINCON2_BPPMODE_24BPP_888 | WINCONx_ENWIN;
	s3c_ielcd_writel(IELCD_WINCON0, cfg);

	/* window0 position setting */
	s3c_ielcd_writel(IELCD_VIDOSD0A, 0);
	cfg = ((xres - 1) << 11) | ((yres - 1) << 0);
	s3c_ielcd_writel(IELCD_VIDOSD0B, cfg);

	/* window0 osd size setting */
	s3c_ielcd_writel(IELCD_VIDOSD0C, xres * yres);

	/* window0 page size(bytes) */
	s3c_ielcd_writel(IELCD_VIDW00ADD2, xres * 4);

#ifdef CONFIG_FB_I80IF
	s3c_ielcd_config_i80();
#else
	s3c_ielcd_config_rgb();
#endif

	return 0;
}
