D=zeromq-4.1.4
T=$D.tar
F=$T.gz
B=$PWD/build

if [ ! -f "$F" ]; then
	wget http://download.zeromq.org/zeromq-4.1.4.tar.gz 
fi

if [ -d "$D" ]; then
	rm -rf "$D"
fi

tar xzf $F && cd $D && ./configure --disable-shared --enable-static --prefix=$B --with-libsodium=$B && make && make install
