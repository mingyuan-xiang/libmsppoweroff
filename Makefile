LIB = libmsppoweroff

OBJECTS = poweroff.o

DEPS += libmsp

override SRC_ROOT = ../../src

override CFLAGS += \
	-I$(SRC_ROOT)/include/libmsptimer \

include $(MAKER_ROOT)/Makefile.$(TOOLCHAIN)
