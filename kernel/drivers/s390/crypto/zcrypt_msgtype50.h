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
#ifndef _ZCRYPT_MSGTYPE50_H_
#define _ZCRYPT_MSGTYPE50_H_

#define MSGTYPE50_NAME			"zcrypt_msgtype50"
#define MSGTYPE50_VARIANT_DEFAULT	0

#define MSGTYPE50_CRB2_MAX_MSG_SIZE	0x390 /*sizeof(struct type50_crb2_msg)*/
#define MSGTYPE50_CRB3_MAX_MSG_SIZE	0x710 /*sizeof(struct type50_crb3_msg)*/

#define MSGTYPE_ADJUSTMENT		0x08  /*type04 extension (not needed in type50)*/

int zcrypt_msgtype50_init(void);
void zcrypt_msgtype50_exit(void);

#endif /* _ZCRYPT_MSGTYPE50_H_ */
