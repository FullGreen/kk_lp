/*
 * Driver for Samsung SoC onboard UARTs.
 *
 * Ben Dooks, Copyright (c) 2003-2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

struct s3c24xx_uart_info {
	char			*name;
	unsigned int		type;
	unsigned int		fifosize;
	unsigned long		rx_fifomask;
	unsigned long		rx_fifoshift;
	unsigned long		rx_fifofull;
	unsigned long		tx_fifomask;
	unsigned long		tx_fifoshift;
	unsigned long		tx_fifofull;
	unsigned int		def_clk_sel;
	unsigned long		num_clks;
	unsigned long		clksel_mask;
	unsigned long		clksel_shift;

	/* uart port features */

	unsigned int		has_divslot:1;

	/* uart controls */
	int (*reset_port)(struct uart_port *, struct s3c2410_uartcfg *);
};

#ifdef CONFIG_SERIAL_SAMSUNG_DMA
struct uart_dma_data {
        unsigned ch;
	unsigned int busy;
	unsigned int req_size;
        unsigned long fifo_base;
        enum dma_ch req_ch;
	enum dma_transfer_direction direction;
};

struct exynos_uart_dma {
	unsigned int use_dma;

	dma_addr_t tx_src_addr;
	dma_addr_t rx_dst_addr;

        struct uart_dma_data tx;
        struct uart_dma_data rx;

        struct samsung_dma_ops *ops;

        char *rx_buff;
};
#endif

struct s3c24xx_serial_drv_data {
	struct s3c24xx_uart_info	*info;
	struct s3c2410_uartcfg		*def_cfg;
	unsigned int			fifosize[CONFIG_SERIAL_SAMSUNG_UARTS];
};

struct s3c24xx_uart_port {
	unsigned char			rx_claimed;
	unsigned char			tx_claimed;
	unsigned long			baudclk_rate;

	unsigned int			rx_irq;
	unsigned int			tx_irq;

#ifdef CONFIG_SERIAL_SAMSUNG_DMA
	unsigned int                    err_irq;
	unsigned int                    err_occurred;
#endif
	struct s3c24xx_uart_info	*info;
	struct clk			*clk;
	struct clk			*baudclk;
	struct uart_port		port;
#ifdef CONFIG_SERIAL_SAMSUNG_DMA
        struct exynos_uart_dma          uart_dma;
#endif
	struct s3c24xx_serial_drv_data	*drv_data;

	/* reference to platform data */
	struct s3c2410_uartcfg		*cfg;

	struct notifier_block		aud_uart_notifier;
	struct delayed_work			qos_work;
};

/* conversion functions */

#define s3c24xx_dev_to_port(__dev) (struct uart_port *)dev_get_drvdata(__dev)

/* register access controls */

#define portaddr(port, reg) ((port)->membase + (reg))
#define portaddrl(port, reg) ((unsigned long *)((port)->membase + (reg)))

#define rd_regb(port, reg) (__raw_readb(portaddr(port, reg)))
#define rd_regl(port, reg) (__raw_readl(portaddr(port, reg)))

#define wr_regb(port, reg, val) __raw_writeb(val, portaddr(port, reg))
#define wr_regl(port, reg, val) __raw_writel(val, portaddr(port, reg))

#ifdef CONFIG_SERIAL_SAMSUNG_DEBUG

extern void printascii(const char *);

static void dbg(const char *fmt, ...)
{
	va_list va;
	char buff[256];

	va_start(va, fmt);
	vsprintf(buff, fmt, va);
	va_end(va);

	printascii(buff);
}

#else
#define dbg(x...) do { } while (0)
#endif
