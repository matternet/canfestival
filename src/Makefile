#! gmake

#
# Copyright (C) 2006 Laurent Bessard
#
# This file is part of canfestival, a library implementing the canopen
# stack
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

ifneq ($(KERNELRELEASE),)
# Kbuild part of Makefile
obj-m := canfestival.o
canfestival-objs := $(OBJS)

else
# Normal Makefile
CC = gcc
PROG_CFLAGS = 
OS_NAME = Linux
ARCH_NAME = armv7l
PREFIX = /usr/local
BINUTILS_PREFIX = 
TARGET = unix
CAN_DRIVER = can_socket
TIMERS_DRIVER = timers_unix
ENABLE_LSS = 0
ENABLE_SHARED = 

INCLUDES = -I../include -I../include/$(TARGET) -I../include/$(TIMERS_DRIVER) -I../drivers/$(TARGET)

OBJS = $(TARGET)_objacces.o $(TARGET)_lifegrd.o $(TARGET)_sdo.o \
	   $(TARGET)_pdo.o $(TARGET)_sync.o $(TARGET)_nmtSlave.o $(TARGET)_nmtMaster.o $(TARGET)_states.o $(TARGET)_timer.o $(TARGET)_dcf.o $(TARGET)_emcy.o


ifeq ($(ENABLE_LSS),1)
OBJS += $(TARGET)_lss.o
endif

# # # # Target specific parameters # # # #

ifeq ($(TARGET),hcs12)
OPT_CFLAGS = -Os
PROGDEFINES = -mnoshort -Wall -Wmissing-prototypes -fno-strict-aliasing
endif

ifeq ($(TARGET),cm4)
  OBJS += ../drivers/cm4/cm4.o
  LIB_ROOT = ../../include/cm4/stlib
  INCLUDES += -I$(LIB_ROOT)/STM32F37x_StdPeriph_Driver/inc \
              -I$(LIB_ROOT)/CMSIS/Include \
              -I$(LIB_ROOT)/CMSIS/Device/ST/STM32F37x/Include
  PROGDEFINES = -DSTM32F3XX -DUSE_STDPERIPH_DRIVER
endif

ifeq ($(TARGET),unix)
OPT_CFLAGS = -fPIC -O2
endif

# # # # Options # # # #

all: canfestival

ifeq ($(TIMERS_DRIVER), timers_kernel)
USE_KERNEL_TIMER = true
endif
ifeq ($(TIMERS_DRIVER), timers_kernel_xeno)
USE_KERNEL_TIMER = true
endif

ifeq ($(USE_KERNEL_TIMER), true)
OBJS := $(shell echo $(OBJS) | sed "s:$(TARGET)_::g")
OBJS += symbols.o
OBJS += ../drivers/unix/libcanfestival_$(TARGET).o
EXTRA_CFLAGS := $(shell echo $(INCLUDES) | sed "s:-I:-I$(src)/:g")
EXTRA_CFLAGS += $(PROG_CFLAGS)
KERNELDIR := 
export OBJS
export EXTRA_CFLAGS

canfestival:
	@echo " "
	@echo "*********************************************"
	@echo "**Building [canfestival.o]"
	@echo "*********************************************"
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) clean
	rm -f Module.symvers

install:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) modules_install
	mkdir -p $(PREFIX)/include/canfestival
	cp ../include/*.h $(PREFIX)/include/canfestival

uninstall:
	rm -rf $(PREFIX)/include/canfestival

else
CFLAGS = $(OPT_CFLAGS)

ifeq ($(TARGET),none)
canfestival: libcanfestival.o
else
ifeq ($(ENABLE_SHARED),1)
canfestival: libcanfestival.so
else
canfestival: libcanfestival.a
endif
endif

libcanfestival.so: $(OBJS)
	@echo " "
	@echo "*********************************************"
	@echo "**Building [libcanfestival.so]"
	@echo "*********************************************"
	$(CC) -shared -Wl,-soname,$@ -o $@  $(OBJS)

libcanfestival.a: $(OBJS)
	@echo " "
	@echo "*********************************************"
	@echo "**Building [libcanfestival.a]"
	@echo "*********************************************"
	$(BINUTILS_PREFIX)ar rc $@ $(OBJS)
	$(BINUTILS_PREFIX)ranlib $@

libcanfestival.o: $(OBJS)
	@echo " "
	@echo "*********************************************"
	@echo "**Prelink [libcanfestival.o]"
	@echo "*********************************************"
	$(BINUTILS_PREFIX)ld -r $(OBJS) -o $@

$(TARGET)_%.o: %.c
	@echo " "
	@echo "*********************************************"
	@echo "**Compiling $< -> $@"
	@echo "*********************************************"
	$(CC) $(CFLAGS) $(PROG_CFLAGS) ${PROGDEFINES} $(INCLUDES) -o $@ -c $<

ifeq ($(ENABLE_SHARED),1)
install: libcanfestival.so
	mkdir -p $(PREFIX)/lib/
	mkdir -p $(PREFIX)/include/canfestival
	cp libcanfestival.so $(PREFIX)/lib/
	cp canfestival.pc $(PREFIX)/lib/pkgconfig
	cp ../include/*.h $(PREFIX)/include/canfestival
else
install: libcanfestival.a
	mkdir -p $(PREFIX)/lib/
	mkdir -p $(PREFIX)/include/canfestival
	cp libcanfestival.a $(PREFIX)/lib/
	cp canfestival.pc $(PREFIX)/lib/pkgconfig
	cp ../include/*.h $(PREFIX)/include/canfestival
endif

uninstall:
	rm -f $(PREFIX)/lib/libcanfestival.a
	rm -f $(PREFIX)/lib/libcanfestival.so
	rm -rf $(PREFIX)/include/canfestival

clean:
	rm -f $(OBJS) libcanfestival.a libcanfestival.o libcanfestival.so

endif
mrproper: clean

endif
