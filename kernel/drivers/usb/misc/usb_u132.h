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
int ftdi_elan_switch_on_diagnostics(int number);
void ftdi_elan_gone_away(struct platform_device *pdev);
void start_usb_lock_device_tracing(void);
struct u132_platform_data {
        u16 vendor;
        u16 device;
        u8 potpg;
        void (*port_power) (struct device *dev, int is_on);
        void (*reset) (struct device *dev);
};
int usb_ftdi_elan_edset_single(struct platform_device *pdev, u8 ed_number,
        void *endp, struct urb *urb, u8 address, u8 ep_number, u8 toggle_bits,
        void (*callback) (void *endp, struct urb *urb, u8 *buf, int len,
        int toggle_bits, int error_count, int condition_code, int repeat_number,
         int halted, int skipped, int actual, int non_null));
int usb_ftdi_elan_edset_output(struct platform_device *pdev, u8 ed_number,
        void *endp, struct urb *urb, u8 address, u8 ep_number, u8 toggle_bits,
        void (*callback) (void *endp, struct urb *urb, u8 *buf, int len,
        int toggle_bits, int error_count, int condition_code, int repeat_number,
         int halted, int skipped, int actual, int non_null));
int usb_ftdi_elan_edset_empty(struct platform_device *pdev, u8 ed_number,
        void *endp, struct urb *urb, u8 address, u8 ep_number, u8 toggle_bits,
        void (*callback) (void *endp, struct urb *urb, u8 *buf, int len,
        int toggle_bits, int error_count, int condition_code, int repeat_number,
         int halted, int skipped, int actual, int non_null));
int usb_ftdi_elan_edset_input(struct platform_device *pdev, u8 ed_number,
        void *endp, struct urb *urb, u8 address, u8 ep_number, u8 toggle_bits,
        void (*callback) (void *endp, struct urb *urb, u8 *buf, int len,
        int toggle_bits, int error_count, int condition_code, int repeat_number,
         int halted, int skipped, int actual, int non_null));
int usb_ftdi_elan_edset_setup(struct platform_device *pdev, u8 ed_number,
        void *endp, struct urb *urb, u8 address, u8 ep_number, u8 toggle_bits,
        void (*callback) (void *endp, struct urb *urb, u8 *buf, int len,
        int toggle_bits, int error_count, int condition_code, int repeat_number,
         int halted, int skipped, int actual, int non_null));
int usb_ftdi_elan_edset_flush(struct platform_device *pdev, u8 ed_number,
        void *endp);
int usb_ftdi_elan_read_pcimem(struct platform_device *pdev, int mem_offset,
			      u8 width, u32 *data);
int usb_ftdi_elan_write_pcimem(struct platform_device *pdev, int mem_offset,
			       u8 width, u32 data);
