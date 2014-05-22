# stick to what we have for now
ONLY_FOR_ARCHS =	amd64
#NOT_FOR_ARCHS =	
#SHARED_ONLY =		
#COMES_WITH =		

COMMENT =			dbus utilities

DISTNAME =			dbus-utils-0.1

CATEGORIES =		misc

HOMEPAGE =			http://uglyman.kremlin.cc

MAINTAINER =		kremlin <ian@kremlin.cc>

# LGPLv1.3+ (glib)
PERMIT_PACKAGE_CDROM =	Yes

# for now
WANTLIB = c gio-2.0 glib-2.0

#TODO: see if it's okay to host this
MASTER_SITES = http://uglyman.kremlin.cc/gitweb/gitweb.cgi?p=systemd-utl.git;a=snapshot;h=refs/heads/master;sf=tgz

#MODULES =		???
#BUILD_DEPENDS =	???
#RUN_DEPENDS =		???
#TEST_DEPENDS =		???
LIB_DEPENDS =		x11/dbus>=1.8.2v0 \
					devel/glib2

#MAKE_FLAGS =		???
#MAKE_ENV =		???
#FAKE_FLAGS =		???
#TEST_FLAGS =		???

# build/configuration variables
#
#SEPARATE_BUILD =	Yes (build in a directory other than WRKSRC)
#SEPARATE_BUILD =	flavored (distinct flavors may share a common WRKSRC)
CONFIGURE_STYLE = 	simple

#CFLAGS =		???
#LDFLAGS =		???
#MAKE_FILE =		???
#PKG_ARCH =		??? (* for arch-independent packages)
#WRKDIST =		??? if other than ${WRKDIR}/${DISTNAME}
#WRKSRC =		??? if other than ${WRKDIST}
#WRKBUILD =		??? if other than ${WRKSRC}
#WRKCONF =		??? if other than ${WRKBUILD}

#ALL_TARGET =		???
#INSTALL_TARGET =	???
#TEST_TARGET =		???

.include <bsd.port.mk>
