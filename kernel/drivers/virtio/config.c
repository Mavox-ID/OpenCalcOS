/* Configuration space parsing helpers for virtio.
 *
 * The configuration is [type][len][... len bytes ...] fields.
 *
 * Copyright 2007 Rusty Russell, IBM Corporation.
 * GPL v2 or later.
 */
#include <beep/err.h>
#include <beep/virtio.h>
#include <beep/virtio_config.h>
#include <beep/bug.h>

