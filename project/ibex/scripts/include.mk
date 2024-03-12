
#
# Real prereqquisites without PHONY targets
#
real-prereqs = $(filter-out $(PHONY), $^)

#
# Shorthand for $(Q)$(MAKE) -f scripts/build.mk obj=
# Usage: $(Q)$(MAKE) $(build)=dir
#
build := -f $(srctree)/scripts/build.mk obj

#
# Shorthand for $(Q)$(MAKE) -f scripts/clean.mk obj=
# Usage: $(Q)$(MAKE) $(clean)=dir
#
clean := -f $(srctree)/scripts/clean.mk obj
