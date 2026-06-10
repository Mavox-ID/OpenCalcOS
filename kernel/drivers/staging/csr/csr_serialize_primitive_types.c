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
#include <beep/module.h>
#include <beep/slab.h>
#include "csr_prim_defs.h"
#include "csr_msgconv.h"
#include "csr_macro.h"

void CsrUint8Des(u8 *value, u8 *buffer, size_t *offset)
{
    *value = buffer[*offset];
    *offset += sizeof(*value);
}
EXPORT_SYMBOL_GPL(CsrUint8Des);

void CsrUint16Des(u16 *value, u8 *buffer, size_t *offset)
{
    *value = (buffer[*offset + 0] << 0) |
             (buffer[*offset + 1] << 8);
    *offset += sizeof(*value);
}
EXPORT_SYMBOL_GPL(CsrUint16Des);

void CsrUint32Des(u32 *value, u8 *buffer, size_t *offset)
{
    *value = (buffer[*offset + 0] << 0) |
             (buffer[*offset + 1] << 8) |
             (buffer[*offset + 2] << 16) |
             (buffer[*offset + 3] << 24);
    *offset += sizeof(*value);
}
EXPORT_SYMBOL_GPL(CsrUint32Des);

void CsrMemCpyDes(void *value, u8 *buffer, size_t *offset, size_t length)
{
    memcpy(value, &buffer[*offset], length);
    *offset += length;
}
EXPORT_SYMBOL_GPL(CsrMemCpyDes);

void CsrCharStringDes(char **value, u8 *buffer, size_t *offset)
{
    *value = kstrdup((char *) &buffer[*offset], GFP_KERNEL);
    *offset += strlen(*value) + 1;
}
EXPORT_SYMBOL_GPL(CsrCharStringDes);

void CsrUint8Ser(u8 *buffer, size_t *offset, u8 value)
{
    buffer[*offset] = value;
    *offset += sizeof(value);
}
EXPORT_SYMBOL_GPL(CsrUint8Ser);

void CsrUint16Ser(u8 *buffer, size_t *offset, u16 value)
{
    buffer[*offset + 0] = (u8) ((value >> 0) & 0xFF);
    buffer[*offset + 1] = (u8) ((value >> 8) & 0xFF);
    *offset += sizeof(value);
}
EXPORT_SYMBOL_GPL(CsrUint16Ser);

void CsrUint32Ser(u8 *buffer, size_t *offset, u32 value)
{
    buffer[*offset + 0] = (u8) ((value >> 0) & 0xFF);
    buffer[*offset + 1] = (u8) ((value >> 8) & 0xFF);
    buffer[*offset + 2] = (u8) ((value >> 16) & 0xFF);
    buffer[*offset + 3] = (u8) ((value >> 24) & 0xFF);
    *offset += sizeof(value);
}
EXPORT_SYMBOL_GPL(CsrUint32Ser);

void CsrMemCpySer(u8 *buffer, size_t *offset, const void *value, size_t length)
{
    memcpy(&buffer[*offset], value, length);
    *offset += length;
}
EXPORT_SYMBOL_GPL(CsrMemCpySer);

void CsrCharStringSer(u8 *buffer, size_t *offset, const char *value)
{
    if (value)
    {
        strcpy(((char *) &buffer[*offset]), value);
        *offset += strlen(value) + 1;
    }
    else
    {
        CsrUint8Ser(buffer, offset, 0);
    }
}
EXPORT_SYMBOL_GPL(CsrCharStringSer);
