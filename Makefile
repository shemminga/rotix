##########################
#   Makefile for Rotix   #
##########################
#
#	Rotix - A program to generate rotational obfuscations
#	Copyright (C) 2001  Sjoerd Hemminga <sjoerd@huiswerkservice.nl>
#
#	This program is free software; you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation; either version 2 of the License, or
#	(at your option) any later version.
#
#	This program is distributed in the hope that it will be useful, but
#	WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
#	General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with this program; if not, write to the Free Software
#	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
#	USA 

include Makefile.settings

ifdef DEBUG
CFLAGS += -g3
else
CFLAGS += -O3
endif

ifdef I18N
CFLAGS += -DPACKAGE=\"${PACKAGE}\" -D LOCALEDIR=\"${LOCALE}\"
endif

ifdef NO_GETOPT_LONG
CFLAGS += -D NO_GETOPT_LONG=1
endif

all : rotix po

rotix : rot.o help.o rotix.o
	$(CC) -Wall $(CFLAGS) -o rotix rot.o help.o rotix.o
ifdef STRIP
ifndef DEBUG
	$(STRIP) rotix
endif
endif

ifdef I18N
CFLAGS += -D I18N=1
endif

rot.o : rot.c
	$(CC) -Wall $(CFLAGS) -c rot.c

help.o : help.c
	$(CC) -Wall $(CFLAGS) -c help.c

rotix.o : rotix.c
	$(CC) -Wall $(CFLAGS) -c rotix.c

po : po/NL.mo

po/NL.mo : po/NL.po
	msgfmt -o po/NL.mo po/NL.po

.PHONY : clean rmbin distclean cleanall

cleanall : distclean

distclean : clean rmbin
	rm Makefile.settings

clean :
	rm -f *.o

rmbin :
	rm -f rotix
	rm -f po/*.mo

install: rotix po
	mkdir -p $(DESTDIR)$(BINDIR)
	cp rotix $(DESTDIR)$(BINDIR)
	chmod 0755 $(DESTDIR)$(BINDIR)/rotix
	mkdir -p $(DESTDIR)$(MANDIR)/man1
	cp rotix.1 $(DESTDIR)$(MANDIR)/man1
	chmod 0644 $(DESTDIR)$(MANDIR)/man1/rotix.1
ifdef I18N
	mkdir -p $(DESTDIR)$(LOCALE)/nl/LC_MESSAGES
	cp po/NL.mo $(DESTDIR)$(LOCALE)/nl/LC_MESSAGES/rotix.mo
	chmod 0644 $(DESTDIR)$(LOCALE)/nl/LC_MESSAGES/rotix.mo
endif
	
uninstall:
	rm -f $(DESTDIR)$(BINDIR)/rotix
	rm -f $(DESTDIR)$(MANDIR)/man1/rotix.1
ifdef I18N
	rm -f $(DESTDIR)$(LOCALE)/nl/LC_MESSAGES/rotix.mo
endif
