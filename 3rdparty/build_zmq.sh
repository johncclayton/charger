#!/usr/bin/env bash

D=zeromq-4.1.4
T=$D.tar
F=$T.gz
B=$PWD/build

if [ ! -f "$F" ]; then
	wget https://github.com/zeromq/zeromq4-1/releases/download/v4.1.4/zeromq-4.1.4.tar.gz
fi

if [ -d "$D" ]; then
	rm -rf "$D"
fi

tar xzf $F && cd $D && ./configure --host=arm-linux-gnueabihf --disable-shared --enable-static --prefix=$B --with-libsodium=$B && make && make install
