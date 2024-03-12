
src := $(obj)
PHONY := __build
__build:

obj-y :=
lib-y :=
app-y :=
targets :=
ccflags-y :=
ldflags-y :=
ldlibs-y :=

ifeq ($(strip $(src)),src/app)
ccflags-y += $(BUILD_CFLAGS_LIBS)
ldflags-y += $(BUILD_LDFLAGS_LIBS)
ldlibs-y += $(BUILD_LDLIBS_LIBS)
endif

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

$(obj)/%.o: $(src)/%.c FORCE
	$(cmd_cc_o_c)

$(obj)/built-in.a: $(real-obj-y) FORCE
	$(cmd_ar)

$(obj)/%.a: $(real-lib-y) FORCE
	$(cmd_ar)

ibex: $(real-app-y) FORCE
	$(cmd_cc_elf_o)

PHONY += $(subdir-y)
$(subdir-y):
	$(MAKE) $(build)=$@

__build: $(targets) $(subdir-y)

# Add FORCE to the prequisites of a target to force it to be always rebuilt.
PHONY += FORCE
FORCE:

.PHONY: $(PHONY)
