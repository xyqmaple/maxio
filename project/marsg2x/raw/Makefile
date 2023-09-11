-include .config

ifeq ("$(origin V)","command line")
BUILD_VERBOSE := $(V)
endif
ifndef BUILD_VERBOSE
BUILD_VERBOSE := 0
endif

ifeq ($(BUILD_VERBOSE),1)
Q :=
else
Q := @
endif

export Q

MCONF := ../scripts/kconfig/mconf
$(MCONF):
	$(Q)make CC=gcc HOSTCC=gcc -C ../scripts/kconfig
menuconfig: $(MCONF)
	$(Q)rm -rf ./include
	$(Q)$(MCONF) Kconfig

distclean:
	$(Q)make CC=gcc HOSTCC=gcc -C ../scripts/kconfig distclean
	$(Q)rm -rf ./include

.PHONY: menuconfig distclean

