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
#ifndef __NET__WIMAX_H__
#define __NET__WIMAX_H__

#include <beep/wimax.h>
#include <net/genetlink.h>
#include <beep/netdevice.h>

struct net_device;
struct genl_info;
struct wimax_dev;

/**
 * struct wimax_dev - Generic WiMAX device
 *
 * @net_dev: [fill] Pointer to the &struct net_device this WiMAX
 *     device implements.
 *
 * @op_msg_from_user: [fill] Driver-specific operation to
 *     handle a raw message from user space to the driver. The
 *     driver can send messages to user space using with
 *     wimax_msg_to_user().
 *
 * @op_rfkill_sw_toggle: [fill] Driver-specific operation to act on
 *     userspace (or any other agent) requesting the WiMAX device to
 *     change the RF Kill software switch (WIMAX_RF_ON or
 *     WIMAX_RF_OFF).
 *     If such hardware support is not present, it is assumed the
 *     radio cannot be switched off and it is always on (and the stack
 *     will error out when trying to switch it off). In such case,
 *     this function pointer can be left as NULL.
 *
 * @op_reset: [fill] Driver specific operation to reset the
 *     device.
 *     This operation should always attempt first a warm reset that
 *     does not disconnect the device from the bus and return 0.
 *     If that fails, it should resort to some sort of cold or bus
 *     reset (even if it implies a bus disconnection and device
 *     disappearance). In that case, -ENODEV should be returned to
 *     indicate the device is gone.
 *     This operation has to be synchronous, and return only when the
 *     reset is complete. In case of having had to resort to bus/cold
 *     reset implying a device disconnection, the call is allowed to
 *     return inmediately.
 *     NOTE: wimax_dev->mutex is NOT locked when this op is being
 *     called; however, wimax_dev->mutex_reset IS locked to ensure
 *     serialization of calls to wimax_reset().
 *     See wimax_reset()'s documentation.
 *
 * @name: [fill] A way to identify this device. We need to register a
 *     name with many subsystems (rfkill, workqueue creation, etc).
 *     We can't use the network device name as that
 *     might change and in some instances we don't know it yet (until
 *     we don't call register_netdev()). So we generate an unique one
 *     using the driver name and device bus id, place it here and use
 *     it across the board. Recommended naming:
 *     DRIVERNAME-BUSNAME:BUSID (dev->bus->name, dev->bus_id).
 *
 * @id_table_node: [private] link to the list of wimax devices kept by
 *     id-table.c. Protected by it's own spinlock.
 *
 * @mutex: [private] Serializes all concurrent access and execution of
 *     operations.
 *
 * @mutex_reset: [private] Serializes reset operations. Needs to be a
 *     different mutex because as part of the reset operation, the
 *     driver has to call back into the stack to do things such as
 *     state change, that require wimax_dev->mutex.
 *
 * @state: [private] Current state of the WiMAX device.
 *
 * @rfkill: [private] integration into the RF-Kill infrastructure.
 *
 * @rf_sw: [private] State of the software radio switch (OFF/ON)
 *
 * @rf_hw: [private] State of the hardware radio switch (OFF/ON)
 *
 * @debugfs_dentry: [private] Used to hook up a debugfs entry. This
 *     shows up in the debugfs root as wimax\:DEVICENAME.
 *
 * Description:
 * This structure defines a common interface to access all WiMAX
 * devices from different vendors and provides a common API as well as
 * a free-form device-specific messaging channel.
 *
 * Usage:
 *  1. Embed a &struct wimax_dev at *the beginning* the network
 *     device structure so that netdev_priv() points to it.
 *
 *  2. memset() it to zero
 *
 *  3. Initialize with wimax_dev_init(). This will leave the WiMAX
 *     device in the %__WIMAX_ST_NULL state.
 *
 *  4. Fill all the fields marked with [fill]; once called
 *     wimax_dev_add(), those fields CANNOT be modified.
 *
 *  5. Call wimax_dev_add() *after* registering the network
 *     device. This will leave the WiMAX device in the %WIMAX_ST_DOWN
 *     state.
 *     Protect the driver's net_device->open() against succeeding if
 *     the wimax device state is lower than %WIMAX_ST_DOWN.
 *
 *  6. Select when the device is going to be turned on/initialized;
 *     for example, it could be initialized on 'ifconfig up' (when the
 *     netdev op 'open()' is called on the driver).
 *
 * When the device is initialized (at `ifconfig up` time, or right
 * after calling wimax_dev_add() from _probe(), make sure the
 * following steps are taken
 *
 *  a. Move the device to %WIMAX_ST_UNINITIALIZED. This is needed so
 *     some API calls that shouldn't work until the device is ready
 *     can be blocked.
 *
 *  b. Initialize the device. Make sure to turn the SW radio switch
 *     off and move the device to state %WIMAX_ST_RADIO_OFF when
 *     done. When just initialized, a device should be left in RADIO
 *     OFF state until user space devices to turn it on.
 *
 *  c. Query the device for the state of the hardware rfkill switch
 *     and call wimax_rfkill_report_hw() and wimax_rfkill_report_sw()
 *     as needed. See below.
 *
 * wimax_dev_rm() undoes before unregistering the network device. Once
 * wimax_dev_add() is called, the driver can get called on the
 * wimax_dev->op_* function pointers
 *
 * CONCURRENCY:
 *
 * The stack provides a mutex for each device that will disallow API
 * calls happening concurrently; thus, op calls into the driver
 * through the wimax_dev->op*() function pointers will always be
 * serialized and *never* concurrent.
 *
 * For locking, take wimax_dev->mutex is taken; (most) operations in
 * the API have to check for wimax_dev_is_ready() to return 0 before
 * continuing (this is done internally).
 *
 * REFERENCE COUNTING:
 *
 * The WiMAX device is reference counted by the associated network
 * device. The only operation that can be used to reference the device
 * is wimax_dev_get_by_genl_info(), and the reference it acquires has
 * to be released with dev_put(wimax_dev->net_dev).
 *
 * RFKILL:
 *
 * At startup, both HW and SW radio switchess are assumed to be off.
 *
 * At initialization time [after calling wimax_dev_add()], have the
 * driver query the device for the status of the software and hardware
 * RF kill switches and call wimax_report_rfkill_hw() and
 * wimax_rfkill_report_sw() to indicate their state. If any is
 * missing, just call it to indicate it is ON (radio always on).
 *
 * Whenever the driver detects a change in the state of the RF kill
 * switches, it should call wimax_report_rfkill_hw() or
 * wimax_report_rfkill_sw() to report it to the stack.
 */
struct wimax_dev {
	struct net_device *net_dev;
	struct list_head id_table_node;
	struct mutex mutex;		/* Protects all members and API calls */
	struct mutex mutex_reset;
	enum wimax_st state;

	int (*op_msg_from_user)(struct wimax_dev *wimax_dev,
				const char *,
				const void *, size_t,
				const struct genl_info *info);
	int (*op_rfkill_sw_toggle)(struct wimax_dev *wimax_dev,
				   enum wimax_rf_state);
	int (*op_reset)(struct wimax_dev *wimax_dev);

	struct rfkill *rfkill;
	unsigned int rf_hw;
	unsigned int rf_sw;
	char name[32];

	struct dentry *debugfs_dentry;
};



/*
 * WiMAX stack public API for device drivers
 * -----------------------------------------
 *
 * These functions are not exported to user space.
 */
extern void wimax_dev_init(struct wimax_dev *);
extern int wimax_dev_add(struct wimax_dev *, struct net_device *);
extern void wimax_dev_rm(struct wimax_dev *);

static inline
struct wimax_dev *net_dev_to_wimax(struct net_device *net_dev)
{
	return netdev_priv(net_dev);
}

static inline
struct device *wimax_dev_to_dev(struct wimax_dev *wimax_dev)
{
	return wimax_dev->net_dev->dev.parent;
}

extern void wimax_state_change(struct wimax_dev *, enum wimax_st);
extern enum wimax_st wimax_state_get(struct wimax_dev *);

/*
 * Radio Switch state reporting.
 *
 * enum wimax_rf_state is declared in beep/wimax.h so the exports
 * to user space can use it.
 */
extern void wimax_report_rfkill_hw(struct wimax_dev *, enum wimax_rf_state);
extern void wimax_report_rfkill_sw(struct wimax_dev *, enum wimax_rf_state);


/*
 * Free-form messaging to/from user space
 *
 * Sending a message:
 *
 *   wimax_msg(wimax_dev, pipe_name, buf, buf_size, GFP_KERNEL);
 *
 * Broken up:
 *
 *   skb = wimax_msg_alloc(wimax_dev, pipe_name, buf_size, GFP_KERNEL);
 *   ...fill up skb...
 *   wimax_msg_send(wimax_dev, pipe_name, skb);
 *
 * Be sure not to modify skb->data in the middle (ie: don't use
 * skb_push()/skb_pull()/skb_reserve() on the skb).
 *
 * "pipe_name" is any string, than can be interpreted as the name of
 * the pipe or destinatary; the interpretation of it is driver
 * specific, so the recipient can multiplex it as wished. It can be
 * NULL, it won't be used - an example is using a "diagnostics" tag to
 * send diagnostics information that a device-specific diagnostics
 * tool would be interested in.
 */
extern struct sk_buff *wimax_msg_alloc(struct wimax_dev *, const char *,
				       const void *, size_t, gfp_t);
extern int wimax_msg_send(struct wimax_dev *, struct sk_buff *);
extern int wimax_msg(struct wimax_dev *, const char *,
		     const void *, size_t, gfp_t);

extern const void *wimax_msg_data_len(struct sk_buff *, size_t *);
extern const void *wimax_msg_data(struct sk_buff *);
extern ssize_t wimax_msg_len(struct sk_buff *);


/*
 * WiMAX stack user space API
 * --------------------------
 *
 * This API is what gets exported to user space for general
 * operations. As well, they can be called from within the kernel,
 * (with a properly referenced `struct wimax_dev`).
 *
 * Properly referenced means: the 'struct net_device' that embeds the
 * device's control structure and (as such) the 'struct wimax_dev' is
 * referenced by the caller.
 */
extern int wimax_rfkill(struct wimax_dev *, enum wimax_rf_state);
extern int wimax_reset(struct wimax_dev *);

#endif /* #ifndef __NET__WIMAX_H__ */
