#!/usr/bin/env bash

D=libsodium-1.0.8
T=$D.tar
F=$T.gz
B=$PWD/build

if [ ! -f "$F" ]; then
	wget https://download.libsodium.org/libsodium/releases/libsodium-1.0.8.tar.gz
fi

if [ -d "$D" ]; then
	rm -rf "$D"
fi

tar xzf $F && cd $D && ./configure --disable-shared --enable-static --prefix=$B && make && make install
