#ifndef _BEEP_DIRENT_H
#define _BEEP_DIRENT_H

struct beep_dirent64 {
	u64		d_ino;
	s64		d_off;
	unsigned short	d_reclen;
	unsigned char	d_type;
	char		d_name[0];
};

#endif
