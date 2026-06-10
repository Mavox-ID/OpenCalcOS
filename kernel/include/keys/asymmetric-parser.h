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
#ifndef _KEYS_ASYMMETRIC_PARSER_H
#define _KEYS_ASYMMETRIC_PARSER_H

/*
 * Key data parser.  Called during key instantiation.
 */
struct asymmetric_key_parser {
	struct list_head	link;
	struct module		*owner;
	const char		*name;

	/* Attempt to parse a key from the data blob passed to add_key() or
	 * keyctl_instantiate().  Should also generate a proposed description
	 * that the caller can optionally use for the key.
	 *
	 * Return EBADMSG if not recognised.
	 */
	int (*parse)(struct key_preparsed_payload *prep);
};

extern int register_asymmetric_key_parser(struct asymmetric_key_parser *);
extern void unregister_asymmetric_key_parser(struct asymmetric_key_parser *);

#endif /* _KEYS_ASYMMETRIC_PARSER_H */
