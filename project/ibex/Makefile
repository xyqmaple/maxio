
PHONY := build
build:

ifeq ("$(origin V)","command line")
BUILD_VERBOSE = $(V)
endif
ifndef BUILD_VERBOSE
BUILD_VERBOSE = 0
endif
ifeq ($(BUILD_VERBOSE),1)
Q =
else
Q = @
endif

abs_srctree := $(realpath $(dir $(lastword $(MAKEFILE_LIST))))
srctree := .
export srctree

MAKE		:= make
RM		:= rm
export RM

CROSS_COMPILE	:=
CC		:= $(CROSS_COMPILE)gcc
LD		:= $(CROSS_COMPILE)ld
AR		:= $(CROSS_COMPILE)ar
NM		:= $(CROSS_COMPILE)nm
OBJCOPY		:= $(CROSS_COMPILE)objcopy
OBJDUMP		:= $(CROSS_COMPILE)objdump
READELF		:= $(CROSS_COMPILE)readelf
export CC LD AR NM OBJCOPY OBJDUMP READELF

libs-subdirs	:= $(filter-out $(srctree)/lib,\
	$(shell find $(srctree)/lib -maxdepth 1 -type d))
BUILD_CFLAGS_LIBS	:= $(addprefix -I,$(libs-subdirs))
BUILD_LDFLAGS_LIBS	:= $(addprefix -L,$(libs-subdirs))
BUILD_LDLIBS_LIBS	:= $(addprefix -l,$(notdir $(libs-subdirs)))

export BUILD_CFLAGS_LIBS BUILD_LDFLAGS_LIBS BUILD_LDLIBS_LIBS

include scripts/include.mk

app-y		:= src/app/
libs-y		:= lib/
build-dirs	:= $(patsubst %/,%,$(filter %/,$(libs-y)))
build-dirs-last	:= $(patsubst %/,%,$(filter %/,$(app-y)))
clean-dirs	:= $(patsubst %/,%,$(filter %/,$(app-y) $(libs-y)))
clean-dirs	:= $(addprefix _clean_,$(clean-dirs))

$(build-dirs): FORCE
	$(MAKE) $(build)=$@

$(build-dirs-last): FORCE
	$(MAKE) $(build)=$@

$(clean-dirs): FORCE
	$(MAKE) $(clean)=$(patsubst _clean_%,%,$@)

PHONY += $(build-dirs) $(build-dirs-last)
build: $(build-dirs) $(build-dirs-last)

PHONY += $(clean-dirs) clean
clean: $(clean-dirs)

# Add FORCE to the prequisites of a target to force it to be always rebuilt.
PHONY += FORCE
FORCE:

.PHONY: $(PHONY)
