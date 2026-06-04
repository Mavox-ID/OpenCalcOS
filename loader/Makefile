#    Mavox-ID | https://ye-a.pp.ua
#    Copyright (C) 2026  Mavox-ID
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.

GCC = nspire-gcc
NDLESS_SDK = ../ndless/ndless-sdk
LD = nspire-gcc
GCCFLAGS = -Os -nostdlib -Wall -W -marm -I../ndless/ndless-sdk/include
LDFLAGS = -T nspire.ld -L$(NDLESS_SDK)/lib -L$(NDLESS_SDK)/thirdparty/nspire-io/lib -Wl,--start-group -lndls -lsyscalls -lnspireio -Wl,--end-group
OBJCOPY := "$(shell which arm-elf-objcopy 2>/dev/null)"
ifeq (${OBJCOPY},"")
	OBJCOPY := arm-none-eabi-objcopy
endif
EXE = loader.tns
OBJS = $(patsubst %.c,%.o,$(wildcard *.c))
OBJS += $(patsubst %.S,%.o,$(wildcard *.S))
DISTDIR = .
vpath %.tns $(DISTDIR)

all: $(EXE)

%.o: %.c
	$(GCC) $(GCCFLAGS) -c $<

%.o: %.S
	$(GCC) $(GCCFLAGS) -c $<

$(EXE): $(OBJS)
	$(LD) $^ -o $(@:.tns=.elf) $(LDFLAGS)
	mkdir -p $(DISTDIR)
	$(OBJCOPY) -O binary $(@:.tns=.elf) $(DISTDIR)/$@

clean:
	rm -f *.o *.elf
	rm -f $(DISTDIR)/$(EXE)
