#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const char ____versions[]
__used __section("__versions") =
	"\x10\x00\x00\x00\xd8\x7e\x99\x92"
	"_printk\0"
	"\x18\x00\x00\x00\xe1\xbe\x10\x6b"
	"_copy_to_user\0\0\0"
	"\x1c\x00\x00\x00\xcb\xf6\xfd\xf0"
	"__stack_chk_fail\0\0\0\0"
	"\x18\x00\x00\x00\xa5\xc7\x6d\x32"
	"device_destroy\0\0"
	"\x1c\x00\x00\x00\x4e\x31\xbc\x33"
	"class_unregister\0\0\0\0"
	"\x18\x00\x00\x00\xf8\xe3\xc3\xf4"
	"class_destroy\0\0\0"
	"\x1c\x00\x00\x00\xc0\xfb\xc3\x6b"
	"__unregister_chrdev\0"
	"\x14\x00\x00\x00\x52\x00\x99\xfe"
	"gpio_free\0\0\0"
	"\x18\x00\x00\x00\x5c\x9b\x22\x47"
	"gpio_request\0\0\0\0"
	"\x18\x00\x00\x00\xfd\x9e\x3e\x4f"
	"gpio_to_desc\0\0\0\0"
	"\x24\x00\x00\x00\xbe\x8c\xe6\x9f"
	"gpiod_direction_output_raw\0\0"
	"\x1c\x00\x00\x00\x85\x29\xca\x91"
	"__register_chrdev\0\0\0"
	"\x18\x00\x00\x00\xf2\xe1\xff\x52"
	"class_create\0\0\0\0"
	"\x18\x00\x00\x00\x2b\x15\x5b\x4d"
	"device_create\0\0\0"
	"\x1c\x00\x00\x00\x48\x9f\xdb\x88"
	"__check_object_size\0"
	"\x18\x00\x00\x00\xc2\x9c\xc4\x13"
	"_copy_from_user\0"
	"\x1c\x00\x00\x00\xe3\xbd\x58\xb4"
	"gpiod_set_raw_value\0"
	"\x18\x00\x00\x00\x99\xb6\xcd\x7e"
	"param_ops_int\0\0\0"
	"\x18\x00\x00\x00\xbd\xf6\x3d\x29"
	"module_layout\0\0\0"
	"\x00\x00\x00\x00\x00\x00\x00\x00";

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "05862B16431090A5DFD35E0");
