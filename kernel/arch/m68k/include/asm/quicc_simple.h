/*
    Mavox-ID | https://ye-a.pp.ua
    Copyright (C) 2026  Mavox-ID

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __SIMPLE_H
#define __SIMPLE_H

/* #include "quicc.h" */

#define GLB_SCC_0   0
#define GLB_SCC_1   1
#define GLB_SCC_2   2
#define GLB_SCC_3   3

typedef void (int_routine)(unsigned short interrupt_event);
typedef int_routine *int_routine_ptr; 
typedef void *(alloc_routine)(int length);
typedef void (free_routine)(int scc_num, int channel_num, void *buf);
typedef void (store_rx_buffer_routine)(int scc_num, int channel_num, void *buff, int length);
typedef int  (handle_tx_error_routine)(int scc_num, int channel_num, QUICC_BD *tbd);
typedef void (handle_rx_error_routine)(int scc_num, int channel_num, QUICC_BD *rbd);
typedef void (handle_lost_error_routine)(int scc_num, int channel_num);

/* user defined functions for global errors */
typedef void (handle_glob_overrun_routine)(int scc_number);
typedef void (handle_glob_underrun_routine)(int scc_number);
typedef void (glob_intr_q_overflow_routine)(int scc_number);

/*
 * General initialization and command routines
 */
void quicc_issue_cmd (unsigned short cmd, int scc_num);
void quicc_init(void);
void quicc_scc_init(int scc_number, int number_of_rx_buf, int number_of_tx_buf);
void quicc_smc_init(int smc_number, int number_of_rx_buf, int number_of_tx_buf);
void quicc_scc_start(int scc_num);
void quicc_scc_loopback(int scc_num);

/* Interrupt enable/disable routines for critical pieces of code*/
unsigned short  IntrDis(void);
void            IntrEna(unsigned short old_sr);

/* For debugging */
void print_rbd(int scc_num);
void print_tbd(int scc_num);

#endif
