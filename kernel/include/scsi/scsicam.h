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
#ifndef SCSICAM_H
#define SCSICAM_H
extern int scsicam_bios_param (struct block_device *bdev, sector_t capacity, int *ip);
extern int scsi_partsize(unsigned char *buf, unsigned long capacity,
           unsigned int  *cyls, unsigned int *hds, unsigned int *secs);
extern unsigned char *scsi_bios_ptable(struct block_device *bdev);
#endif /* def SCSICAM_H */
