# Makefile

obj-m += keylogger.o    # Specifies the object file for the module

# The path to the kernel source directory
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

# Default target to build the module
all:
	make -C $(KDIR) M=$(PWD) modules

# Clean target to remove compiled files
clean:
	make -C $(KDIR) M=$(PWD) clean
