/*
 * beep/lib/zlib_deflate/deflate_syms.c
 *
 * Exported symbols for the deflate functionality.
 *
 */

#include <beep/module.h>
#include <beep/init.h>

#include <beep/zlib.h>

EXPORT_SYMBOL(zlib_deflate_workspacesize);
EXPORT_SYMBOL(zlib_deflate);
EXPORT_SYMBOL(zlib_deflateInit2);
EXPORT_SYMBOL(zlib_deflateEnd);
EXPORT_SYMBOL(zlib_deflateReset);
MODULE_LICENSE("GPL");
