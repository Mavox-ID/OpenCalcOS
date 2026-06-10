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
#ifndef _P80211META_H
#define _P80211META_H

/*----------------------------------------------------------------*/
/* The following structure types are used for the metadata */
/* representation of category list metadata, group list metadata, */
/* and data item metadata for both Mib and Messages. */

struct p80211meta {
	char *name;		/* data item name */
	u32 did;		/* partial did */
	u32 flags;		/* set of various flag bits */
	u32 min;		/* min value of a BOUNDEDint */
	u32 max;		/* max value of a BOUNDEDint */

	u32 maxlen;		/* maxlen of a OCTETSTR or DISPLAYSTR */
	u32 minlen;		/* minlen of a OCTETSTR or DISPLAYSTR */
	p80211enum_t *enumptr;	/* ptr to the enum type for ENUMint */
	p80211_totext_t totextptr;	/* ptr to totext conversion function */
	p80211_fromtext_t fromtextptr;	/* ptr to totext conversion function */
	p80211_valid_t validfunptr;	/* ptr to totext conversion function */
};

struct grplistitem {
	char *name;
	struct p80211meta *itemlist;
};

struct catlistitem {
	char *name;
	struct grplistitem *grplist;
};

#endif /* _P80211META_H */
