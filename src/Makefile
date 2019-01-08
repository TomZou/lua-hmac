CMOD = hmac.so

OBJS = hmac.o

#----------------------

LNX_CFLAGS = -O2 -g -fPIC -Wall -pedantic $(INCDIR)
LNX_LDFLAGS = -O -g -shared -fPIC $(LIBDIR)

MAC_ENV=env MACOSX_DEPLOYMENT_TARGET='$(MACVER)'
MAC_CFLAGS=-O2 -fno-common $(WARN) $(INCDIR) -I/usr/local/opt/openssl/include $(DEFS)
MAC_LDFLAGS=-bundle -undefined dynamic_lookup -L/usr/local/opt/openssl/lib

#----------------------

INSTALL  = install
CC       = g++
CFLAGS  += $(MYCFLAGS)
LDFLAGS += $(MYLDFLAGS)

.PHONY: all clean install none linux bsd macosx luasocket

all:

install: $(CMOD)
	$(INSTALL) $(CMOD) $(LUACPATH)

linux:
	@echo "linux $(MYCFLAGS)"
	@echo "linux $(LNX_CFLAGS)"
	@echo "linux $(LNX_LDFLAGS)"
	@$(MAKE) $(CMOD) MYCFLAGS="$(LNX_CFLAGS)" MYLDFLAGS="$(LNX_LDFLAGS)"

macosx:
	@$(MAKE) $(CMOD) MYCFLAGS="$(MAC_CFLAGS)" MYLDFLAGS="$(MAC_LDFLAGS)" MYENV="$(MAC_ENV)"

$(CMOD): $(OBJS)
	@echo "OBJS $(LDFLAGS)"
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

clean:
	rm -f $(OBJS) $(CMOD)

%.o : %.cpp
	@echo "CC -------------- $(CFLAGS)"
	$(CC) $(CFLAGS) -c $^ -o $@
