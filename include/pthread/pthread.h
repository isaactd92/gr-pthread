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


#ifndef INCLUDED_PTHREAD_PTHREAD_H
#define INCLUDED_PTHREAD_PTHREAD_H

#include <pthread/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace pthread {

    /*!
     * \brief <+description of block+>
     * \ingroup pthread
     *
     */
    class PTHREAD_API pthread : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<pthread> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of pthread::pthread.
       *
       * To avoid accidental use of raw pointers, pthread::pthread's
       * constructor is in a private implementation
       * class. pthread::pthread::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace pthread
} // namespace gr

#endif /* INCLUDED_PTHREAD_PTHREAD_H */

