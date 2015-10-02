#!/bin/bash
pushd . > /dev/null
cd pkgrepo && dpkg-scanpackages . /dev/null | gzip -9c > Packages.gz && scp -r *.* john@d1813.home:www/debian/
