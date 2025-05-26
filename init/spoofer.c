// spoof_props.c
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/property.h>

static int __init spoof_properties_init(void)
{
	add_device_property(NULL, "ro.boot.verifiedbootstate", "green");
	add_device_property(NULL, "ro.secureboot.lockstate", "locked");
	add_device_property(NULL, "ro.boot.flash.locked", "1");
	add_device_property(NULL, "ro.boot.vbmeta.device_state", "locked");
	add_device_property(NULL, "ro.boot.veritymode", "enforcing");
	add_device_property(NULL, "sys.oem_unlock_allowed", "0");

	pr_info("Spoofed sensitive props for PlayIntegrity\n");
	return 0;
}

late_initcall(spoof_properties_init);
