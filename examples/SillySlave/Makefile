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

CC = gcc
CXX = g++
LD = g++
PYTHON = python
OPT_CFLAGS = -O2
CFLAGS = $(OPT_CFLAGS)
PROG_CFLAGS = 
EXE_CFLAGS =  -lpthread -lrt -ldl
OS_NAME = Linux
ARCH_NAME = armv7l
PREFIX = /usr/local
TARGET = unix
CAN_DRIVER = can_socket
TIMERS_DRIVER = timers_unix
ENABLE_SHARED = 

INCLUDES = -I../../include -I../../include/$(TARGET) -I../../include/$(CAN_DRIVER) -I../../include/$(TIMERS_DRIVER)

SILLYSLAVE_OBJS = SillySlave.o slave.o main.o

ifeq ($(ENABLE_SHARED),1)
OBJS = $(SILLYSLAVE_OBJS) -lcanlib
else
OBJS = $(SILLYSLAVE_OBJS) ../../src/libcanfestival.a ../../drivers/$(TARGET)/libcanfestival_$(TARGET).a -lcanlib
endif

all: SillySlave

../../drivers/$(TARGET)/libcanfestival_$(TARGET).a:
	$(MAKE) -C ../../drivers/$(TARGET) libcanfestival_$(TARGET).a

ifeq($(ENABLE_SHARED),1)
SillySlave: SillySlave.c $(OBJS)
	$(LD) $(CFLAGS) $(PROG_CFLAGS) ${PROGDEFINES} $(INCLUDES) -o $@ $(OBJS) -L../../src -L../../drivers/unix -lcanfestival -lcanfestival_unix $(EXE_CFLAGS)
else
SillySlave: SillySlave.c $(OBJS)
	$(LD) $(CFLAGS) $(PROG_CFLAGS) ${PROGDEFINES} $(INCLUDES) -o $@ $(OBJS) $(EXE_CFLAGS)
endif


SillySlave.c: SillySlave.od
	$(MAKE) -C ../../objdictgen gnosis
	$(PYTHON) ../../objdictgen/objdictgen.py SillySlave.od SillySlave.c

%.o: %.c
	$(CC) $(CFLAGS) $(PROG_CFLAGS) ${PROGDEFINES} $(INCLUDES) -o $@ -c $<

clean:
	rm -f $(SILLYSLAVE_OBJS)
	rm -f SillySlave

mrproper: clean
	rm -f SillySlave.c

install: SillySlave
	mkdir -p $(PREFIX)/bin/
	cp $< $(PREFIX)/bin/

uninstall:
	rm -f $(PREFIX)/bin/SillySlave


