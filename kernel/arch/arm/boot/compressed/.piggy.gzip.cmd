cmd_arch/arm/boot/compressed/piggy.gzip := (cat arch/arm/boot/compressed/../Calc | gzip -n -f -9 > arch/arm/boot/compressed/piggy.gzip) || (rm -f arch/arm/boot/compressed/piggy.gzip ; false)
