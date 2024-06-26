#!/bin/sh

echo "" > dummy

mkimage -f auto -A arm64 -O linux -C none -n "U-Boot" \
    -b "u-boot.dtb" -d "u-boot.bin" "u-boot-depthcharge.itb"

vbutil_kernel --version 1 --arch aarch64 \
    --vmlinuz "u-boot-depthcharge.itb" \
    --config "dummy" --bootloader "dummy" \
    --keyblock "/usr/share/vboot/devkeys/kernel.keyblock" \
    --signprivate "/usr/share/vboot/devkeys/kernel_data_key.vbprivk" \
    --pack "u-boot-depthcharge.kpart"
