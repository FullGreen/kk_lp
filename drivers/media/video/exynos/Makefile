obj-$(CONFIG_VIDEO_EXYNOS5_FIMC_IS_SENSOR)	+= fimc-is-sensor/
obj-$(CONFIG_EXYNOS_MEDIA_DEVICE)	+= mdev/
obj-$(CONFIG_VIDEO_EXYNOS_MIPI_CSIS)	+= mipi-csis/
obj-$(CONFIG_VIDEO_EXYNOS_FIMC_LITE)	+= fimc-lite/
obj-$(CONFIG_VIDEO_EXYNOS_GSCALER)	+= gsc/
obj-$(CONFIG_VIDEO_EXYNOS_SCALER)	+= scaler/
obj-$(CONFIG_VIDEO_EXYNOS_JPEG)		+= jpeg/
obj-$(CONFIG_VIDEO_EXYNOS_FIMG2D)	+= fimg2d/
obj-$(CONFIG_VIDEO_EXYNOS_MFC)	+= mfc/
obj-$(CONFIG_VIDEO_EXYNOS_TV)		+= tv/
obj-$(CONFIG_VIDEO_EXYNOS_ROTATOR)	+= rotator/
ifeq ($(CONFIG_SOC_EXYNOS3250),y)
	obj-$(CONFIG_VIDEO_EXYNOS_FIMC_IS)	+= fimc-is-w1/
else ifeq ($(CONFIG_SOC_EXYNOS3472),y)
	obj-$(CONFIG_VIDEO_EXYNOS_FIMC_IS)	+= fimc-is/
else
	obj-$(CONFIG_VIDEO_EXYNOS_FIMC_IS)	+= fimc-is/
endif
obj-$(CONFIG_VIDEO_EXYNOS5_FIMC_IS)	+= fimc-is-mc2/
obj-$(CONFIG_VIDEO_EXYNOS_JPEG_HX)		+= jpeg_hx/
EXTRA_CLAGS += -Idrivers/media/video
