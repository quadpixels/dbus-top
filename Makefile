all: dbus-top

# Edit the following two lines for use with BMC
S=$(HOME)/oecore-x86_64/environment-setup-armv7a-openbmc-linux-gnueabi
BMC_SYS_ROOT="$(HOME)/oecore-x86_64/sysroots/armv7a-openbmc-linux-gnueabi"

BMC_INCS=-I$(BMC_SYS_ROOT)/usr/include/
BMC_LIBS=-lsystemd -lncurses

CFLAGS=-std=c++17 -lsystemd -lpthread -lncurses
CFLAGS_BMC=--sysroot=$(BMC_SYS_ROOT) -march=armv7-a -std=gnu++17  -lsystemd -lpthread -lncurses

dbus-top: main.cpp
	g++ main.cpp -std=c++17 $(CFLAGS) -O2 -o $@

dbus-top_bmc: main.cpp
	@source $(S) && \
	 arm-openbmc-linux-gnueabi-g++ $(CFLAGS_BMC) $(BMC_INCS) $^ $(BMC_LIBS) -o $@ -O2


clean:
	@if [ -f dbus-top     ]; then rm -v dbus-top    ; fi
	@if [ -f dbus-top_bmc ]; then rm -v dbus-top_bmc; fi
