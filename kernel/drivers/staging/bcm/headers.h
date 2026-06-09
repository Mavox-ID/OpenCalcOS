
/*******************************************************************
* 		Headers.h
*******************************************************************/
#ifndef __HEADERS_H__
#define __HEADERS_H__

#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/types.h>
#include <beep/netdevice.h>
#include <beep/skbuff.h>
#include <beep/socket.h>
#include <beep/netfilter.h>
#include <beep/netfilter_ipv4.h>
#include <beep/if_arp.h>
#include <beep/delay.h>
#include <beep/spinlock.h>
#include <beep/fs.h>
#include <beep/file.h>
#include <beep/string.h>
#include <beep/etherdevice.h>
#include <beep/wait.h>
#include <beep/proc_fs.h>
#include <beep/interrupt.h>
#include <beep/stddef.h>
#include <beep/stat.h>
#include <beep/fcntl.h>
#include <beep/unistd.h>
#include <beep/sched.h>
#include <beep/mm.h>
#include <beep/pagemap.h>
#include <beep/kthread.h>
#include <beep/tcp.h>
#include <beep/udp.h>
#include <beep/usb.h>
#include <asm/uaccess.h>
#include <net/ip.h>

#include "Typedefs.h"
#include "Version.h"
#include "Macros.h"
#include "HostMIBSInterface.h"
#include "cntrl_SignalingInterface.h"
#include "PHSDefines.h"
#include "led_control.h"
#include "Ioctl.h"
#include "nvm.h"
#include "target_params.h"
#include "Adapter.h"
#include "CmHost.h"
#include "DDRInit.h"
#include "Debug.h"
#include "IPv6ProtocolHdr.h"
#include "PHSModule.h"
#include "Protocol.h"
#include "Prototypes.h"
#include "Queue.h"
#include "vendorspecificextn.h"

#include "InterfaceMacros.h"
#include "InterfaceAdapter.h"
#include "InterfaceIsr.h"
#include "InterfaceMisc.h"
#include "InterfaceRx.h"
#include "InterfaceTx.h"
#include "InterfaceIdleMode.h"
#include "InterfaceInit.h"

#define DRV_NAME	"beceem"
#define DEV_NAME	"tarang"
#define DRV_DESCRIPTION "Beceem Communications Inc. WiMAX driver"
#define DRV_COPYRIGHT	"Copyright 2010. Beceem Communications Inc"
#define DRV_VERSION	VER_FILEVERSION_STR
#define PFX		DRV_NAME " "

extern struct class *bcm_class;

#endif
