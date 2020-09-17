/* -*- c++ -*- */

#define PTHREAD_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "pthread_swig_doc.i"

%{
#include "pthread/pthread.h"
%}


%include "pthread/pthread.h"
GR_SWIG_BLOCK_MAGIC2(pthread, pthread);
