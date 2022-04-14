#!/bin/sh

# extracting archives
tar xvfz binutils-2.9.1.tar.gz
tar xvfz gcc-2.8.1.tar.gz

# applying patch
patch -p0 < iop-gcc.patch

# making iop-elf-gcc
distdir=/usr/local/sce/iop/gcc/
cd binutils-2.9.1
./configure --target=mipsel-scei-elfl --prefix=$distdir
make
make install
cd ..
cd gcc-2.8.1
./configure --target=mipsel-scei-elfl --prefix=$distdir --with-gnu-ld --with-gnu-as
make LANGUAGES=c
make LANGUAGES=c install
