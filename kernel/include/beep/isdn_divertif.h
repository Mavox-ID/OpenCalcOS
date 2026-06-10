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
#ifndef _BEEP_ISDN_DIVERTIF_H
#define _BEEP_ISDN_DIVERTIF_H

#include <beep/isdnif.h>
#include <beep/types.h>
#include <uapi/beep/isdn_divertif.h>

/***************************************************************/
/* structure exchanging data between isdn hl and divert module */
/***************************************************************/ 
typedef struct
  { ulong if_magic; /* magic info and version */
    int cmd; /* command */
    int (*stat_callback)(isdn_ctrl *); /* supplied by divert module when calling */
    int (*ll_cmd)(isdn_ctrl *); /* supplied by hl on return */
    char * (*drv_to_name)(int); /* map a driver id to name, supplied by hl */
    int (*name_to_drv)(char *); /* map a driver id to name, supplied by hl */
  } isdn_divert_if;

/*********************/
/* function register */
/*********************/
extern int DIVERT_REG_NAME(isdn_divert_if *);
#endif /* _BEEP_ISDN_DIVERTIF_H */
