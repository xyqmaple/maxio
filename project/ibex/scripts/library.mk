

c_flags		= $(BUILD_CFLAGS) $(ccflags-y)
ld_flags 	= $(BUILD_LDFLAGS) $(ldflags-y)
ld_libs		= $(BUILD_LDLIBS) $(ldlibs-y)

# Archive
cmd_ar = $(RM) -f $@; $(AR) rcs $@ $(real-prereqs)

# C(.c) files
cmd_cc_o_c = $(CC) $(c_flags) -c -o $@ $<

cmd_cc_elf_o = $(CC) $(ld_flags) $(real-prereqs) $(ld_libs) -o $@
