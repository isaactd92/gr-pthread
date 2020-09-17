/* -*- c++ -*- */
/* 
 * Copyright 2020 gr-pthread author.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "pthread_impl.h"

#include <pthread.h>
#include <stdio.h>
#include <signal.h>

#include <zmq.hpp>

zmq::context_t context(1);

int i=0;
int j=0;

void *thread_routine2(void*)
{
 
  while(j<1000){
   printf("El segundo hilo comienza a ejecutarse ...\n");
   j++; 
 }
  if(j>=1000){
  printf("Estoy fuera del while del segundo hilo ...\n");
 }

}

 void *thread_routine(void*)
 {
  while(i<1000){
   
  printf("El primer hilo comienza a ejecutarse ...\n");
  i++;  
 }
  if(i>=1000){
  printf("Estoy fuera del while del primer hilo ...\n");
 }

  int arreglo[20] = {1,2,3,4,5};
  char array[sizeof(arreglo)]={};

  memcpy(array,arreglo,sizeof(arreglo));
  
  zmq::socket_t server (context, ZMQ_PUSH);
  server.bind("ipc://5557");
  size_t tamano = sizeof(array);
  zmq::message_t reply(tamano);
  memcpy((void *) reply.data(), array, tamano);//void * memset ( void * ptr, int value, size_t num );
  server.send(reply); 	

 }

namespace gr {
  namespace pthread {

    pthread::sptr
    pthread::make()
    {
      return gnuradio::get_initial_sptr
        (new pthread_impl());
    }

    /*
     * The private constructor
     */
    pthread_impl::pthread_impl()
      : gr::block("pthread",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, sizeof(float)))
    {}

    /*
     * Our virtual destructor.
     */
    pthread_impl::~pthread_impl()
    {
    }

    void
    pthread_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    pthread_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      float *out = (float *) output_items[0];

      // Do <+signal processing+>
      for (int i = 0 ; i<noutput_items;i++)	 	      
	out[i]=2;
      	
      pthread_t thread1;
      pthread_t thread2;

      if(0!=pthread_create(&thread1,NULL,thread_routine,NULL))
	return -1;

      if(0!=pthread_create(&thread2,NULL,thread_routine2,NULL))
	return -1;

      pthread_join(thread1,NULL);
      pthread_join(thread2,NULL);
      
      printf("\n");
      printf("__________>>>>>Se terminó los join<<<<<<<_______. \n");
      printf("\n");	

      zmq::socket_t client (context, ZMQ_PULL);
      client.connect("ipc://5557");
      zmq::message_t msg;
      client.recv(&msg);
      size_t mensaje = msg.size();//20
      char* llegada = (char*)(msg.data());	
      int entero[mensaje]={};
      memcpy(entero,llegada,mensaje);//20 bytes
	   
      printf("**********El mensaje de llegada 0 es: %d\n***************\n",entero[0]);
      printf("**********El mensaje de llegada 1 es: %d\n***************\n",entero[1]);
      printf("**********El mensaje de llegada 2 es: %d\n***************\n",entero[2]);    
      printf("**********El mensaje de llegada 3 es: %d\n***************\n",entero[3]);
      printf("**********El mensaje de llegada 4 es: %d\n***************\n",entero[4]); 	

      printf("\n");
      printf("__________>>>>>Se terminó el programa<<<<<<<_______. \n");
      printf("\n");	

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace pthread */
} /* namespace gr */

