/* This is a generated file, don't edit */

#define NUM_APPLETS 38
#define KNOWN_APPNAME_OFFSETS 4

const uint16_t applet_nameofs[] ALIGN2 = {
48,
100,
156,
};

const char applet_names[] ALIGN1 = ""
"bash" "\0"
"beeprc" "\0"
"busybox" "\0"
"cat" "\0"
"chmod" "\0"
"clear" "\0"
"cp" "\0"
"dd" "\0"
"dmesg" "\0"
"echo" "\0"
"free" "\0"
"halt" "\0"
"hexdump" "\0"
"hexedit" "\0"
"hush" "\0"
"init" "\0"
"kill" "\0"
"ln" "\0"
"ls" "\0"
"mkdir" "\0"
"mount" "\0"
"mountpoint" "\0"
"mv" "\0"
"poweroff" "\0"
"printf" "\0"
"pwd" "\0"
"reboot" "\0"
"rm" "\0"
"rmdir" "\0"
"sh" "\0"
"sha256sum" "\0"
"sleep" "\0"
"top" "\0"
"touch" "\0"
"umount" "\0"
"uname" "\0"
"uptime" "\0"
"watch" "\0"
;

#define APPLET_NO_bash 0
#define APPLET_NO_beeprc 1
#define APPLET_NO_busybox 2
#define APPLET_NO_cat 3
#define APPLET_NO_chmod 4
#define APPLET_NO_clear 5
#define APPLET_NO_cp 6
#define APPLET_NO_dd 7
#define APPLET_NO_dmesg 8
#define APPLET_NO_echo 9
#define APPLET_NO_free 10
#define APPLET_NO_halt 11
#define APPLET_NO_hexdump 12
#define APPLET_NO_hexedit 13
#define APPLET_NO_hush 14
#define APPLET_NO_init 15
#define APPLET_NO_kill 16
#define APPLET_NO_ln 17
#define APPLET_NO_ls 18
#define APPLET_NO_mkdir 19
#define APPLET_NO_mount 20
#define APPLET_NO_mountpoint 21
#define APPLET_NO_mv 22
#define APPLET_NO_poweroff 23
#define APPLET_NO_printf 24
#define APPLET_NO_pwd 25
#define APPLET_NO_reboot 26
#define APPLET_NO_rm 27
#define APPLET_NO_rmdir 28
#define APPLET_NO_sh 29
#define APPLET_NO_sha256sum 30
#define APPLET_NO_sleep 31
#define APPLET_NO_top 32
#define APPLET_NO_touch 33
#define APPLET_NO_umount 34
#define APPLET_NO_uname 35
#define APPLET_NO_uptime 36
#define APPLET_NO_watch 37

#ifndef SKIP_applet_main
int (*const applet_main[])(int argc, char **argv) = {
hush_main,
init_main,
busybox_main,
cat_main,
chmod_main,
clear_main,
cp_main,
dd_main,
dmesg_main,
echo_main,
free_main,
halt_main,
hexdump_main,
hexedit_main,
hush_main,
init_main,
kill_main,
ln_main,
ls_main,
mkdir_main,
mount_main,
mountpoint_main,
mv_main,
halt_main,
printf_main,
pwd_main,
halt_main,
rm_main,
rmdir_main,
hush_main,
md5_sha1_sum_main,
sleep_main,
top_main,
touch_main,
umount_main,
uname_main,
uptime_main,
watch_main,
};
#endif

const uint8_t applet_flags[] ALIGN1 = {
0x00,
0xae,
0x3c,
0x02,
0xeb,
0x28,
0x8f,
0x23,
0xec,
0x02,
};

const uint8_t applet_suid[] ALIGN1 = {
0x10,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
0x00,
};

const uint8_t applet_install_loc[] ALIGN1 = {
0x01,
0x11,
0x31,
0x11,
0x11,
0x23,
0x33,
0x21,
0x11,
0x11,
0x11,
0x21,
0x13,
0x12,
0x11,
0x13,
0x13,
0x11,
0x13,
};
