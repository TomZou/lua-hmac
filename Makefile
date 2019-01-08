# Inform the location to intall the modules
PWDPATH  = $(shell pwd)
LUAPATH  = $(PWDPATH)/../../lib
LUACPATH = $(PWDPATH)/../../libc

# Edit the lines below to inform new path, if necessary.
# Path below points to internal LuaSocket's help files.
INCDIR    = -I. -I$(PWDPATH)/../../../3rd/skynet/3rd/lua
LIBDIR    = -L/usr/lib -lcrypto -lssl

# For Mac OS X: set the system version
MACOSX_VERSION=10.11

#----------------------
# Do not edit this part

.PHONY: all clean install none linux bsd macosx

all: none

none:
	@echo "Usage: $(MAKE) <platform>"
	@echo "  * linux"
	@echo "  * bsd"
	@echo "  * macosx"

install:
	@cd src && $(MAKE) LUACPATH="$(LUACPATH)" LUAPATH="$(LUAPATH)" install

linux:
	@echo "---------------------"
	@echo "** Build for Linux **"
	@echo "---------------------"
	@cd src && $(MAKE) LIBDIR="$(LIBDIR)" INCDIR="$(INCDIR)" $@

macosx:
	@echo "------------------------------"
	@echo "** Build for Mac OS X $(MACOSX_VERSION) **"
	@echo "------------------------------"
	@cd src && $(MAKE) LIBDIR="$(LIBDIR)" INCDIR="$(INCDIR)" MACVER="$(MACOSX_VERSION)" $@
	
clean:
	@cd src && $(MAKE) clean
