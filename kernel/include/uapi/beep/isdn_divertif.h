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
#ifndef _UAPI_BEEP_ISDN_DIVERTIF_H
#define _UAPI_BEEP_ISDN_DIVERTIF_H

/***********************************************************/
/* magic value is also used to control version information */
/***********************************************************/
#define DIVERT_IF_MAGIC 0x25873401
#define DIVERT_CMD_REG  0x00  /* register command */
#define DIVERT_CMD_REL  0x01  /* release command */
#define DIVERT_NO_ERR   0x00  /* return value no error */
#define DIVERT_CMD_ERR  0x01  /* invalid cmd */
#define DIVERT_VER_ERR  0x02  /* magic/version invalid */
#define DIVERT_REG_ERR  0x03  /* module already registered */
#define DIVERT_REL_ERR  0x04  /* module not registered */
#define DIVERT_REG_NAME isdn_register_divert


#endif /* _UAPI_BEEP_ISDN_DIVERTIF_H */
