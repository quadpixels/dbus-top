all: dbus-top

# Edit the following two lines for use with BMC
# Note: because hwmon_bmk_bmc depends on libboost_system, you might need to copy
# its runtime library to the BMC as well.
S=$(HOME)/oecore-x86_64/environment-setup-armv7a-openbmc-linux-gnueabi
BMC_SYS_ROOT="$(HOME)/oecore-x86_64/sysroots/armv7a-openbmc-linux-gnueabi"

BMC_INCS=-I$(BMC_SYS_ROOT)/usr/include/
BMC_LIBS=$(HOME)/Downloads/AsioUring/build_bmc/libasio_uring_asio.a $(HOME)/Downloads/AsioUring/build_bmc/libasio_uring_core.a $(HOME)/Downloads/liburing-0.1/build_bmc/liburing.a

# ASIO_URing
ASIO_URING_CFLAGS=-DBOOST_ALL_NO_LIB -DBOOST_SYSTEM_DYN_LINK -I$(HOME)/Downloads/AsioUring/src/asio/include -I$(HOME)/Downloads/AsioUring/src/core/include -isystem $(HOME)/Downloads/liburing-0.1/src/include  -std=gnu++17 $(HOME)/Downloads/AsioUring/build/bin/libasio_uring_asio.a $(HOME)/Downloads/AsioUring/build/bin/libasio_uring_core.a -lpthread /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0 $(HOME)/Downloads/liburing-0.1/build/liburing.a
ASIO_URING_CFLAGS_BMC=--sysroot=$(BMC_SYS_ROOT) -march=armv7-a -DBOOST_ALL_NO_LIB -DBOOST_SYSTEM_DYN_LINK -I$(HOME)/Downloads/AsioUring/src/asio/include -I$(HOME)/Downloads/AsioUring/src/core/include -isystem $(HOME)/Downloads/liburing-0.1/src/include -std=gnu++17 -lpthread -lboost_system

dbus-top: main.cpp
	g++ main.cpp -std=c++17 -O2 -o $@

dbus-top_bmc: main.cpp
	@source $(S) && \
	 arm-openbmc-linux-gnueabi-g++ $(BMC_INCS) $(ASIO_URING_CFLAGS_BMC) $^ $(BMC_LIBS) -o $@ -O2


clean:
	@if [ -f dbus-top ]; then rm -v dbus-top; fi
