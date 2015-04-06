/*
 * File:    fifo_ring.h
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   fifo ring
 *
 * Copyright (c) Li XianJing
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * 2008-12-27 Li XianJing <xianjimli@hotmail.com> created.
 *
 */

#ifndef FIFO_RING_H
#define FIFO_RING_H

FifoRing* fifo_ring_create(size_t length)
Ret fifo_ring_pop(FifoRing* thiz, void** data)
Ret fifo_ring_push(FifoRing* thiz, void* data)    
void fifo_ring_destroy(FifoRing* thiz)

#endif/*FIFO_RING_H*/
