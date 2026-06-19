cmd_drivers/thermal/built-in.o :=  arm-none-eabi-ld -EL   -r -o drivers/thermal/built-in.o drivers/thermal/thermal_sys.o drivers/thermal/step_wise.o 
