#!/bin/bash

PACKAGE=charger_1.0-1_all.deb
if [ -f "$PACKAGE" ]; then
	rm "$PACKAGE"
fi

mkdir -p debian/DEBIAN

cp debian/control debian/DEBIAN/control
cp debian/copyright debian/DEBIAN/copyright

fakeroot dpkg-deb --build debian $PACKAGE && echo "Linting it..." && lintian $PACKAGE
