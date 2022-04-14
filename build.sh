#!/bin/bash

TOP=$PWD

build_ee() {
	[[ ! -d 'build_cygee' ]] && mkdir build_cygee
	pushd build_cygee
		CC='gcc -m32' LDFLAGS='-static' ../ee/configure --target=ee --enable-c-cpplib --without-sim --disable-sim --host=i686-linux-gnu --prefix=$TOP/toolchain/ee
		make -j $(($(nproc) + 1))
		make install
	popd
	
	# remove some files which we don't need in the decomp toolchain
	
	rm $TOP/toolchain/ee/bin/bison
	rm $TOP/toolchain/ee/bin/byacc
	rm $TOP/toolchain/ee/bin/flex
	rm $TOP/toolchain/ee/bin/flex++
	rm $TOP/toolchain/ee/bin/gcov
	rm $TOP/toolchain/ee/bin/patch
	rm $TOP/toolchain/ee/bin/runtest
	
	# Bison files, and dejagnu (we need neither)
	rm -rf $TOP/toolchain/ee/share
	
	rm -rf $TOP/toolchain/ee/info
	rm -rf $TOP/toolchain/ee/man
	#rm -rf $TOP/toolchain/ee/libexec
}

build_iop() {
# build toolchains

	[[ ! -d 'build_iop_binutils' ]] && mkdir build_iop_binutils
	pushd build_iop_binutils
		CC='gcc -m32' LDFLAGS='-static' ../iop/binutils-2.9.1/configure --target=mipsel-scei-elfl --host=i686-linux-gnu --prefix=$TOP/toolchain/iop
		make -j $(($(nproc) + 1))
		make install
	popd

	[[ ! -d 'build_iop_gcc' ]] && mkdir build_iop_gcc
	pushd build_iop_gcc
		CC='gcc -m32' LDFLAGS='-static' ../iop/gcc-2.8.1/configure --target=mipsel-scei-elfl --host=i686-linux-gnu --prefix=$TOP/toolchain/iop --with-gnu-ld --with-gnu-as
		# TODO: C++?
		make LANGUAGES=c -j $(($(nproc) + 1))
		make LANGUAGES=c install
	popd

	rm -rf $TOP/toolchain/iop/info
	rm -rf $TOP/toolchain/iop/man
}

build_ee
build_iop