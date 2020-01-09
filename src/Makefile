VERSION=$(shell awk '/Version:/ { print $$2 }' MAKEDEV.spec)
RELEASE=$(shell awk '/Release:/ { print $$2 }' MAKEDEV.spec)
TAG = makedev$(subst .,-,$(VERSION)-$(RELEASE))

all: MAKEDEV mksock $(GENERATED_WITH_SUBDIR)

GENERATED = alsa cciss dac960 ida

DO_02 = cciss dac960 ida

CONF = 00macros cdrom console ftape generic ia64 ibcs ide ipfilter isdn \
       linux1394 linux-2.6.x 02linux-2.6.x mouse qic raid redhat s390 sound std \
       undocumented v4l $(GENERATED)

GENERATED_WITH_SUBDIR=$(patsubst %,makedev.d/%,$(GENERATED))

GENERATORS=$(patsubst %,./gen%,$(GENERATED))

$(GENERATED_WITH_SUBDIR): $(GENERATORS)
	$(patsubst makedev.d/%,./gen%,$@) > $@

CONF_WITH_SUBDIR=$(patsubst %,makedev.d/%,$(CONF))

DESTDIR=
DESTDIRS=$(DESTDIR)${DESTDIR:+/}
devdir=/dev
makedevdir=/dev
sbindir=/usr/sbin
sysconfdir=/etc
mandir=/usr/share/man
manext=8
mansubdir=$(mandir)/man$(manext)
confdir=$(sysconfdir)/makedev.d

DEBUGFLAGS=
DEFINES=-DCFGDIR=\"$(confdir)\" -DDEVDIR=\"$(devdir)\" -DVERSION=\"$(VERSION)\"
OPTFLAGS=-g -Os -Wall -Wextra -Wuninitialized
CFLAGS=$(OPTFLAGS) $(DEFINES) $(DEBUG)

ifdef SELINUX
DEFINES += -DMAKEDEV_SELINUX
LDFLAGS += -lselinux
endif

all: MAKEDEV mksock $(CONF_WITH_SUBDIR)

force-tag:
	cvs tag -cFR $(TAG) || echo GRRRrrrrr -- [tag aborted]

tag:
	cvs tag -cR  $(TAG) || echo GRRRrrrrr -- [tag aborted]

archive:
	@git-archive --format=tar --prefix=MAKEDEV-$(VERSION)/ HEAD | gzip -c > MAKEDEV-$(VERSION)-$(RELEASE).tar.gz
	@echo "The final archive is MAKEDEV-$(VERSION)-$(RELEASE).tar.gz."

MAKEDEV: MAKEDEV.c sel.h
	$(CC) -o $@ $(CFLAGS) MAKEDEV.c $(LDFLAGS)

mksock: mksock.c sel.h
	$(CC) -o $@ $(CFLAGS) mksock.c $(LDFLAGS)

install: install-bin install-conf

clean:
	$(RM) -f MAKEDEV core mksock $(GENERATED_WITH_SUBDIR)

install-bin: $(DESTDIRS)$(makedevdir)/MAKEDEV $(DESTDIRS)$(sbindir)/mksock

$(DESTDIRS)$(makedevdir)/MAKEDEV: MAKEDEV
	install -m755 -d $(DESTDIRS)$(makedevdir)
	install -m755 -d $(DESTDIRS)$(devdir)
	install -m755 MAKEDEV $(DESTDIRS)$(makedevdir)/MAKEDEV
	if test $(makedevdir) != $(devdir) ; then \
		topdir="" ; \
		while ! test -r $(DESTDIRS)/$(devdir)/$${topdir}/$(makedevdir); do \
			topdir=$${topdir}$${topdir:+/}.. ; \
		done ; \
		ln -s $${topdir}$(makedevdir)/MAKEDEV $(DESTDIRS)$(devdir)/ ; \
	fi
	install -m755 -d $(DESTDIR)/$(mansubdir)
	install -m644 MAKEDEV.m $(DESTDIR)/$(mansubdir)/MAKEDEV.$(manext)

$(DESTDIRS)$(sbindir)/mksock: mksock
	install -m755 -d $(DESTDIR)/$(sbindir)
	install -m755 mksock $(DESTDIR)/$(sbindir)/mksock

install-conf: $(GENERATED_WITH_SUBDIR)
	install -m755 -d $(DESTDIRS)$(confdir)
	for conf in $(DO_02) ; do \
		install -m644 makedev.d/$$conf $(DESTDIRS)$(confdir)/02$$conf ; \
		rm makedev.d/$$conf ; \
	done
	for conf in $(filter 0%, $(CONF)) ; do \
		install -m644 makedev.d/$$conf $(DESTDIRS)$(confdir)/$$conf ; \
	done
	for conf in $(filter-out $(DO_02), $(filter-out 0%, $(CONF))) ; do \
		install -m644 makedev.d/$$conf $(DESTDIRS)$(confdir)/01$$conf ; \
	done
