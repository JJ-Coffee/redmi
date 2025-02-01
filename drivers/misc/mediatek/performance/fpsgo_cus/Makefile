FBT_TOP = $(srctree)/drivers/misc/mediatek/performance/fpsgo_v3/fbt
MTK_TOP = $(srctree)/drivers/misc/mediatek

ifeq ($(CONFIG_MTK_FPSGO_V3),$(filter $(CONFIG_MTK_FPSGO_V3),m))
ccflags-y += -DCONFIG_MTK_FPSGO_V3
subdir-ccflags-y += -DCONFIG_MTK_FPSGO_V3
endif

ccflags-y += \
	     -I$(srctree)/include/ \
	     -I$(MTK_TOP)/include/ \
	     -I$(FBT_TOP)/include/ \

obj-m += fpsgo.o
fpsgo-y += src/fpsgo_main.o

ifeq (y,$(CONFIG_MTK_FPSGO_V3))
	ifeq (y,$(CONFIG_THUMB2_KERNEL))
		fpsgo-y += src/xgf_v3_ko_thumb2.o
	else
		fpsgo-$(CONFIG_ARM) += src/xgf_v3_ko_arm32.o
		ifeq (y,$(CONFIG_CFI_CLANG))
			ifeq (y,$(CONFIG_CFI_PERMISSIVE))
				fpsgo-$(CONFIG_ARM64) += src/xgf_v3_ko_arm64_cfi_d.o
			else
				fpsgo-$(CONFIG_ARM64) += src/xgf_v3_ko_arm64_cfi.o
			endif
		else
			fpsgo-$(CONFIG_ARM64) += src/xgf_v3_ko_arm64.o
		endif
	endif
else
	ifeq (m,$(CONFIG_MTK_FPSGO_V3))
		fpsgo-y += src/xgf_v3_ko_quark.o
	endif
endif

# A dummy target that always runs (forcing a rebuild if needed)
FORCE:

# Rule to copy the prebuilt object into the output directory
$(obj)/src/xgf_v3_ko_arm64.o: FORCE
	@echo "Copying prebuilt xgf_v3_ko_arm64.o..."
	cp $(srctree)/drivers/misc/mediatek/performance/fpsgo_cus/src/xgf_v3_ko_arm64.o $@

# Ensure the proper dependency for the target 'fpsgo.o'
$(obj)/fpsgo.o: $(obj)/src/xgf_v3_ko_arm64.o
