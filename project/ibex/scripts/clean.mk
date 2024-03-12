
src := $(obj)
PHONY := __clean
__clean:

obj-y :=
lib-y :=
app-y :=
targets :=
ccflags-y :=
ldflags-y :=
ldlibs-y :=

include scripts/include.mk

build-dir := $(if $(filter /%,$(src)),$(src),$(srctree)/$(src))
build-file := $(build-dir)/Makefile
include $(build-file)
include scripts/library.mk

# Subdirectories we need to descend into
subdir-y := $(sort $(patsubst %/,%,$(filter %/,$(obj-y))))

# Replace multi-part objects by their individual parts, 
# including built-in.a from subdirectories
real-obj-y := $(foreach m,$(filter-out %/,$(obj-y)),$(if $(strip $($(m:.o=-y))),$($(m:.o=-y)),$(m)))
real-lib-y := $(foreach m,$(lib-y),$(if $(strip $($(m:.o=-y))),$($(m:.o=-y)),$(m)))
real-app-y := $(foreach m,$(app-y),$(if $(strip $($(m:.o=-y))),$($(m:.o=-y)),$(m)))

# Add subdir path
real-lib-y	:= $(addprefix $(obj)/,$(real-lib-y))
real-obj-y	:= $(addprefix $(obj)/,$(real-obj-y))
real-app-y	:= $(addprefix $(obj)/,$(real-app-y))
subdir-y	:= $(addprefix $(obj)/,$(subdir-y))

ifneq ($(strip $(real-lib-y)),)
targets += $(obj)/lib$(notdir $(obj)).a
endif
ifneq ($(strip $(real-app-y)),)
targets += ibex
endif

PHONY += $(subdir-y)
$(subdir-y):
	$(MAKE) $(clean)=$@

__clean: $(subdir-y)
	$(RM) -f $(targets) $(real-lib-y) $(real-obj-y) $(real-app-y)

# Add FORCE to the prequisites of a target to force it to be always rebuilt.
PHONY += FORCE
FORCE:

.PHONY: $(PHONY)
