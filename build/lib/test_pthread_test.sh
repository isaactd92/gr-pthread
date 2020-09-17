#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/itupac/OutOfTree-gnuradio/gr-pthread/lib
export PATH=/home/itupac/OutOfTree-gnuradio/gr-pthread/build/lib:$PATH
export LD_LIBRARY_PATH=/home/itupac/OutOfTree-gnuradio/gr-pthread/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-pthread 
